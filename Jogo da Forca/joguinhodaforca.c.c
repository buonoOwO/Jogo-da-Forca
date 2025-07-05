#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

char palavra_secreta[100];

// Função de abertura do jogo
void abertura_jogo() {
    printf("\n\n");
    printf("*************************************************\n");
    printf("********** Bem-vindo ao Jogo da Forca! **********\n");
    printf("*************************************************\n");
    printf("\n\n");
}

// Função para escolher o tema e a palavra secreta
void escolhe_tema(char *palavra_secreta) {
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
        case 0:
            escolhe_palavra("jogos.txt", palavra_secreta);
            break;
        case 1:
            escolhe_palavra("animais.txt", palavra_secreta);
            break;
        case 2:
            escolhe_palavra("comidas_bebidas.txt", palavra_secreta);
            break;
        case 3:
            escolhe_palavra("profissoes.txt", palavra_secreta);
            break;
        case 4:
            escolhe_palavra("paises_estados_cidades.txt", palavra_secreta);
            break;
        case 5:
            escolhe_palavra("personagens.txt", palavra_secreta);
            break;
        case 6:
            escolhe_palavra("filmes.txt", palavra_secreta);
            break;
        case 7:
            escolhe_palavra("corpo_humano.txt", palavra_secreta);
            break;
        case 8:
            escolhe_palavra("livros.txt", palavra_secreta);
            break;
        case 9:
            printf("\n( ╹ -╹)?\n");
            printf("Que pena... Não sabia que você desistia tão facilmente.\n")
            printf ("Volte quando estiver pronto para um desafio!\n\n");
            palavra_secreta[0] = '\0'; // palavra vazia
            return 1;
        default:
            printf("\nTema inválido. Por favor, tente de novo.\n\n");
            palavra_secreta[0] = '\0'; // palavra vazia também
            return;
    }
}

// Função para sortear uma palavra de um arquivo de acordo com o tema
void escolhe_palavra(const char *arquivo_desejado, char *palavra) {
    FILE *arquivo = fopen(arquivo_desejado, "r");

    if (arquivo == NULL) {
        printf("Arquivo não encontrado: %s\n", arquivo_desejado);
        palavra[0] = '\0';
        return;
    }

    int quantidade_palavras;
    fscanf(arquivo, "%d", &quantidade_palavras);

    srand(time(0));
    int posicao = rand() % quantidade_palavras;

    for (int i = 0; i <= posicao; i++) {
        fscanf(arquivo, "%s", palavra);
    }

    fclose(arquivo);
}

int main(void) {

    abertura_jogo();
    escolhe_tema(palavra_secreta);

    printf("Palavra escolhida: %s\n", palavra_secreta);

    return 0;
}
