#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes_forca.h"

char palavra_secreta[TAMANHO];
int chutes_errados = 0;
int tentativas = 6;

// Função de abertura do jogo
void abertura_jogo() {
    printf("\n\n");
    printf("*************************************************\n");
    printf("********** Bem-vindo ao Jogo da Forca! **********\n");
    printf("*************************************************\n");
    printf("\n\n");
}

// Função para escolher o tema do jogo
void escolhe_tema() {
    int opcao;
    char entrada[160];

    printf("Por favor, escolha qual tema você deseja jogar:\n\n");

    printf("0 - Jogos\n");
    printf("1 - Animais\n");
    printf("2 - Comidas e bebidas\n");
    printf("3 - Profissões\n");
    printf("4 - Países, estados e cidades\n");
    printf("5 - Personagens\n");
    printf("6 - Filmes\n");
    printf("7 - Corpo humano\n");
    printf("8 - Livros\n\n");
    printf("9 - Sair\n\n");

    fgets(entrada, sizeof entrada, stdin);
    sscanf(entrada, "%d", &opcao);

    switch (opcao) {
        case 0: escolhe_palavra("jogos.txt"); break;
        case 1: escolhe_palavra("animais.txt"); break;
        case 2: escolhe_palavra("comidas_bebidas.txt"); break;
        case 3: escolhe_palavra("profissoes.txt"); break;
        case 4: escolhe_palavra("paises_estados_cidades.txt"); break;
        case 5: escolhe_palavra("personagens.txt"); break;
        case 6: escolhe_palavra("filmes.txt"); break;
        case 7: escolhe_palavra("corpo_humano.txt"); break;
        case 8: escolhe_palavra("livros.txt"); break;
        case 9:
            printf("\n( ╹ -╹)?\n");
            printf("Que pena... Não sabia que você desistia fácil assim.\n");
            printf("Volte quando realmente quiser um desafio.\n\n");
            exit(0);
        default:
            printf("\nTema inválido, tente novamente.\n\n");
            escolhe_tema();
    }
}

// Função que escolhe a palavra secreta de um arquivo
void escolhe_palavra(const char* arquivo_desejado) {
    FILE* arquivo = fopen(arquivo_desejado, "r");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado.\n");
        exit(1);
    }

    int quantidade_palavras;
    fscanf(arquivo, "%d", &quantidade_palavras);

    srand(time(0));
    int palavra_aleatoria = rand() % quantidade_palavras;

    for (int i = 0; i <= palavra_aleatoria; i++) {
        fscanf(arquivo, "%s", palavra_secreta);
    }

    fclose(arquivo);
}

// Função que verifica se o chute está correto
bool verifica_chute(char chute) {
    for (int i = 0; i < strlen(palavra_secreta); i++) {
        if (chute == palavra_secreta[i]) {
            return true;
        }
    }

    chutes_errados++;
    return false;
}

// Função que trata os chutes do jogador
void chuta(char palavra[]) {
    char entrada[160];
    char chute;
    
    tentativas >= 0 ? printf("__________     \n"): printf("               \n");
    tentativas >= 0 ? printf(" |/      |     \n"): printf("               \n");
    tentativas >= 1 ? printf(" |             \n") printf(" |      (_)    \n");
    tentativas >= 2 ? printf(" |             \n") printf(" |      \\|/   \n");
    tentativas >= 3 ? printf(" |             \n") printf(" |       |     \n");
    tentativas >= 4 ? printf(" |             \n"); printf(" |      / \\   \n");
                      printf(" |             \n");
                      printf("_|___          \n");
    
    printf ("\nTentativas: %d", tentativas);

    printf("\nQual a letra?: ");
    fgets(entrada, sizeof entrada, stdin);
    sscanf(entrada, "%c", &chute);

    if (verifica_chute(chute)) {
        printf("Você acertou! A palavra tem a letra %c.\n", chute);
        for (int i = 0; i < strlen(palavra_secreta); i++) {
            if (palavra_secreta[i] == chute) {
                palavra[i] = chute;
            }
        }
    } else {
        tentativas = tentativas - 1;
        printf("Você errou... A palavra não tem a letra %c.\n", chute);
    }
}

// Exibe o estado atual da palavra com espaços
void sublinha_palavra(char palavra[]) {
    int tamanho = strlen(palavra_secreta);
    for (int i = 0; i < tamanho; i++) {
        palavra[i] = '_';
    }
    palavra[tamanho] = '\0';
}

// Verifica se o jogador foi enforcado
bool enforcou() {
    return chutes_errados >= 6;
}

// Verifica se o jogador ganhou
bool ganhou(char palavra[]) {
    return strcmp(palavra, palavra_secreta) == 0;
}

// Programa principal
int main(void) {
    char palavra[TAMANHO];

    abertura_jogo();
    escolhe_tema();
    sublinha_palavra(palavra);

    do {
        // Mostra o progresso da palavra
        printf("\nPalavra: ");
        for (int i = 0; i < strlen(palavra_secreta); i++) {
            printf("%c ", palavra[i]);
        }
        printf("\n");

        chuta(palavra);

    } while (!ganhou(palavra) && !enforcou());

    if (ganhou(palavra)) {
        printf("\nParabéns! Você acertou a palavra: %s\n", palavra_secreta);
    } else {
        printf("\nPuxa! Você foi enforcado. A palavra era: %s\n", palavra_secreta);
    }

    return 0;
}
