#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "funcoes_forca.h"

char palavra_secreta[TAMANHO];
int chutes_errados = 0;

// Função de abertura do jogo
void abertura_jogo (){
    printf ("\n\n");

    printf ("*************************************************\n");
    printf ("********** Bem-vindo ao Jogo da Forca! **********\n");
    printf ("*************************************************\n");

    printf ("\n\n");
}

//Função para escolher o tema do jogo
void escolhe_tema(){

    int opcao;
    char entrada[160];

    printf ("Por favor, escolha qual tema você deseja jogar:\n\n");

    printf ("0 - Jogos\n");
    printf ("1 - Animais\n");
    printf ("2 - Comidas e bebidas\n");
    printf ("3 - Profissões\n");
    printf ("4 - Países, estados e cidades\n");
    printf ("5 - Personagens\n");
    printf ("6 - Filmes\n");
    printf ("7 - Corpo humano\n");
    printf ("8 - Livros\n\n");
    printf ("9 - Sair\n\n");

    fgets (entrada, sizeof entrada, stdin);
    sscanf (entrada, "%d", &opcao);

    switch (opcao){

        case 0:
            escolhe_palavra("jogos.txt");
            break;

        case 1:
            escolhe_palavra("animais.txt");
            break;

        case 2:
            escolhe_palavra("comidas_bebidas.txt");
            break;

        case 3:
            escolhe_palavra("profissoes.txt");
            break;

        case 4:
            escolhe_palavra("paises_estados_cidades.txt");
            break;

        case 5:
            escolhe_palavra("personagens.txt");
            break;

        case 6:
            escolhe_palavra("filmes.txt");
            break;

        case 7:
            escolhe_palavra("corpo_humano.txt");
            break;

        case 8:
            escolhe_palavra("livros.txt");
            break;

        case 9:
            printf ("\n( ╹ -╹)?\n");
            printf ("Que pena... Não sabia que você desistia fácil assim.\n");
            printf ("Volte quando realmente querer um desafio.\n\n");
            break;

        default:
            printf ("\nTema inválido, tente novamente.\n\n");
            escolhe_tema();
    }
}

// Função para sortear uma palavra de um arquivo de acordo com o tema
void escolhe_palavra(const char* arquivo_desejado){

    FILE *arquivo = fopen(arquivo_desejado, "r");

    if (arquivo == NULL){
        printf ("Arquivo não encontrado.\n");
        exit(1);
    }

    int quantidade_palavras; //primeira linha do .txt informa a quantidade de palavras do arquivo

    fscanf (arquivo, "%d", &quantidade_palavras);

    srand (time(0));
    int palavra_aleatoria = rand() % quantidade_palavras;

    for (int i = 0; i <= palavra_aleatoria; i++){
        fscanf (arquivo, "%s", palavra_secreta);
    }

    fclose (arquivo);

}

// Função que trata dos chutes dados pelo jogador
void chuta(){
    char chute;
    char palavra [TAMANHO];
    char entrada [160];
    
    int tamanho = strlen(palavra_secreta);
    
    for (int i = 0; i < tamanho; i++){
        palavra[i] = '_';
        printf ("%c ", palavra[i]);
    }

    printf ("\nQual a letra?: ");
    fgets(entrada, sizeof entrada, stdin);
    sscanf (entrada, "%c", &chute);

    if (verifica_chute(chute)){
        printf ("Você acertou! A palavra tem a letra %c.\n", chute);
    } else {
        printf ("Você errou... A palavra não tem a letra %c.\n", chute);
    }
    
}

// Função que verifica se o chute está certo ou não
bool verifica_chute(char chute){
    for (int i = 0; i < strlen(palavra_secreta); i++){

        if (chute == palavra_secreta[i]){
            return true;

        }
    }
    
    chutes_errados++;
    return false;
}

//Função que verifica os erros do jogador
bool enforcou (){
    if (chutes_errados >= 6){
        return true;
    } else {
        return false;
    }
}

//Função que verifica os acertos do jogador
bool ganhou 

int main (void){

    abertura_jogo();
    escolhe_tema();
    
    do{

    chuta();
    
    } while (!ganhou() || !enforcou());

    printf ("\nPalavra escolhida: %s", palavra_secreta);

    return 0;
}

    return 0;
}
