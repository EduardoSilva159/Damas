#include <stdio.h>
#include "damas.h"
#include "regras.h"

// Função para preencher a matriz com o estado inicial do jogo
void inicializar_tabuleiro(char tabuleiro[10][10]) {
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            // Se a soma do índice da linha com a coluna for par, é casa não-jogável (#)
            if ((i + j) % 2 == 0) {
                tabuleiro[i][j] = '#';
            } 
            // Se for ímpar, é uma casa jogável
            else {
                if (i < 3) {
                    tabuleiro[i][j] = 'o'; // Peças do jogador de cima (linhas 0, 1 e 2)
                } else if (i > 6) {
                    tabuleiro[i][j] = '@'; // Peças do jogador de baixo (linhas 7, 8 e 9)
                } else {
                    tabuleiro[i][j] = ' '; // Casas vazias no meio do tabuleiro
                }
            }
        }
    }
}

// Função para imprimir o tabuleiro
void imprimir_tabuleiro(char tabuleiro[10][10]) {
    // Imprime as letras das colunas na borda superior
    printf("  A B C D E F G H I J\n");
    
    // Loop para imprimir cada linha do tabuleiro
    for (int i = 0; i < 10; i++) {
        // Imprime a divisória horizontal antes da linha
        printf(" +-+-+-+-+-+-+-+-+-+-+\n");
        
        // Imprime o número da linha na borda esquerda
        printf("%d|", i);
        
        // Loop para imprimir o conteúdo das colunas daquela linha
        for (int j = 0; j < 10; j++) {
            printf("%c|", tabuleiro[i][j]);
        }
        
        // Imprime o número da linha na borda direita
        printf("%d\n", i);
    }
    
    // Imprime a última divisória horizontal e as letras na borda inferior
    printf(" +-+-+-+-+-+-+-+-+-+-+\n");
    printf("  A B C D E F G H I J\n");
}

int trans_entr(char entrada[10], int coords[4]){
    if(entrada[2]!='-'||entrada[3]!='-'){
        return 1;
    }
    else if(entrada[0]<'A'||entrada[0]>'J'||entrada[4]<'A'||entrada[4]>'J'){
        return 1;
    }
    else if(entrada[1]<'0'||entrada[1]>'9'||entrada[5]<'0'||entrada[5]>'9'){
        return 1;
    }
    //transforma a entrada que é uma string em coordenadas inteiras
    //entrada tem 10 posições por causa do fgets, que lê o \n no final da string e precisa de espaço pro '\0'
    else{ 
    coords[0] = entrada[0] - 'A';
    coords[1] = entrada[1] - '0';
    coords[2] = entrada[4] - 'A';
    coords[3] = entrada[5] - '0';
    return 0;
}
}

// Valida a jogada usando as funções do regras.c e, se for válida, executa o movimento.
// Retorna: 0 = jogada feita, 1 = jogada inválida, 2 = jogo acabou.
int vlog_mdtb(char jogador, int coords[4], char tabuleiro[10][10]){
    int i, j, p, q;
    i = coords[1]; // linha de origem
    j = coords[0]; // coluna de origem
    p = coords[3]; // linha de destino
    q = coords[2]; // coluna de destino

    // a peça de origem precisa ser do jogador da vez
    if(!ehPecaDoJogador(tabuleiro[i][j], jogador)){
        return 1;
    }

    // verifica se existe captura obrigatória no tabuleiro para esse jogador
    int tem_captura = capturaObrigatoria(tabuleiro, jogador);

    // tenta validar a jogada como uma captura simples (peça normal)
    if(validarCapturaSimples(tabuleiro, i, j, p, q, jogador)){
        // a peça capturada fica no meio do caminho
        int linha_central = (i + p) / 2;
        int coluna_central = (j + q) / 2;
        tabuleiro[linha_central][coluna_central] = ' ';
        tabuleiro[p][q] = tabuleiro[i][j];
        tabuleiro[i][j] = ' ';
    }
    // tenta validar como captura de dama
    else if(validarCapturaDama(tabuleiro, i, j, p, q, jogador)){
        // descobre a direção do movimento pra achar e remover a peça capturada
        int passo_linha, passo_coluna;
        if(p - i > 0){ passo_linha = 1; } else { passo_linha = -1; }
        if(q - j > 0){ passo_coluna = 1; } else { passo_coluna = -1; }
        for(int l = i + passo_linha, c = j + passo_coluna; l != p; l += passo_linha, c += passo_coluna){
            if(ehPecaDoAdversario(tabuleiro[l][c], jogador)){
                tabuleiro[l][c] = ' ';
            }
        }
        tabuleiro[p][q] = tabuleiro[i][j];
        tabuleiro[i][j] = ' ';
    }
    // se não foi captura, mas existia captura obrigatória, a jogada é inválida
    else if(tem_captura){
        return 1;
    }
    // movimento normal de peça (sem captura)
    else if(validarMovimentoNormal(tabuleiro, i, j, p, q, jogador)){
        tabuleiro[p][q] = tabuleiro[i][j];
        tabuleiro[i][j] = ' ';
    }
    // movimento de dama (sem captura)
    else if(validarMovimentoDama(tabuleiro, i, j, p, q, jogador)){
        tabuleiro[p][q] = tabuleiro[i][j];
        tabuleiro[i][j] = ' ';
    }
    // nenhuma regra validou a jogada
    else{
        return 1;
    }

    // promoção a dama: 'o' que chega na linha 9 e '@' que chega na linha 0
    if(tabuleiro[p][q]=='o' && p==9){
        tabuleiro[p][q]='O';
    }
    else if(tabuleiro[p][q]=='@' && p==0){
        tabuleiro[p][q]='&';
    }

    // o jogo acaba quando o adversário não tem mais nenhuma peça
    char adversario;
    if(jogador == 'C'){ adversario = 'B'; } else { adversario = 'C'; }
    int adversario_tem_peca = 0;
    for(int l = 0; l < 10; l++){
        for(int c = 0; c < 10; c++){
            if(ehPecaDoJogador(tabuleiro[l][c], adversario)){
                adversario_tem_peca = 1;
            }
        }
    }
    if(adversario_tem_peca == 0){
        return 2;
    }

    return 0;
}

char troca_jogador(char jogador){
    if(jogador == 'C'){
        jogador = 'B';
    }
    else{
        jogador = 'C';
    }
    return jogador;
    //retorna o jogador que vai jogar na próxima rodada
}

void loop(char jogador, char tabuleiro[10][10]){
    char entrada[10];
    int coords[4];

    inicializar_tabuleiro(tabuleiro);
    imprimir_tabuleiro(tabuleiro);
    printf("Qual jogador vai começar jogando?\n");
    scanf(" %c", &jogador);
    getchar();

    while(jogador != 'C' && jogador != 'B'){
        printf("Jogador inválido. Por favor, escolha 'C' para cima ou 'B' para baixo.\n");
        scanf(" %c", &jogador);
        getchar();//pega o \n que ficou no buffer do teclado
    }

    int jogo_acaba=0;
    while(jogo_acaba==0){
        printf("faca uma jogada:\n");
        if(fgets(entrada, sizeof(entrada), stdin) == NULL){
            break; //encerra se a entrada terminar (evita loop infinito)
        }
        if( trans_entr(entrada, coords) == 1){
            printf("Jogada inválida.\n");
        }
        else{
        int result = vlog_mdtb(jogador, coords, tabuleiro);
        
        if(result==1){
            printf("Jogada inválida.\n");
        }
        else if(result==2){
            jogo_acaba=1;
        }
        else{
            imprimir_tabuleiro(tabuleiro);
            jogador = troca_jogador(jogador);
        }
    }
}
    printf("O jogo acabou. O jogador %c venceu!\n", jogador);
}