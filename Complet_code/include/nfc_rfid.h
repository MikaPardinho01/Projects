void inicializa_nfc();
void atualiza_nfc();

// Funcao para verificacao de duplicatas
extern bool isDuplicateUID(unsigned long newUID);
extern int i;
extern unsigned long newUID;

// Funcao para limpar a memoria flash
void clearMemoryIfAllowed();

//Funcao para armazenar os dados na memoria flash
void storeUID(unsigned long newUID);
