/*

DESCRIÇÃO:Esse jogo da forca consiste em um desafio onde o jogador 
deve adivinhar uma palavra escondida,a cada erro, uma parte do 
desenho da forca é montada.

REQUER:Que o jogador selecione o tema e adivinhar a palavra antes que o 
desenho da forca seja completado.

ASSEGURA:O jogo verifica se cada jogada houve vitória ou derrota

*/

#include <stdio.h>
#include <ctype.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes_forca.h"

char palavra_secreta[TAMANHO];
int chutes_errados = 0;
int tentativas = 6;
int qtde_chutes = 0;
char registra_letra[26];

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
    printf("8 - Cores\n\n");
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
        case 8: escolhe_palavra("cores.txt"); break;
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
    chute = tolower(chute); //vai converter para minúsculo
    
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
    
        desenha_forca();
        
        printf ("Letras chutadas:");
        
        for (int i = 0; i < qtde_chutes; i++){
            printf ("%c ", registra_letra[i]);
        }
    
        printf ("\nTentativas: %d", tentativas);

        printf("\nQual a letra?: ");
        fgets(entrada, sizeof entrada, stdin);
        sscanf(entrada, "%c", &chute);
                
        if (ja_chutou(chute)){
            printf ("Você já chutou essa letra antes. Tente outra.");
            return; // para evitar o excesso de if e else
        } 
        
        registra_letra[qtde_chutes] = chute;
        
        qtde_chutes++;

        if (verifica_chute(chute)) {
            
            chute = tolower(chute);
            
            printf("\nVocê acertou! A palavra tem a letra %c.\n", chute);
            for (int i = 0; i < strlen(palavra_secreta); i++) {
                if (palavra_secreta[i] == chute) {
                    palavra[i] = chute;
                }
            }
        } else {
            tentativas = tentativas - 1;
            printf("\nVocê errou... A palavra não tem a letra %c.\n", chute);
        
            if (tentativas == 0){
                desenha_forca();
            }
        }
    }

// Função que verifica se a letra já foi chutada antes
bool ja_chutou(char chute) {
    chute = tolower(chute);
    
    for (int i = 0; i < qtde_chutes; i++) {
        if (tolower(registra_letra[i]) == chute) {
            return true;
        }
    }
    return false;
}

// Função que ilustra a forca
void desenha_forca(){
    printf("__________       \n"); 
    printf(" |/      |       \n"); 
    printf(" |      %c%c%c   \n", (tentativas <=  5?'(':' '), (tentativas <= 5?'_':' '), (tentativas <= 5?')':' '));
    printf(" |      %c%c%c   \n", (tentativas <= 3? '\\': ' '), (tentativas <= 4? '|':' '), (tentativas <= 2? '/':' '));
    printf(" |       %c      \n", (tentativas <= 4? '|':' '));
    printf(" |      %c %c    \n", (tentativas <= 1? '/':' '), (tentativas == 0? '\\':' '));
    printf(" |               \n");
    printf("_|___            \n");
    
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

//Função que limpa o terminal para evitar a poluição visual quando necessário
void limpar_terminal(){
    #ifdef _WIN32
        system("cls");
    #else
        system ("clear");
    #endif
}

int main(void) {
    char palavra[TAMANHO];

    abertura_jogo();
    escolhe_tema();
    limpar_terminal();
    
    sublinha_palavra(palavra);
    
    // Mostra o progresso da palavra
    do {
        limpar_terminal();
        
        printf("\nPalavra: ");
        for (int i = 0; i < strlen(palavra_secreta); i++) {
            printf("%c ", palavra[i]);
        }
        printf("\n");

        chuta(palavra);

    } while (!ganhou(palavra) && !enforcou());

    if (ganhou(palavra)) {
        printf("\nParabéns! Você acertou a palavra: %s\n", palavra_secreta);
        printf ("Você é um bom jogador! Deveria tentar novamente.\n");
    } else {
        printf("\nPuxa! Você foi enforcado. A palavra era: %s\n", palavra_secreta);
        printf ("Tente novamente, tenho certeza que você sairá melhor na próxima partida.\n");
    }

    return 0;
}
