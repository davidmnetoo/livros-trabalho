#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Livro
{
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    struct Livro *prox;
} Livro;

typedef struct Categoria
{
    int codigocat;
    char nome[100];
    Livro *livros;
    struct Categoria *prox;
} Categoria;

typedef struct Biblioteca
{
    Categoria *categorias;
} Biblioteca;

typedef struct LivroArray
{
    Livro **livros;
    char **categorias;
    int count;
} LivroArray;

LivroArray *procurarLivrosPorTitulo(Biblioteca biblioteca, const char *titulo);
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
Categoria *verificacategoriaporcodigo(Biblioteca biblioteca, int codigocat);
void mostrarcategorias(Biblioteca biblioteca);

int controlocodigolivro = 0;
int controlocodigocat = 0;

int main()
{
    Biblioteca biblioteca;
    biblioteca.categorias = NULL;

    Categoria *categoria1 = criarCategoria("Ficcao");
    Categoria *categoria2 = criarCategoria("Nao Ficcao");

    biblioteca.categorias = categoria1;
    categoria1->prox = categoria2;

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
            break;
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
                cat = cat->prox;
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
                Categoria *novaCategoria = criarCategoria(titulo);
                if (biblioteca.categorias == NULL)
                {
                    biblioteca.categorias = novaCategoria;
                }
                else
                {
                    Categoria *temp = biblioteca.categorias;
                    while (temp->prox != NULL)
                    {
                        temp = temp->prox;
                    }
                    temp->prox = novaCategoria;
                }
                printf("Categoria criada com sucesso!\n");
            }
            break;

        case 4:
            strcpy(titulo, pedirString("Introduza o titulo do livro: "));
            strcpy(autor, pedirString("Introduza o nome do autor: "));
            ano = pedirInteiro("Introduza o ano do livro: ");
            mostrarcategorias(biblioteca);
            int codigocat;

            do
            {
                codigocat = pedirInteiro("Introduza o numero da sua categoria: ");

            } while (codigocat < 1 || codigocat > controlocodigocat);

            Categoria *categoriaLivro = verificacategoriaporcodigo(biblioteca, codigocat);
            ;
            if (categoriaLivro == NULL)
            {
                printf("A categoria não existe, deve ser criada antes de adicionar livros nela");
            }
            else
            {
                inserirLivro(categoriaLivro, criarLivro(titulo, autor, ano));
                printf("livro creado com sucesso!\n");
            }

            break;

        case 5:
            strcpy(titulo, pedirString("Introduza o titulo do livro a procurar: "));
            LivroArray *livrosEncontrados = procurarLivrosPorTitulo(biblioteca, titulo);
            if (livrosEncontrados->count > 0)
            {
                printf("Livros encontrados:\n");
                for (int i = 0; i < livrosEncontrados->count; i++)
                {
                    Livro *livro = livrosEncontrados->livros[i];
                    char *categoriaNome = livrosEncontrados->categorias[i];
                    printf("Categoria: %s, Titulo: %s, Autor: %s, Ano: %d\n", categoriaNome, livro->titulo, livro->autor, livro->ano);
                    free(categoriaNome); // Free the duplicated category name
                }
            }
            else
            {
                printf("Nenhum livro encontrado com o titulo '%s'.\n", titulo);
            }
            free(livrosEncontrados->livros);
            free(livrosEncontrados->categorias);
            free(livrosEncontrados);
            break;
            break;
        case 6:

            // trocar isto para atualizar por codigo
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
                    // tem que tambem ser possivel atualizar a categoria

                    printf("Informacoes do livro atualizadas com sucesso!\n");
                    break;
                }
                cat = cat->prox;
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
                cat = cat->prox;
            }
            if (cat == NULL)
            {
                printf("Categoria nao encontrada!\n");
            }
            break;

        case 0:
            printf("Encerrando o programa. Obrigado por usar a biblioteca!\n");
            break;

        default:
            printf("Opcao invalida. Por favor, escolha uma opcao valida.\n");
            break;
        }
    } while (escolha);

    return 0;
}

int gerarcodigolivro(void)
{
    return ++controlocodigolivro;
}

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

void mostrarbiblioteca(Biblioteca biblioteca)
{
    Categoria *cat = biblioteca.categorias;
    while (cat != NULL)
    {
        printf("\nCategoria: %s\n\n", cat->nome);
        listarLivros(cat);
        cat = cat->prox;
    }
}

void mostrarcategorias(Biblioteca biblioteca)
{
    Categoria *cat = biblioteca.categorias;
    while (cat != NULL)
    {
        printf("%i. Categoria: %s\n", cat->codigocat, cat->nome);
        cat = cat->prox;
    }
}

Categoria *verificacategoriaporcodigo(Biblioteca biblioteca, int codigo)
{
    Categoria *cat = biblioteca.categorias;
    while (cat != NULL)
    {
        if (cat->codigocat == codigo)
        {
            return cat;
        }
        cat = cat->prox;
    }
    return NULL; // Retorna NULL se a categoria não for encontrada
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
        cat = cat->prox;
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
    novaCategoria->prox = NULL;
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
    novoLivro->prox = NULL;
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
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novoLivro;
    }
}

void listarLivros(Categoria *categoria)
{
    Livro *temp = categoria->livros;
    while (temp != NULL)
    {
        printf("Codigo: %d, Titulo: %s, Autor: %s, Ano: %d\n", temp->codigo, temp->titulo, temp->autor, temp->ano);
        temp = temp->prox;
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
        temp = temp->prox;
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
        temp = temp->prox;
    }
    if (temp == NULL)
    {
        printf("Livro nao encontrado!\n");
        return;
    }
    if (prev == NULL)
    {
        categoria->livros = temp->prox;
    }
    else
    {
        prev->prox = temp->prox;
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

LivroArray *procurarLivrosPorTitulo(Biblioteca biblioteca, const char *titulo)
{
    LivroArray *result = (LivroArray *)malloc(sizeof(LivroArray));
    if (result == NULL)
    {
        printf("Erro de alocação de memória.\n");
        exit(EXIT_FAILURE);
    }
    result->livros = NULL;
    result->categorias = NULL;
    result->count = 0;

    Categoria *cat = biblioteca.categorias;
    while (cat != NULL)
    {
        Livro *livro = cat->livros;
        while (livro != NULL)
        {
            if (strcmp(livro->titulo, titulo) == 0)
            {
                // Increase the size of the arrays
                result->livros = realloc(result->livros, (result->count + 1) * sizeof(Livro *));
                result->categorias = realloc(result->categorias, (result->count + 1) * sizeof(char *));
                if (result->livros == NULL || result->categorias == NULL)
                {
                    printf("Erro de alocação de memória.\n");
                    exit(EXIT_FAILURE);
                }
                // Store the matching book pointer and its category name
                result->livros[result->count] = livro;
                result->categorias[result->count] = strdup(cat->nome);
                result->count++;
            }
            livro = livro->prox;
        }
        cat = cat->prox;
    }

    return result;
}