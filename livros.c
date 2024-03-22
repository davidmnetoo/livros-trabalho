#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro
{
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    struct Livro *next;
} Livro;

typedef struct Categoria
{
    int codigocat;
    char nome[100];
    Livro *livros;
    struct Categoria *next;
} Categoria;

typedef struct Biblioteca
{
    Categoria *categorias;
} Biblioteca;

void mostrarbiblioteca(Biblioteca biblioteca);
Categoria *verificaCategoria(Biblioteca biblioteca, const char *nomeCategoria);
Livro *criarLivro(char titulo[], char autor[], int ano);
Categoria *criarCategoria(char nome[]);
void inserirLivro(Categoria *categoria, Livro *novoLivro);
void listarLivros(Categoria *categoria);
Livro *procurarLivro(Categoria *categoria, char titulo[]);
void eliminarLivro(Categoria *categoria, int codigo);
void atualizarLivro(Livro *livro, char titulo[], char autor[], int ano);
char *pedirString(const char *mensagem);
int pedirInteiro(const char *mensagem);
int gerarcodigolivro(void);
int gerarcodigocat(void);



int main()
{
    Biblioteca biblioteca;
    biblioteca.categorias = NULL;

    Categoria *categoria1 = criarCategoria("Ficcao");
    Categoria *categoria2 = criarCategoria("NaoFiccao");

    biblioteca.categorias = categoria1;
    categoria1->next = categoria2;

    inserirLivro(categoria1, criarLivro("Harry Potter", "J.K. Rowling", 1997));
    inserirLivro(categoria1, criarLivro("Senhor dos Aneis", "J.R.R. Tolkien", 1954));
    inserirLivro(categoria2, criarLivro("Sapiens", "Yuval Noah Harari", 2011));
    inserirLivro(categoria2, criarLivro("Cosmos", "Carl Sagan", 1980));

    int escolha;
    char titulo[100];
    int codigo, ano;
    char autor[100];
    char categoria[100];

    do

    {
        printf("\nMenu:\n");
        printf("1. Mostrar biblioteca\n");
        printf("2. Listar livros numa categoria\n");
        printf("3. Criar categoria\n");
        printf("4. Adicionar livro\n");
        printf("5. Procurar um livro por titulo\n");
        printf("6. Atualizar informacoes de um livro\n");
        printf("7. Eliminar um livro\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
        mostrarbiblioteca(biblioteca);
        case 2:
            strcpy(titulo, pedirString("Introduza o nome da categoria: "));
            Categoria *cat = biblioteca.categorias;
            while (cat != NULL)
            {
                if (strcmp(cat->nome, titulo) == 0)
                {
                    listarLivros(cat);
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Categoria nao encontrada!\n");
            }
            break;

        case 3:
            strcpy(titulo, pedirString("Introduza o nome da categoria: "));
            Categoria *categoriaExistente = verificaCategoria(biblioteca, titulo);
            if (categoriaExistente != NULL)
            {
                printf("Categoria já existe!\n");
            }
            else
            {
                criarCategoria(titulo);
                printf("Categoria criada com sucesso!\n");
            }
            break;

        case 4:
            strcpy(titulo, pedirString("Introduza o titulo do livro: "));
            strcpy(autor, pedirString("Introduza o nome do autor: "));
            ano = pedirInteiro("Introduza o ano do livro: ");
            strcpy(categoria, pedirString("Introduza a categoria: "));
            // aqui tem que ser melhorado para quando a categoria ja existe e quando é para criar a categoria
            Categoria *categoriaLivro = verificaCategoria(biblioteca, categoria);
            if (categoriaLivro == NULL)
            {
                // A categoria não existe, então vamos criá-la
                categoriaLivro = criarCategoria(categoria);
                // Adicionar a nova categoria à lista de categorias
                if (biblioteca.categorias == NULL)
                {
                    biblioteca.categorias = categoriaLivro;
                }
                else
                {
                    Categoria *temp = biblioteca.categorias;
                    while (temp->next != NULL)
                    {
                        temp = temp->next;
                    }
                    temp->next = categoriaLivro;
                }
            }
            // Agora, inserir o livro na categoria correta
            inserirLivro(categoriaLivro, criarLivro(titulo, autor, ano));

            break;

        case 5:
            strcpy(titulo, pedirString("Introduza o titulo do livro a procurar: "));
            cat = biblioteca.categorias;
            while (cat != NULL)
            {
                Livro *livro = procurarLivro(cat, titulo);
                if (livro != NULL)
                {
                    printf("Livro encontrado na categoria '%s':\n", cat->nome);
                    printf("Codigo: %d, Titulo: %s, Autor: %s, Ano: %d\n", livro->codigo, livro->titulo, livro->autor, livro->ano);
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Livro nao encontrado!\n");
            }
            break;

        case 6:
            strcpy(titulo, pedirString("Introduza o titulo do livro a atualizar: "));
            cat = biblioteca.categorias;
            while (cat != NULL)
            {
                Livro *livro = procurarLivro(cat, titulo);
                if (livro != NULL)
                {
                    strcpy(titulo, pedirString("Introduza o novo titulo: "));
                    strcpy(autor, pedirString("Introduza o novo autor: "));
                    ano = pedirInteiro("Introduza o novo ano: ");
                    atualizarLivro(livro, titulo, autor, ano);
                    printf("Informacoes do livro atualizadas com sucesso!\n");
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Livro nao encontrado!\n");
            }
            break;

        case 7:
            strcpy(titulo, pedirString("Introduza o nome da categoria: "));
            cat = biblioteca.categorias;
            while (cat != NULL)
            {
                if (strcmp(cat->nome, titulo) == 0)
                {
                    codigo = pedirInteiro("Introduza o codigo do livro a eliminar: ");
                    eliminarLivro(cat, codigo);
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Categoria nao encontrada!\n");
            }
            break;
        }
    } while (escolha);

    return 0;
}

int controlocodigolivro = 0;
int gerarcodigolivro(void)
{
    return ++controlocodigolivro;
}

int controlocodigocat = 0;
int gerarcodigocat(void)
{
    return ++controlocodigocat;
}

char *pedirString(const char *mensagem)
{
    static char entrada[100];
    printf("%s", mensagem);
    scanf(" %s", entrada);
    return entrada;
}

int pedirInteiro(const char *mensagem)
{
    int entrada;
    printf("%s", mensagem);
    scanf("%d", &entrada);
    return entrada;
}


void mostrarbiblioteca(Biblioteca biblioteca) {
    Categoria *cat = biblioteca.categorias;
    while (cat != NULL) {
        printf("Categoria: %s\n", cat->nome);
        listarLivros(cat);
        cat = cat->next;
    }
}



Categoria *verificaCategoria(Biblioteca biblioteca, const char *nomeCategoria)
{
    Categoria *cat = biblioteca.categorias;
    while (cat != NULL)
    {
        if (strcmp(cat->nome, nomeCategoria) == 0)
        {
            return cat; // Categoria encontrada
        }
        cat = cat->next;
    }
    return NULL; // Categoria não encontrada
}

Categoria *criarCategoria(char nome[])
{
    Categoria *novaCategoria = (Categoria *)malloc(sizeof(Categoria));
    if (novaCategoria == NULL)
    {
        printf("Alocacao de memoria falhou!\n");
        exit(1);
    }
    strcpy(novaCategoria->nome, nome);
    novaCategoria->codigocat = gerarcodigocat();
    novaCategoria->livros = NULL;
    novaCategoria->next = NULL;
    return novaCategoria;
}

Livro *criarLivro(char titulo[], char autor[], int ano)
{
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (novoLivro == NULL)
    {
        printf("Alocacao de memoria falhou!\n");
        exit(1);
    }
    novoLivro->codigo = gerarcodigolivro();
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->ano = ano;
    novoLivro->next = NULL;
    return novoLivro;
}

void inserirLivro(Categoria *categoria, Livro *novoLivro)
{
    if (categoria->livros == NULL)
    {
        categoria->livros = novoLivro;
    }
    else
    {
        Livro *temp = categoria->livros;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = novoLivro;
    }
}

void listarLivros(Categoria *categoria)
{
    printf("Livros na categoria '%s':\n", categoria->nome);
    Livro *temp = categoria->livros;
    while (temp != NULL)
    {
        printf("Codigo: %d, Titulo: %s, Autor: %s, Ano: %d\n", temp->codigo, temp->titulo, temp->autor, temp->ano);
        temp = temp->next;
    }
}

Livro *procurarLivro(Categoria *categoria, char titulo[])
{
    Livro *temp = categoria->livros;
    while (temp != NULL)
    {
        if (strcmp(temp->titulo, titulo) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void eliminarLivro(Categoria *categoria, int codigo)
{
    Livro *temp = categoria->livros;
    Livro *prev = NULL;
    while (temp != NULL && temp->codigo != codigo)
    {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL)
    {
        printf("Livro nao encontrado!\n");
        return;
    }
    if (prev == NULL)
    {
        categoria->livros = temp->next;
    }
    else
    {
        prev->next = temp->next;
    }
    free(temp);
    printf("Livro com codigo %d eliminado com sucesso!\n", codigo);
}

void atualizarLivro(Livro *livro, char titulo[], char autor[], int ano)
{
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    livro->ano = ano;
}
