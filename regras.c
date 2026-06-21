#include "regras.h"
#include <stdio.h>
#include <stdlib.h>

int ehPecaDoJogador(char peca, char jogador){
    if (jogador == 'B' && (peca == '@' || peca == '&')||
     jogador == 'C' && (peca == 'o' || peca == 'O')) 
    {
        return 1;
    }else{
        return 0;
    }
}

int ehPecaDoAdversario(char peca1, char peca2){
    if (peca1 == '@' || peca1 == '&' && (peca2 == 'o' || peca2 == 'O') ||
    peca1 == 'o' || peca1 == 'O' && (peca2 == '@' || peca2 == '&'))
    {
        return 1;
    }else{
        return 0;
    }
    
}
    
