#include "regras.h"
#include <stdio.h>
#include <stdlib.h>

//função para verificar se a peca presenta na posição inicial é do jogador da vez.
int ehPecaDoJogador(char peca, char jogador){
    
    if (
        jogador == 'B' && (peca == '@' || peca == '&')||
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
int validarCapturaSimples(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final, char jogador){

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
//fim da validação de captura simples

//essa função vai ser implementada para usar de maneira que valide a movimentação do jogador de acordo com sua posição inicial C (cima) ou B(baixo);
int direcaoFrente(char jogador){
    
    if (jogador == 'C')
    {
        return 1;
    }else{
        return -1;
    }
    
}
//fim da função de direcaoFrente


//essa função vai validar movimentos que não são de captura, movimentos ditos como normais.
int validarMovimentoNormal(char tabuleiro[10][10],int linha_inicial,int coluna_inicial, int linha_final, int coluna_final, char jogador){
    if (

        ehPecaDoJogador(tabuleiro[linha_inicial][coluna_inicial], jogador) && 
        tabuleiro[linha_final][coluna_final] == ' ' && 
        abs(linha_final - linha_inicial) == 1 && 
        abs(coluna_final - coluna_inicial) == 1 && 
        (linha_final - linha_inicial) == direcaoFrente(jogador))

    {
        return 1;
    }else{
        return 0;
    } 

}
//fim da função validarMovimentoNormal.   


//Nessa função verificamos se o caminho esta livre para uma dama, pois é diferente do movimento de uma peça normal.
int caminhoLivreDama(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final){
    int passo_linha;
    int passo_coluna;

    //para não termos que fazer mais condicionais, criei um "passo_linha" que vê a difenreça do final e inical for > 0 ou < 0, assim agiremos a partir dessa diferança.
    if (linha_final - linha_inicial > 0)
    {
        passo_linha = 1;
    }else{
        passo_linha = -1;
    }

    if (coluna_final - coluna_inicial > 0)
    {
        passo_coluna = 1;
    }else{
        passo_coluna = -1;
    }
    
    for (int i = linha_inicial + passo_linha, j = coluna_inicial + passo_coluna;
        i != linha_final;
        i += passo_linha,
        j += passo_coluna)
    {
        
        if (tabuleiro[i][j] != ' ')
      {
        return 0;
      }
      
    }
    
     return 1;
}
//Fim da função caminhoLivreDama

//verifica se eh dama
int ehDama(char peca){
    if (peca == '&' || peca == 'O')
    {
        return 1;
    }else{
        return 0;
    }
}

//essa função verifica as condições para um movimento normal de dama.
int validarMovimentoDama(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final, char jogador){
    if (
        ehPecaDoJogador(tabuleiro[linha_inicial][coluna_inicial],jogador) 
        && ehDama(tabuleiro[linha_inicial][coluna_inicial]) 
        && abs(linha_final - linha_inicial) == abs(coluna_final - coluna_inicial) 
        && tabuleiro[linha_final][coluna_final] == ' '
        && caminhoLivreDama(tabuleiro, linha_inicial, coluna_inicial, linha_final, coluna_final))
    {
        return 1;
    }else{
        return 0;
    }
    
}
//Fim da função validar movimento dama

int validarCapturaDama(char tabuleiro[10][10], int linha_inicial, int coluna_inicial, int linha_final, int coluna_final, char jogador){
    int passo_linha;
    int passo_coluna;
    int cont_adversarias = 0;

    if (linha_final - linha_inicial > 0)
    {
        passo_linha = 1;
    }else{
        passo_linha = -1;
    }

    if (coluna_final - coluna_inicial > 0)
    {
        passo_coluna = 1;
    }else{
        passo_coluna = -1;
    }
    
    for (int i = linha_inicial + passo_linha, j = coluna_inicial + passo_coluna;
         i != linha_final; 
         i+= passo_linha,
         j+= passo_coluna   )

    {
        if (ehPecaDoAdversario(tabuleiro[i][j], jogador))
            {
                cont_adversarias++;
            }
        else if(ehPecaDoJogador(tabuleiro[i][j], jogador)){

            return 0;

        }    
        
    }

    if (
        cont_adversarias == 1 
        && ehPecaDoJogador(tabuleiro[linha_inicial][coluna_inicial],jogador) 
        && abs(linha_final - linha_inicial) == abs(coluna_final - coluna_inicial) 
        && ehDama(tabuleiro[linha_inicial][coluna_inicial]) 
        && tabuleiro[linha_final][coluna_final] == ' '){
            return 1;
        }else{

            return 0;

        }
    
}
//fim da função validarCapturaDama.


//função para verificar se a peça esta dentro do tabuleiro(usar na captura obrigatoria)
int dentroTabuleiro(int linha, int coluna){

    if (linha >= 0 && linha <= 9 && coluna >=0 && coluna <=9)
    {
        return 1;
    }else{
        return 0;
    }   
}
//fim da função dentroTabuleiro.

//verifica a existencia de captura dentro de cada posição do tabuleiro.
int verificarExistenciaCaptura(char tabuleiro[10][10], int i, int j, char jogador){

    if (ehDama(tabuleiro[i][j])) {
        
        for (int d = 1; d < 10; d++) {

            if (dentroTabuleiro(i+d, j+d) && validarCapturaDama(tabuleiro, i, j, i+d, j+d, jogador)) return 1;
            if (dentroTabuleiro(i+d, j-d) && validarCapturaDama(tabuleiro, i, j, i+d, j-d, jogador)) return 1;
            if (dentroTabuleiro(i-d, j+d) && validarCapturaDama(tabuleiro, i, j, i-d, j+d, jogador)) return 1;
            if (dentroTabuleiro(i-d, j-d) && validarCapturaDama(tabuleiro, i, j, i-d, j-d, jogador)) return 1;

        }
    } else {
        
        if (dentroTabuleiro(i+2, j+2) && validarCapturaSimples(tabuleiro, i, j, i+2, j+2, jogador)) return 1;
        if (dentroTabuleiro(i+2, j-2) && validarCapturaSimples(tabuleiro, i, j, i+2, j-2, jogador)) return 1;
        if (dentroTabuleiro(i-2, j+2) && validarCapturaSimples(tabuleiro, i, j, i-2, j+2, jogador)) return 1;
        if (dentroTabuleiro(i-2, j-2) && validarCapturaSimples(tabuleiro, i, j, i-2, j-2, jogador)) return 1;

    }

    return 0;  
}
//fim da função verificarExistenciaCaptura


//função final da captura, varrer todo o tabuleiro em busca da captura
int capturaObrigatoria(char tabuleiro[10][10], char jogador){
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            if (ehPecaDoJogador(tabuleiro[i][j], jogador) && verificarExistenciaCaptura(tabuleiro, i, j, jogador)) {
                return 1;
            }
        }
    }
    return 0;
}
//fim da função capturaObrigatoria