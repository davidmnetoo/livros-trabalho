#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Estrutura para representar um livro
typedef struct Livro
{
    int codigo;
    char titulo[100];
    char autor[100];
    int ano;
    struct Livro *next;
} Livro;

// Estrutura para representar uma categoria
typedef struct Categoria
{
    char nome[100];
    Livro *livros;
    struct Categoria *next;
} Categoria;

// Estrutura para representar a biblioteca
typedef struct Biblioteca
{
    Categoria *categorias;
} Biblioteca;

// Função para criar um novo livro
Livro *criarLivro(int codigo, char titulo[], char autor[], int ano)
{
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (novoLivro == NULL)
    {
        printf("Alocação de memória falhou!\n");
        exit(1);
    }
    novoLivro->codigo = codigo;
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->ano = ano;
    novoLivro->next = NULL;
    return novoLivro;
}

// Função para criar uma nova categoria
Categoria *criarCategoria(char nome[])
{
    Categoria *novaCategoria = (Categoria *)malloc(sizeof(Categoria));
    if (novaCategoria == NULL)
    {
        printf("Alocação de memória falhou!\n");
        exit(1);
    }
    strcpy(novaCategoria->nome, nome);
    novaCategoria->livros = NULL;
    novaCategoria->next = NULL;
    return novaCategoria;
}

// Função para inserir um livro numa categoria
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

// Função para listar todos os livros numa categoria
void listarLivros(Categoria *categoria)
{
    printf("Livros na categoria '%s':\n", categoria->nome);
    Livro *temp = categoria->livros;
    while (temp != NULL)
    {
        printf("Código: %d, Título: %s, Autor: %s, Ano: %d\n", temp->codigo, temp->titulo, temp->autor, temp->ano);
        temp = temp->next;
    }
}

// Função para procurar um livro pelo título numa categoria (pesquisa linear)
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

// Função para eliminar um livro pelo código de uma categoria
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
        printf("Livro não encontrado!\n");
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
    printf("Livro com código %d eliminado com sucesso!\n", codigo);
}

// Função para atualizar informações de um livro
void atualizarLivro(Livro *livro, char titulo[], char autor[], int ano)
{
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    livro->ano = ano;
}

int main()
{
    // Criar uma biblioteca
    Biblioteca biblioteca;
    biblioteca.categorias = NULL;

    // Criar categorias
    Categoria *categoria1 = criarCategoria("Ficção");
    Categoria *categoria2 = criarCategoria("Não Ficção");

    // Inserir categorias na biblioteca
    biblioteca.categorias = categoria1;
    categoria1->next = categoria2;

    // Inserir livros nas categorias
    inserirLivro(categoria1, criarLivro(1, "Harry Potter", "J.K. Rowling", 1997));
    inserirLivro(categoria1, criarLivro(2, "Senhor dos Anéis", "J.R.R. Tolkien", 1954));
    inserirLivro(categoria2, criarLivro(3, "Sapiens", "Yuval Noah Harari", 2011));
    inserirLivro(categoria2, criarLivro(4, "Cosmos", "Carl Sagan", 1980));

    int escolha;
    char titulo[100];
    int codigo, ano;
    char autor[100];

    do
    {
        printf("\nMenu:\n");
        printf("1. Listar livros numa categoria\n");
        printf("2. Criar categoria\n");
        printf("3. Adicionar livro\n");
        printf("4. Procurar um livro\n");
        printf("5. Atualizar informações de um livro\n");
        printf("6. Eliminar um livro\n");

        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &escolha);

        switch (escolha)
        {
        case 1:
            printf("Introduza o nome da categoria: ");
            scanf("%s", titulo);
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
                printf("Categoria não encontrada!\n");
            }
            break;

            // criar categoria
        case #:
            char nome[100];
            printf("Introduza o nome da categoria: \n");
            scanf("%s", nome);
            criarCategoria(nome);
            break;

            // criar um livro
        case #:
            char nome[100];
            char categoria[100];
            int codigo;

            printf("Introduza o codigo do livro: \n");
            scanf("%d", codigo);
            printf("Introduza o nome do livro: \n");
            scanf("%s", nome);

            printf("selecione a categoria");
            scanf("%s", categoria);

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
                printf("Categoria não encontrada!\n");
            }
            break;

            inserirLivro(Categoria * categoria, Livro * novoLivro);
        criarLivro(int codigo, char *titulo, char *autor, int ano)

            // procurar um livro
            case #:
            printf("Introduza o título do livro a procurar: ");
            scanf("%s", titulo);
            cat = biblioteca.categorias;
            while (cat != NULL)
            {
                Livro *livro = procurarLivro(cat, titulo);
                if (livro != NULL)
                {
                    printf("Livro encontrado na categoria '%s':\n", cat->nome);
                    printf("Código: %d, Título: %s, Autor: %s, Ano: %d\n", livro->codigo, livro->titulo, livro->autor, livro->ano);
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Livro não encontrado!\n");
            }
            break;

        case 4:
            printf("Introduza o código do livro a atualizar: ");
            scanf("%d", &codigo);
            printf("Introduza o novo título: ");
            scanf("%s", titulo);
            printf("Introduza o novo autor: ");
            scanf("%s", autor);
            printf("Introduza o novo ano: ");
            scanf("%d", &ano);
            cat = biblioteca.categorias;
            while (cat != NULL)
            {
                Livro *livro = procurarLivro(cat, titulo);
                if (livro != NULL)
                {
                    atualizarLivro(livro, titulo, autor, ano);
                    printf("Informações do livro atualizadas com sucesso!\n");
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Livro não encontrado!\n");
            }
            break;

        case 5:
            printf("Introduza o nome da categoria: ");
            scanf("%s", titulo);
            cat = biblioteca.categorias;
            while (cat != NULL)
            {
                if (strcmp(cat->nome, titulo) == 0)
                {
                    printf("Introduza o código do livro a eliminar: ");
                    scanf("%d", &codigo);
                    eliminarLivro(cat, codigo);
                    break;
                }
                cat = cat->next;
            }
            if (cat == NULL)
            {
                printf("Categoria não encontrada!\n");
            }
            break;
        }
    } while (escolha);

    return 0;
}