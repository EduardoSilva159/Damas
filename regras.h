#ifndef REGRAS_H
#define REGRAS_H   

int ehPecaDoJogador(char peca, char jogador);

int ehPecaDoAdversario(char peca, char jogador);

int validarCapturaSimples(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final, char jogador);

int direcaoFrente(char jogador);

int validarMovimentoNormal(char tabuleiro[10][10],int linha_inicial,int coluna_inicial, int linha_final, int coluna_final, char jogador);

int caminhoLivreDama(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final);

int ehDama(char peca);

int verificarExistenteCaptura(char tabuleiro[10][10], int i, int j, char jogador);

int validarCapturaDama(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final, char jogador);

int dentroTabuleiro(int linha, int coluna);

int capturaObrigatoria(char tabuleiro[10][10], char jogador);



#endif