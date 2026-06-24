#include "regras.h"
#include <stdio.h>
#include <stdlib.h>
//função para verificar se a peca presenta na posição inicial é do jogador da vez.
int ehPecaDoJogador(char peca, char jogador){
    
    if (jogador == 'B' && (peca == '@' || peca == '&')||
     jogador == 'C' && (peca == 'o' || peca == 'O')) 
    {
        return 1;
    }else{
        return 0;
    }
}
//função para verificar se a peça presenta na posição final é do adversario.
int ehPecaDoAdversario(char peca, char jogador){
    char adversario;

    if (jogador == 'B')
    {
        adversario = 'C';
    }else{
        adversario = 'B';
    }
    
    return ehPecaDoJogador(peca, adversario);
}
//Essa função vai verificar se as entradas ditas pelo usuario são validas para uma captura. Usando as funções já feitas.
int validarCapturaSimples(int tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final, char jogador){

//declarando coluna e linha centrais para verificação. Vericação de se a peça entre a posição inicial e final é adversaria.
int coluna_central = (coluna_final + coluna_inicial)/2;
int linha_central= (linha_final + linha_inicial)/2;

if (ehPecaDoJogador(tabuleiro[linha_inicial][coluna_inicial], jogador) 
&& ehPecaDoAdversario(tabuleiro[linha_central][coluna_central],jogador) 
&& (abs(linha_final-linha_inicial) == 2 && abs(coluna_final - coluna_inicial) == 2) 
&& tabuleiro[linha_final][coluna_final] == ' ')
{
    return 1;
}else{
    return 0;
}

}




    
