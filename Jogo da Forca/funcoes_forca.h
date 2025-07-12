#define TAMANHO 35

void abertura_jogo();
void escolhe_tema();
void escolhe_palavra(const char* arquivo_desejado);
bool verifica_chute(char chute, int *tamanho);
void chuta(char palavra[], int *tamanho);
bool ja_chutou(char chute);
void desenha_forca();
void sublinha_palavra(char palavra[], int *tamanho);
bool enforcou();
bool ganhou(char palavra[]);
void limpar_terminal();
