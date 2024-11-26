#ifndef TOKEN_H
#define TOKEN_H

extern unsigned long Intervalo_Troca;
extern unsigned long tempoAnterior;

void inicializa_token();
void atualiza_token();
extern int gerarSenha();
extern void mostrarSenha(int senha);
extern void mostrarTempoRestante(unsigned long tempoRestante);

#endif