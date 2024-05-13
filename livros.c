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
Livro *criarLivro(int condigo, char titulo[], char autor[], int ano);
Categoria *criarCategoria(char nome[]);
int inserirLivro(Categoria *categoria, Livro *novoLivro);
void listarLivros(Categoria *categoria);
Livro *procurarLivro(Categoria *categoria, int codigo);
int eliminarLivro(Categoria *categoria, int codigo);
int eliminarCategoria(Biblioteca *biblioteca, int codigocat);
int atualizarLivro(Livro *livro, char titulo[], char autor[], int ano, Categoria *novaCategoria, Biblioteca biblioteca);
char *pedirString(const char *mensagem);
int pedirInteiro(const char *mensagem);
int gerarcodigolivro(void);
int gerarcodigocat(void);
Categoria *verificacategoriaporcodigo(Biblioteca biblioteca, int codigocat);
void mostrarcategorias(Biblioteca biblioteca);
void mergeSort(LivroArray *livros, int esquerda, int direita);
void merge(LivroArray *livros, int esquerda, int meio, int direita);

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

    inserirLivro(categoria1, criarLivro(14, "Geronimo Stilton - O Fantasma do Metro", "Cristiano Ronaldo", 1997));
    inserirLivro(categoria1, criarLivro(77, "Os Lusiadas", "Freddie Mercurie", 1954));
    inserirLivro(categoria2, criarLivro(12, "O Principezinho", "The Weekend", 2011));
    inserirLivro(categoria2, criarLivro(24, "World of Warcraft", "Michael Jackson", 1980));

    int escolha;
    char titulo[100];
    int codigo, ano;
    char autor[100];
    char categoria[100];

    do
    {
        escolha = pedirInteiro("\nMenu:\n1. Mostrar biblioteca\n2. Listar livros numa categoria\n3. Criar categoria\n4. Adicionar livro\n5. Procurar um livro por titulo\n6. Atualizar informacoes de um livro\n7. Eliminar um livro\n8. Eliminar uma Categoria\n0. Sair\nEscolha: ");

        switch (escolha)
        {
        case 1:
            mostrarbiblioteca(biblioteca);
            break;
        case 2:
            mostrarcategorias(biblioteca);
            int codigocat;
            do
            {
                codigocat = pedirInteiro("Introduza o numero da categoria que procura: ");

            } while (codigocat < 1 || codigocat > controlocodigocat);

            Categoria *categoriaLivro = verificacategoriaporcodigo(biblioteca, codigocat);
            ;
            if (categoriaLivro == NULL)
            {
                printf("A categoria nao existe.\n");
            }
            else
            {
                printf("\nCategoria: %s\n\n", categoriaLivro->nome);
                listarLivros(categoriaLivro);
            }
            break;

        case 3:
            strcpy(titulo, pedirString("Introduza o nome da categoria: "));
            Categoria *categoriaExistente = verificaCategoria(biblioteca, titulo);
            if (categoriaExistente != NULL)
            {
                printf("Categoria ja existe!\n");
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
            codigo = pedirInteiro("Insira o codigo ISBN do livro: ");
            strcpy(titulo, pedirString("Introduza o titulo do livro: "));
            strcpy(autor, pedirString("Introduza o nome do autor: "));
            ano = pedirInteiro("Introduza o ano do livro: ");
            mostrarcategorias(biblioteca);

            do
            {
                codigocat = pedirInteiro("Introduza o numero da sua categoria: ");

            } while (codigocat < 1 || codigocat > controlocodigocat);

            categoriaLivro = verificacategoriaporcodigo(biblioteca, codigocat);
            ;
            if (categoriaLivro == NULL)
            {
                printf("A categoria nao existe, deve ser criada antes de adicionar livros nela");
            }
            else
            {
                if (inserirLivro(categoriaLivro, criarLivro(codigo, titulo, autor, ano)))
                {
                    printf("Livro criado com sucesso!\n");
                }
                else
                    printf("Ja existe um livro com esse codigo ISBN!\n");
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
                    printf("Categoria: %s, Título: %s, Autor: %s, Ano: %d\n", categoriaNome, livro->titulo, livro->autor, livro->ano);
                }
                char sortChoice;
                do
                {
                    sortChoice = pedirString("Deseja ordenar os resultados por ano? (S/N) ")[0];
                } while (sortChoice != 'n' && sortChoice != 'N' && sortChoice != 's' && sortChoice != 'S');

                if (sortChoice == 'S' || sortChoice == 's')
                {
                    // Ordenar os livros por ano usando merge sort
                    mergeSort(livrosEncontrados, 0, livrosEncontrados->count - 1);
                    for (int i = 0; i < livrosEncontrados->count; i++)
                    {
                        Livro *livro = livrosEncontrados->livros[i];
                        char *categoriaNome = livrosEncontrados->categorias[i];
                        printf("Categoria: %s, Titulo: %s, Autor: %s, Ano: %d\n", categoriaNome, livro->titulo, livro->autor, livro->ano);
                        free(categoriaNome); // Liberar o nome da categoria duplicada
                    }
                }
            }
            else
            {
                printf("Nenhum livro encontrado com o titulo '%s'.\n", titulo);
            }
            free(livrosEncontrados);
            break;

        case 6:
            do
            {
                codigo = pedirInteiro("Introduza o codigo ISBN do livro a atualizar: ");
            } while (codigo <= 0 || codigo > controlocodigolivro);

            Categoria *cat = biblioteca.categorias;

            while (cat != NULL)
            {
                Livro *livro = procurarLivro(cat, codigo);
                if (livro != NULL)
                {
                    // Atualizar informações do livro
                    strcpy(titulo, pedirString("Introduza o novo titulo: "));
                    strcpy(autor, pedirString("Introduza o novo autor: "));
                    ano = pedirInteiro("Introduza o novo ano: ");
                    mostrarcategorias(biblioteca);

                    do
                    {
                        codigocat = pedirInteiro("Introduza o numero da nova categoria: ");

                    } while (codigocat < 1 || codigocat > controlocodigocat);

                    Categoria *novaCategoria = verificacategoriaporcodigo(biblioteca, codigocat);
                    if (novaCategoria == NULL)
                    {
                        printf("A categoria nao existe");
                    }
                    else
                    {
                        if (atualizarLivro(livro, titulo, autor, ano, novaCategoria, biblioteca))
                        {
                            printf("Livro atualizado com sucesso!\n");
                        }
                        else
                            printf("Nao foi possivel atualizar o livro");
                    }
                    break; // Sair do loop após atualizar o livro
                }
                cat = cat->prox;
            }
            break;

        case 7:

            do
            {
                codigo = pedirInteiro("Introduza o codigo do livro a eliminar: ");
            } while (codigo <= 0);

            cat = biblioteca.categorias;

            while (cat != NULL)
            {
                Livro *livro = procurarLivro(cat, codigo);
                if (livro != NULL)
                {
                    if (eliminarLivro(cat, codigo))
                    {
                    printf("Livro %d eliminado com sucesso!\n", codigo);
                   
                    }
                    else
                    {
                    printf("Nao foi possivel eliminar o livro");
                    }
                    break;
                    
                }
                cat = cat->prox;
            }
            printf("Livro não encontrado");
            break;

        case 8:
            /*  int codigocat; */
            mostrarcategorias(biblioteca);
            do
            {
                codigocat = pedirInteiro("Introduza o numero da categoria que deseja eliminar: ");
            } while (codigocat < 1 || codigocat > controlocodigocat);

            if (eliminarCategoria(&biblioteca, codigocat))
            {
                printf("Categoria eliminada. \n");
            }
            else
                printf("Categoria nao eliminada. \n");

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

int gerarcodigocat(void)
{
    return ++controlocodigocat;
}

char *pedirString(const char *mensagem)
{
    static char entrada[100];

    printf("%s", mensagem);

    scanf("%[^\n]", entrada); // acaba de ler a mensagem quando deteta um \n
    while (getchar() != '\n')
        ;

    return entrada;
}

int pedirInteiro(const char *mensagem)
{
    int entrada;
    printf("%s", mensagem);
    scanf("%d", &entrada);
    while (getchar() != '\n')
        ;
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

Livro *criarLivro(int codigo, char titulo[], char autor[], int ano)
{
    Livro *novoLivro = (Livro *)malloc(sizeof(Livro));
    if (novoLivro == NULL)
    {
        printf("Alocacao de memoria falhou!\n");
        exit(1);
    }
    novoLivro->codigo = codigo;
    strcpy(novoLivro->titulo, titulo);
    strcpy(novoLivro->autor, autor);
    novoLivro->ano = ano;
    novoLivro->prox = NULL;

    return novoLivro;
}

int inserirLivro(Categoria *categoria, Livro *novoLivro)
{

    if (categoria->livros == NULL)
    {
        categoria->livros = novoLivro;
        ++controlocodigolivro;
        return 1; // Livro inserido com sucesso
    }
    else
    {
        if (procurarLivro(categoria, novoLivro->codigo) != NULL)
        {

            return 0; // ERRO ao inserir o livro
        }
        Livro *temp = categoria->livros;
        while (temp->prox != NULL)
        {
            temp = temp->prox;
        }
        temp->prox = novoLivro;
        ++controlocodigolivro;
        return 1; // Livro inserido com sucesso
    }
    return 0; // ERRO ao inserir o livro
}

void listarLivros(Categoria *categoria)
{
    if (categoria->livros == NULL)
    {
        printf("Categoria sem livros\n");
        return; // Retorna se não houver livros na categoria
    }

    Livro *temp = categoria->livros;
    while (temp != NULL)
    {
        printf("Codigo ISBN: %d, Titulo: %s, Autor: %s, Ano: %d\n", temp->codigo, temp->titulo, temp->autor, temp->ano);
        temp = temp->prox;
    }
}

Livro *procurarLivro(Categoria *categoria, int codigo)
{
    Livro *temp = categoria->livros;
    while (temp != NULL)
    {
        if (temp->codigo == codigo)
        {
            return temp;
        }
        temp = temp->prox;
    }
    return NULL;
}

int eliminarLivro(Categoria *categoria, int codigo)
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

        return 0;
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
    controlocodigolivro--;
    return 1;
    // printf("Livro com código %d eliminado com sucesso!\n", codigo);
}

int eliminarCategoria(Biblioteca *biblioteca, int codigocat)
{
    Categoria *atual = biblioteca->categorias;
    Categoria *anterior = NULL;

    // Localizar a categoria a ser eliminada
    while (atual != NULL && atual->codigocat != codigocat)
    {
        anterior = atual;
        atual = atual->prox;
    }

    if (atual == NULL)
    {
        return 0;
    }

    // Remover a categoria da lista de categorias
    if (anterior == NULL)
    {
        biblioteca->categorias = atual->prox;
    }
    else
    {
        anterior->prox = atual->prox;
    }

    // Liberar a memória alocada para os livros da categoria
    Livro *livroAtual = atual->livros;
    while (livroAtual != NULL)
    {
        Livro *temp = livroAtual;
        livroAtual = livroAtual->prox;
        free(temp);
    }

    // Liberar a memória alocada para a categoria
    free(atual);
    controlocodigocat--;

    return 1;
}

int atualizarLivro(Livro *livro, char titulo[], char autor[], int ano, Categoria *novaCategoria, Biblioteca biblioteca)
{
    // Atualizar as informações do livro
    strcpy(livro->titulo, titulo);
    strcpy(livro->autor, autor);
    livro->ano = ano;

    // Remover o livro da sua categoria atual
    Categoria *antigaCategoria = NULL;
    Categoria *cat = biblioteca.categorias;
    while (cat != NULL)
    {
        Livro *temp = cat->livros;
        Livro *prev = NULL;
        while (temp != NULL)
        {
            if (temp->codigo == livro->codigo)
            {
                // Livro encontrado nesta categoria
                if (prev == NULL)
                {
                    // Livro é o primeiro da lista
                    cat->livros = temp->prox;
                }
                else
                {
                    prev->prox = temp->prox;
                }
                antigaCategoria = cat;
                break;
            }
            prev = temp;
            temp = temp->prox;
        }
        if (antigaCategoria != NULL)
        {
            break;
        }
        cat = cat->prox;
    }

    // Atribuir o livro à nova categoria
    if (antigaCategoria != NULL)
    {
        livro->prox = novaCategoria->livros;
        novaCategoria->livros = livro;
        return 1; // Livro atualizado e reatribuído com sucesso
    }
    else
    {
        return 0; // Livro não encontrado ou não foi possível atualizar
    }
}
LivroArray *procurarLivrosPorTitulo(Biblioteca biblioteca, const char *titulo)
{
    LivroArray *result = (LivroArray *)malloc(sizeof(LivroArray));
    if (result == NULL)
    {
        printf("Erro de alocacao de memoria.\n");
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
                // Aumentar o tamanho dos arrays
                result->livros = realloc(result->livros, (result->count + 1) * sizeof(Livro *));
                result->categorias = realloc(result->categorias, (result->count + 1) * sizeof(char *));
                if (result->livros == NULL || result->categorias == NULL)
                {
                    printf("Erro de alocacao de memoria.\n");
                    exit(0);
                }
                // Armazenar o ponteiro do livro correspondente e o nome da categoria
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

// Função para mesclar dois subarrays de livros em ordem crescente de ano de publicação
void merge(LivroArray *livros, int esquerda, int meio, int direita)
{
    int indiceEsquerda = 0, indiceDireita = 0, indiceMerged = esquerda;
    int tamanhoEsquerda = meio - esquerda + 1;
    int tamanhoDireita = direita - meio;

    // Arrays temporários para armazenar os subarrays esquerdo e direito
    Livro *subArrayEsquerdo[tamanhoEsquerda];
    Livro *subArrayDireito[tamanhoDireita];
    char *categoriasEsquerda[tamanhoEsquerda];
    char *categoriasDireita[tamanhoDireita];

    // Copiar dados para os arrays temporários
    for (int i = 0; i < tamanhoEsquerda; i++)
    {
        subArrayEsquerdo[i] = livros->livros[esquerda + i];
        categoriasEsquerda[i] = livros->categorias[esquerda + i];
    }
    for (int j = 0; j < tamanhoDireita; j++)
    {
        subArrayDireito[j] = livros->livros[meio + 1 + j];
        categoriasDireita[j] = livros->categorias[meio + 1 + j];
    }

    // Mesclar os arrays temporários de volta para livros
    while (indiceEsquerda < tamanhoEsquerda && indiceDireita < tamanhoDireita)
    {
        if (subArrayEsquerdo[indiceEsquerda]->ano <= subArrayDireito[indiceDireita]->ano)
        {
            livros->livros[indiceMerged] = subArrayEsquerdo[indiceEsquerda];
            livros->categorias[indiceMerged] = categoriasEsquerda[indiceEsquerda];
            indiceEsquerda++;
        }
        else
        {
            livros->livros[indiceMerged] = subArrayDireito[indiceDireita];
            livros->categorias[indiceMerged] = categoriasDireita[indiceDireita];
            indiceDireita++;
        }
        indiceMerged++;
    }

    // Copiar os elementos restantes do subarray esquerdo, se houver
    while (indiceEsquerda < tamanhoEsquerda)
    {
        livros->livros[indiceMerged] = subArrayEsquerdo[indiceEsquerda];
        livros->categorias[indiceMerged] = categoriasEsquerda[indiceEsquerda];
        indiceEsquerda++;
        indiceMerged++;
    }

    // Copiar os elementos restantes do subarray direito, se

    while (indiceDireita < tamanhoDireita)
    {
        livros->livros[indiceMerged] = subArrayDireito[indiceDireita];
        livros->categorias[indiceMerged] = categoriasDireita[indiceDireita];
        indiceDireita++;
        indiceMerged++;
    }
}

// Função principal para executar o algoritmo de ordenação
void mergeSort(LivroArray *livros, int esquerda, int direita)
{
    if (esquerda < direita)
    {
        int meio = esquerda + (direita - esquerda) / 2;

        // Classificar a primeira metade
        mergeSort(livros, esquerda, meio);
        // Classificar a segunda metade
        mergeSort(livros, meio + 1, direita);

        // Mesclar as duas metades classificadas
        merge(livros, esquerda, meio, direita);
    }
}