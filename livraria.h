#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//structs

struct livro {
        char estilo[255], nome[255], autor[255], editora[255];
        int numero_pagina, ano_publicacao, foi_vendido;
};
typedef struct livro Livro;


//Prototipos das funções

//Lucas Agostinho
void add_livro(Livro biblioteca[], int posicao);
void show_livro(Livro biblioteca[], int posicao);
void show_all_livros(Livro biblioteca[], int quantidade_de_livros);

//Elano Silveira
void show_all_nome_livros(Livro biblioteca[], int quantidade_de_livros);
void show_list_estilo_livros(Livro biblioteca[], int quantidade_de_livros);
void comprar_livro(Livro biblioteca[], int posicao);

//Enivaldo Queiroz
void voltar_menu(Livro biblioteca[], int quantidade_de_livros);
void clone_biblioteca(Livro biblioteca[], Livro biblioteca_clone[], int quantidade_de_livros);
void plus_boutght(Livro biblioteca[], int quantidade_de_livros);

////Jholdy Damasceno
int ordena_livros_recursivamente(Livro biblioteca[], int quantidade_de_livros, int posicao, int contador);
Livro downcase_all_string(Livro biblioteca);
void ordenar_mais_novos(Livro biblioteca[], int quantidade_de_livros);
void ordenar_mais_antigos(Livro biblioteca[], int quantidade_de_livros);
void ordenar_numero_de_paginas(Livro biblioteca[], int quantidade_de_livros);
void ordenar_alf(Livro biblioteca[], int quantidade_de_livros);
void menu(Livro biblioteca[], int quantidade_de_livros);


//Função

//Lucas Agostinho
void add_livro(Livro biblioteca[], int posicao){
        system("clear");
        printf("\n\nCadastro Livro %i\n", posicao + 1);
        printf("Nome: ");
        gets(biblioteca[posicao].nome);
        printf("Autor: ");
        gets(biblioteca[posicao].autor);
        printf("Editora: ");
        gets(biblioteca[posicao].editora);
        printf("Estilo: ");
        gets(biblioteca[posicao].estilo);
        biblioteca[posicao] = downcase_all_string(biblioteca[posicao]);
        biblioteca[posicao].foi_vendido = 0;
        printf("Número de paginas: ");
        scanf("%i", &biblioteca[posicao].numero_pagina);
        fflush(stdin);
        __fpurge(stdin);
        printf("Ano publicação: ");
        scanf("%i", &biblioteca[posicao].ano_publicacao);
        system("clear");
        fflush(stdin);
        __fpurge(stdin);
}

void show_livro(Livro biblioteca[], int posicao) {
        printf("\n\nLivro %i\n", (posicao + 1));
        printf("Livro: %s\n", biblioteca[posicao].nome);
        printf("Autor: %s\n", biblioteca[posicao].autor);
        printf("Editora: %s\n", biblioteca[posicao].editora);
        printf("Estilo: %s\n", biblioteca[posicao].estilo);
        printf("Foram vendidos: %i\n", biblioteca[posicao].foi_vendido);
        printf("Número de paginas: %i\n", biblioteca[posicao].numero_pagina);
        printf("Ano publicação: %i\n", biblioteca[posicao].ano_publicacao);
}

void show_all_livros(Livro biblioteca[], int quantidade_de_livros) {
        for(int posicao = 0; posicao < quantidade_de_livros; posicao++) {
                show_livro(biblioteca, posicao);
        }
}

//Elano Silveira

void show_all_nome_livros(Livro biblioteca[], int quantidade_de_livros) {
        for(int posicao = 0; posicao < quantidade_de_livros; posicao++) {
                printf("\nLivro %i\n", (posicao + 1));
                printf("Nome do Livro: %s\n\n", biblioteca[posicao].nome);
        }
}

void show_list_estilo_livros(Livro biblioteca[], int quantidade_de_livros){
        char estilo_selecionado[255];
        int i, contador = 0;
        printf("\n\nDeseja fazer uma busca por qual estilo?\n");
        gets(estilo_selecionado);
        for (int posicao = 0; posicao < 255; posicao++) {
          estilo_selecionado[posicao] = tolower(estilo_selecionado[posicao]);
        }
        for (int posicao = 0; posicao < quantidade_de_livros; posicao++) {
                if (strcmp(estilo_selecionado, biblioteca[posicao].estilo) == 0 ) {
                        show_livro(biblioteca, posicao);
                        contador++;
                }
        }
        if (contador == 0 ) {
                printf("\n\nNão tem livro com esse estilo na biblioteca!");
        }
}

void comprar_livro(Livro biblioteca[], int posicao) {
        biblioteca[posicao].foi_vendido++;
        printf("Você comprou o livro %s, obrigado por sua compra!\n", biblioteca[posicao].nome);
}

//Enivaldo Queiroz
void voltar_menu(Livro biblioteca[], int quantidade_de_livros) {
        int voltar_para_o_menu = 1;
        printf("\n\nDeseja voltar para o menu? \n");
        printf("Digite: 1 - sim, 2 - não. \n");
        scanf("%i", &voltar_para_o_menu);
        fflush(stdin);
        __fpurge(stdin);
        if (voltar_para_o_menu == 1) {
                system("clear");
                menu(biblioteca, quantidade_de_livros);
        }else{
                printf("Até mais tarde!\n");
        }
}

void clone_biblioteca(Livro biblioteca[], Livro biblioteca_clone[], int quantidade_de_livros){
        for (int posicao = 0; posicao < quantidade_de_livros; posicao++) {
                strcpy(biblioteca_clone[posicao].nome, biblioteca[posicao].nome);
                strcpy(biblioteca_clone[posicao].autor, biblioteca[posicao].autor);
                strcpy(biblioteca_clone[posicao].estilo, biblioteca[posicao].estilo);
                strcpy(biblioteca_clone[posicao].editora, biblioteca[posicao].editora);
                biblioteca_clone[posicao].numero_pagina = biblioteca[posicao].numero_pagina;
                biblioteca_clone[posicao].ano_publicacao = biblioteca[posicao].ano_publicacao;
                biblioteca_clone[posicao].foi_vendido = biblioteca[posicao].foi_vendido;
        }
}

void plus_boutght(Livro biblioteca[], int quantidade_de_livros){
        Livro biblioteca_aux, biblioteca_clone[quantidade_de_livros];
        clone_biblioteca(biblioteca, biblioteca_clone, quantidade_de_livros);
        for (int posicao_atual = 0; posicao_atual < quantidade_de_livros; posicao_atual++) {
                for (int posicao_proximo = posicao_atual + 1; posicao_proximo < quantidade_de_livros; posicao_proximo++) {
                        if (biblioteca_clone[posicao_atual].foi_vendido < biblioteca_clone[posicao_proximo].foi_vendido) {
                                biblioteca_aux = biblioteca_clone[posicao_atual];
                                biblioteca_clone[posicao_atual] = biblioteca_clone[posicao_proximo];
                                biblioteca_clone[posicao_proximo]  = biblioteca_aux;
                        }
                }
        }
        show_all_livros(biblioteca_clone, quantidade_de_livros);
}

//Jholdy Damasceno

void ordenar_mais_novos(Livro biblioteca[], int quantidade_de_livros){
        Livro biblioteca_aux, biblioteca_clone[quantidade_de_livros];
        clone_biblioteca(biblioteca, biblioteca_clone, quantidade_de_livros);
        for (int posicao_atual = 0; posicao_atual < quantidade_de_livros; posicao_atual++) {
                for (int posicao_proximo = posicao_atual + 1; posicao_proximo < quantidade_de_livros; posicao_proximo++) {
                        if (biblioteca_clone[posicao_atual].ano_publicacao < biblioteca_clone[posicao_proximo].ano_publicacao) {
                                biblioteca_aux = biblioteca_clone[posicao_atual];
                                biblioteca_clone[posicao_atual] = biblioteca_clone[posicao_proximo];
                                biblioteca_clone[posicao_proximo]  = biblioteca_aux;
                        }
                }
        }
        show_all_livros(biblioteca_clone, quantidade_de_livros);
}

void ordenar_mais_antigos(Livro biblioteca[], int quantidade_de_livros){
        Livro biblioteca_aux, biblioteca_clone[quantidade_de_livros];
        clone_biblioteca(biblioteca, biblioteca_clone, quantidade_de_livros);
        for (int posicao_atual = 0; posicao_atual < quantidade_de_livros; posicao_atual++) {
                for (int posicao_proximo = posicao_atual + 1; posicao_proximo < quantidade_de_livros; posicao_proximo++) {
                        if (biblioteca_clone[posicao_atual].ano_publicacao > biblioteca_clone[posicao_proximo].ano_publicacao) {
                                biblioteca_aux = biblioteca_clone[posicao_atual];
                                biblioteca_clone[posicao_atual] = biblioteca_clone[posicao_proximo];
                                biblioteca_clone[posicao_proximo]  = biblioteca_aux;
                        }
                }
        }
        show_all_livros(biblioteca_clone, quantidade_de_livros);
}

void ordenar_numero_de_paginas(Livro biblioteca[], int quantidade_de_livros){
        Livro biblioteca_aux, biblioteca_clone[quantidade_de_livros];
        clone_biblioteca(biblioteca, biblioteca_clone, quantidade_de_livros);
        for (int posicao_atual = 0; posicao_atual < quantidade_de_livros; posicao_atual++) {
                for (int posicao_proximo = posicao_atual + 1; posicao_proximo < quantidade_de_livros; posicao_proximo++) {
                        if (biblioteca_clone[posicao_atual].numero_pagina < biblioteca_clone[posicao_proximo].numero_pagina) {
                                biblioteca_aux = biblioteca_clone[posicao_atual];
                                biblioteca_clone[posicao_atual] = biblioteca_clone[posicao_proximo];
                                biblioteca_clone[posicao_proximo]  = biblioteca_aux;
                        }
                }
        }
        show_all_livros(biblioteca_clone, quantidade_de_livros);
}

void ordenar_alf(Livro biblioteca[], int quantidade_de_livros){
        Livro biblioteca_aux, biblioteca_clone[quantidade_de_livros];
        clone_biblioteca(biblioteca, biblioteca_clone, quantidade_de_livros);

        for (int posicao_atual = 0; posicao_atual < quantidade_de_livros; posicao_atual++) {
                for (int posicao_proximo = posicao_atual + 1; posicao_proximo < quantidade_de_livros; posicao_proximo++) {
                        if (strcmp(biblioteca_clone[posicao_proximo].nome, biblioteca_clone[posicao_atual].nome) < 0) {
                                biblioteca_aux = biblioteca_clone[posicao_atual];
                                biblioteca_clone[posicao_atual] = biblioteca_clone[posicao_proximo];
                                biblioteca_clone[posicao_proximo]  = biblioteca_aux;
                        }
                }
        }
        show_all_livros(biblioteca_clone, quantidade_de_livros);
}

int ordena_livros_recursivamente(Livro biblioteca[], int quantidade_de_livros, int posicao, int contador){
        Livro livro_aux;

        while (contador < quantidade_de_livros) {

                if ((biblioteca[posicao].ano_publicacao < biblioteca[(posicao+1)].ano_publicacao) && ((posicao+1) < 10)) {
                        livro_aux = biblioteca[posicao];
                        biblioteca[posicao] = biblioteca[(posicao+1)];
                        biblioteca[(posicao+1)] = livro_aux;
                }
                if ((posicao + 1) == quantidade_de_livros) {
                        posicao = 0;
                        return ordena_livros_recursivamente(biblioteca, quantidade_de_livros, posicao, contador+1);
                }
                return ordena_livros_recursivamente(biblioteca, quantidade_de_livros, posicao+1, contador);
        }
        show_all_livros(biblioteca, quantidade_de_livros);
        return 0;
}

Livro downcase_all_string(Livro biblioteca) {
  Livro biblioteca_aux;
  for (int posicao = 0; posicao < 255; posicao++) {
    biblioteca_aux.nome[posicao] = tolower(biblioteca.nome[posicao]);
    biblioteca_aux.estilo[posicao] = tolower(biblioteca.estilo[posicao]);
    biblioteca_aux.autor[posicao] = tolower(biblioteca.autor[posicao]);
    biblioteca_aux.editora[posicao] = tolower(biblioteca.editora[posicao]);
  }
  return biblioteca_aux;
}

void menu(Livro biblioteca[], int quantidade_de_livros) {
        int opcao = 0, p = 0, livro_escolhido = 0;
        Livro biblioteca_clone[quantidade_de_livros];

        printf("#################################################################################################################\n");
        printf("#                                                 LIVRARIA                                                      #\n");
        printf("#################################################################################################################\n");
        printf("################################### SELECIONE UM NÚMERO PARA SUA OPÇÃO ##########################################\n");
        printf("#################################################################################################################\n");
        printf("# 1 - Cadastrar livros | 2 - Buscar livro | 3 - mostar todos os livros | 4 - Comprar livro | 5 - Mais vendidos  #\n");
        printf("#################################################################################################################\n");
        printf("# 6 - Buscar por estilo | 7 - Publicações mais recentes | 8 - Publicações mais antigos | 9 - Ordenar por número #\n");
        printf("#################################################################################################################\n");
        printf("# de paginas | 10 - Ordem alfabetica | 11 - Publicações mais recentes recursivamente | 12 - Sair                #\n");
        printf("#################################################################################################################\n");
        scanf("%i", &opcao );
        fflush(stdin);
        __fpurge(stdin);

        switch (opcao) {
        case 1:
                for (int posicao = 0; posicao < quantidade_de_livros; posicao++) {
                        add_livro(biblioteca, posicao);
                }
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 2:
                show_all_nome_livros(biblioteca, quantidade_de_livros);
                printf("Informe a posição do seu livro na biblioteca: ");
                scanf("%i", &p);
                fflush(stdin);
                __fpurge(stdin);
                show_livro(biblioteca, (p - 1));
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 3:
                show_all_livros(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 4:
                show_all_livros(biblioteca, quantidade_de_livros);
                printf("\n\nQual o codigo do livro que você deseja comprar?\n");
                scanf("%i", &livro_escolhido);
                fflush(stdin);
                __fpurge(stdin);
                comprar_livro(biblioteca, (livro_escolhido - 1));
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 5:
                plus_boutght(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 6:
                show_list_estilo_livros(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 7:
                ordenar_mais_novos(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 8:
                ordenar_mais_antigos(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 9:
                ordenar_numero_de_paginas(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 10:
                ordenar_alf(biblioteca, quantidade_de_livros);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 11:
                clone_biblioteca(biblioteca, biblioteca_clone, quantidade_de_livros);
                ordena_livros_recursivamente(biblioteca_clone, quantidade_de_livros, 0, 0);
                voltar_menu(biblioteca, quantidade_de_livros);
                break;

        case 12:
                printf("Até mais tarde!\n");
                break;

        default:
                printf("Sua opção não esta no menu!\n");
                voltar_menu(biblioteca, quantidade_de_livros);
        }
}
