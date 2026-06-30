#ifndef DAMAS_H
#define DAMAS_H

void inicializar_tabuleiro(char tabuleiro[10][10]);

void imprimir_tabuleiro(char tabuleiro[10][10]);

int trans_entr(char entrada[10], int coords[4]);

int vlog_mdtb(char jogador, int coords[4], char tabuleiro[10][10]);

char troca_jogador(char jogador);

void loop(char jogador, char tabuleiro[10][10]);

#endif