#ifndef TOKEN_H
#define TOKEN_H

extern int randNumber;

extern unsigned long Intervalo_Troca;
extern unsigned long NovoTempoExtra;
extern unsigned long Intervalo_Normal;
extern unsigned long Tempo_extra;
extern unsigned long tempo_anterior_token;
extern unsigned long troca_Token;

void Inicializa_senha();

int gera_senha();
void tempo_extra();
void Reset_user();

#endif