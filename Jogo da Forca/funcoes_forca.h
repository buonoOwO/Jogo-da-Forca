#define TAMANHO 35

void abertura_jogo();
void escolhe_tema();
void escolhe_palavra(const char* arquivo_desejado);
bool verifica_chute(char chute);
void chuta(char palavra[]);
bool ja_chutou(char chute);
void desenha_forca();
void sublinha_palavra(char palavra[]);
bool enforcou();
bool ganhou(char palavra[]);
void limpar_terminal();
bool ja_chutou(char chute);
