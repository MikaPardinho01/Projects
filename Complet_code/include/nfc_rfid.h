//Inicializa todas as bibliotecas
void inicializa_nfc();

// Função para verificar se o UID é duplicado 
bool isDuplicateUID(unsigned long newUID);

// Função para limpar a memória flash se o usuário der permissão
void clearMemoryIfAllowed();

// Função para armazenar o UID no NVS (memória flash)
void storeUID(unsigned long newUID);

// Função para ler o UID do NVS (memória flash)
void atualiza_nfc();

extern unsigned long numericUID;
extern int i_posicao;
extern bool duplicado;
