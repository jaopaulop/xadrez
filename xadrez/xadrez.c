#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMANHO 8

// Estrutura para representar uma posição no tabuleiro
typedef struct {
    int linha;
    int coluna;
} Posicao;

// Estrutura para representar o tabuleiro
typedef struct {
    char casas[TAMANHO][TAMANHO];
} Tabuleiro;

// Função para inicializar o tabuleiro vazio
void inicializarTabuleiro(Tabuleiro *tab) {
    for (int i = 0; i < TAMANHO; i++) {
        for (int j = 0; j < TAMANHO; j++) {
            tab->casas[i][j] = '.';
        }
    }
}

// Função para exibir o tabuleiro
void exibirTabuleiro(Tabuleiro *tab) {
    printf("\n  ");
    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
    }
    printf("\n");

    for (int i = 0; i < TAMANHO; i++) {
        printf("%d ", i);
        for (int j = 0; j < TAMANHO; j++) {
            printf("%c ", tab->casas[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

// Função para validar se uma posição está dentro do tabuleiro
int posicaoValida(int linha, int coluna) {
    return (linha >= 0 && linha < TAMANHO && coluna >= 0 && coluna < TAMANHO);
}

// ============================================================================
// OBJETIVO 1: MOVIMENTOS BÁSICOS COM LOOPS SIMPLES
// ============================================================================

// Simula movimento da Torre (horizontal e vertical)
void moverTorre(Tabuleiro *tab, Posicao origem, Posicao destino) {
    inicializarTabuleiro(tab);
    tab->casas[origem.linha][origem.coluna] = 'T';

    printf("=== MOVIMENTO DA TORRE ===\n");
    printf("Origem: (%d, %d) -> Destino: (%d, %d)\n",
           origem.linha, origem.coluna, destino.linha, destino.coluna);

    // Torre só pode mover em linha reta (horizontal ou vertical)
    if (origem.linha != destino.linha && origem.coluna != destino.coluna) {
        printf("Movimento inválido! Torre só se move em linha reta.\n");
        return;
    }

    printf("\nTabuleiro inicial:\n");
    exibirTabuleiro(tab);

    // Movimento horizontal (mesma linha)
    if (origem.linha == destino.linha) {
        int direcao = (destino.coluna > origem.coluna) ? 1 : -1;
        int coluna = origem.coluna + direcao;

        printf("Movendo horizontalmente...\n");
        while (coluna != destino.coluna) {
            tab->casas[origem.linha][coluna] = '*';
            printf("Passo intermediário:\n");
            exibirTabuleiro(tab);
            coluna += direcao;
        }
    }
    // Movimento vertical (mesma coluna)
    else {
        int direcao = (destino.linha > origem.linha) ? 1 : -1;
        int linha = origem.linha + direcao;

        printf("Movendo verticalmente...\n");
        while (linha != destino.linha) {
            tab->casas[linha][origem.coluna] = '*';
            printf("Passo intermediário:\n");
            exibirTabuleiro(tab);
            linha += direcao;
        }
    }

    tab->casas[origem.linha][origem.coluna] = '.';
    tab->casas[destino.linha][destino.coluna] = 'T';
    printf("Posição final:\n");
    exibirTabuleiro(tab);
}

// Simula movimento do Bispo (diagonal)
void moverBispo(Tabuleiro *tab, Posicao origem, Posicao destino) {
    inicializarTabuleiro(tab);
    tab->casas[origem.linha][origem.coluna] = 'B';

    printf("=== MOVIMENTO DO BISPO ===\n");
    printf("Origem: (%d, %d) -> Destino: (%d, %d)\n",
           origem.linha, origem.coluna, destino.linha, destino.coluna);

    // Bispo só pode mover na diagonal
    int diffLinha = abs(destino.linha - origem.linha);
    int diffColuna = abs(destino.coluna - origem.coluna);

    if (diffLinha != diffColuna) {
        printf("Movimento inválido! Bispo só se move na diagonal.\n");
        return;
    }

    printf("\nTabuleiro inicial:\n");
    exibirTabuleiro(tab);

    int direcaoLinha = (destino.linha > origem.linha) ? 1 : -1;
    int direcaoColuna = (destino.coluna > origem.coluna) ? 1 : -1;

    int linha = origem.linha + direcaoLinha;
    int coluna = origem.coluna + direcaoColuna;

    printf("Movendo diagonalmente...\n");
    for (; linha != destino.linha && coluna != destino.coluna;
         linha += direcaoLinha, coluna += direcaoColuna) {
        tab->casas[linha][coluna] = '*';
        printf("Passo intermediário:\n");
        exibirTabuleiro(tab);
    }

    tab->casas[origem.linha][origem.coluna] = '.';
    tab->casas[destino.linha][destino.coluna] = 'B';
    printf("Posição final:\n");
    exibirTabuleiro(tab);
}

// Simula movimento da Rainha (combinação de Torre e Bispo)
void moverRainha(Tabuleiro *tab, Posicao origem, Posicao destino) {
    inicializarTabuleiro(tab);
    tab->casas[origem.linha][origem.coluna] = 'R';

    printf("=== MOVIMENTO DA RAINHA ===\n");
    printf("Origem: (%d, %d) -> Destino: (%d, %d)\n",
           origem.linha, origem.coluna, destino.linha, destino.coluna);

    printf("\nTabuleiro inicial:\n");
    exibirTabuleiro(tab);

    // Verifica se é movimento de torre (horizontal/vertical)
    if (origem.linha == destino.linha || origem.coluna == destino.coluna) {
        printf("Rainha movendo como Torre...\n");

        if (origem.linha == destino.linha) {
            int direcao = (destino.coluna > origem.coluna) ? 1 : -1;
            int coluna = origem.coluna;

            do {
                coluna += direcao;
                if (coluna != destino.coluna) {
                    tab->casas[origem.linha][coluna] = '*';
                    printf("Passo intermediário:\n");
                    exibirTabuleiro(tab);
                }
            } while (coluna != destino.coluna);
        } else {
            int direcao = (destino.linha > origem.linha) ? 1 : -1;
            int linha = origem.linha;

            do {
                linha += direcao;
                if (linha != destino.linha) {
                    tab->casas[linha][origem.coluna] = '*';
                    printf("Passo intermediário:\n");
                    exibirTabuleiro(tab);
                }
            } while (linha != destino.linha);
        }
    }
    // Verifica se é movimento de bispo (diagonal)
    else if (abs(destino.linha - origem.linha) == abs(destino.coluna - origem.coluna)) {
        printf("Rainha movendo como Bispo...\n");

        int direcaoLinha = (destino.linha > origem.linha) ? 1 : -1;
        int direcaoColuna = (destino.coluna > origem.coluna) ? 1 : -1;

        int linha = origem.linha;
        int coluna = origem.coluna;

        do {
            linha += direcaoLinha;
            coluna += direcaoColuna;
            if (linha != destino.linha && coluna != destino.coluna) {
                tab->casas[linha][coluna] = '*';
                printf("Passo intermediário:\n");
                exibirTabuleiro(tab);
            }
        } while (linha != destino.linha && coluna != destino.coluna);
    } else {
        printf("Movimento inválido! Rainha move como Torre ou Bispo.\n");
        return;
    }

    tab->casas[origem.linha][origem.coluna] = '.';
    tab->casas[destino.linha][destino.coluna] = 'R';
    printf("Posição final:\n");
    exibirTabuleiro(tab);
}

// ============================================================================
// OBJETIVO 2: MOVIMENTO DO CAVALO COM LOOPS ANINHADOS
// ============================================================================

// Simula movimento do Cavalo em "L"
void moverCavalo(Tabuleiro *tab, Posicao origem, Posicao destino) {
    inicializarTabuleiro(tab);
    tab->casas[origem.linha][origem.coluna] = 'C';

    printf("=== MOVIMENTO DO CAVALO ===\n");
    printf("Origem: (%d, %d) -> Destino: (%d, %d)\n",
           origem.linha, origem.coluna, destino.linha, destino.coluna);

    // Movimentos possíveis do Cavalo (em L)
    int movimentosLinha[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int movimentosColuna[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    printf("\nTabuleiro inicial:\n");
    exibirTabuleiro(tab);

    printf("Verificando todos os movimentos possíveis em L:\n");
    int movimentoValido = 0;

    // Loop aninhado para verificar todos os movimentos possíveis
    for (int i = 0; i < 8; i++) {
        int novaLinha = origem.linha + movimentosLinha[i];
        int novaColuna = origem.coluna + movimentosColuna[i];

        printf("Testando movimento %d: ", i + 1);
        printf("(%d, %d) -> ", origem.linha, origem.coluna);
        printf("(%d, %d)\n", novaLinha, novaColuna);

        // Verifica se a posição é válida
        if (posicaoValida(novaLinha, novaColuna)) {
            // Marca possível movimento no tabuleiro
            for (int teste = 0; teste < 8; teste++) {
                int testeLinha = origem.linha + movimentosLinha[teste];
                int testeColuna = origem.coluna + movimentosColuna[teste];

                if (posicaoValida(testeLinha, testeColuna) &&
                    !(testeLinha == origem.linha && testeColuna == origem.coluna)) {
                    if (testeLinha == novaLinha && testeColuna == novaColuna) {
                        tab->casas[testeLinha][testeColuna] = 'X';
                    } else {
                        tab->casas[testeLinha][testeColuna] = 'o';
                    }
                }
            }

            exibirTabuleiro(tab);

            // Verifica se é o movimento desejado
            if (novaLinha == destino.linha && novaColuna == destino.coluna) {
                printf("Movimento encontrado!\n");
                movimentoValido = 1;
                break;
            }

            // Limpa marcações para próximo teste
            inicializarTabuleiro(tab);
            tab->casas[origem.linha][origem.coluna] = 'C';
        } else {
            printf("Posição fora do tabuleiro!\n\n");
        }
    }

    if (movimentoValido) {
        tab->casas[origem.linha][origem.coluna] = '.';
        tab->casas[destino.linha][destino.coluna] = 'C';
        printf("\nPosição final:\n");
        exibirTabuleiro(tab);
    } else {
        printf("\nMovimento inválido! Cavalo não pode alcançar essa posição.\n");
    }
}

// ============================================================================
// OBJETIVO 3: MOVIMENTOS AVANÇADOS COM RECURSIVIDADE
// ============================================================================

// Função recursiva para encontrar caminho do Cavalo até destino
int encontrarCaminhoCavaloRecursivo(Tabuleiro *tab, Posicao atual, Posicao destino,
                                    int profundidade, int maxProfundidade) {
    // Caso base: chegou ao destino
    if (atual.linha == destino.linha && atual.coluna == destino.coluna) {
        tab->casas[atual.linha][atual.coluna] = 'C';
        return 1;
    }

    // Caso base: profundidade máxima atingida
    if (profundidade >= maxProfundidade) {
        return 0;
    }

    // Marca posição atual
    if (tab->casas[atual.linha][atual.coluna] == '.') {
        tab->casas[atual.linha][atual.coluna] = '0' + profundidade;
    }

    // Movimentos possíveis do Cavalo
    int movimentosLinha[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int movimentosColuna[] = {-1, 1, -2, 2, -2, 2, -1, 1};

    // Tenta cada movimento possível recursivamente
    for (int i = 0; i < 8; i++) {
        int novaLinha = atual.linha + movimentosLinha[i];
        int novaColuna = atual.coluna + movimentosColuna[i];

        if (posicaoValida(novaLinha, novaColuna) &&
            tab->casas[novaLinha][novaColuna] == '.') {

            Posicao novaPosicao = {novaLinha, novaColuna};

            if (encontrarCaminhoCavaloRecursivo(tab, novaPosicao, destino,
                                               profundidade + 1, maxProfundidade)) {
                return 1;
            }
        }
    }

    return 0;
}

// Função para buscar caminho do Cavalo com recursão
void buscarCaminhoCavalo(Tabuleiro *tab, Posicao origem, Posicao destino) {
    printf("=== BUSCA RECURSIVA DE CAMINHO DO CAVALO ===\n");
    printf("Origem: (%d, %d) -> Destino: (%d, %d)\n",
           origem.linha, origem.coluna, destino.linha, destino.coluna);

    inicializarTabuleiro(tab);

    printf("\nBuscando caminho com profundidade máxima 6...\n");

    if (encontrarCaminhoCavaloRecursivo(tab, origem, destino, 0, 6)) {
        printf("\nCaminho encontrado!\n");
        printf("Os números representam a ordem dos movimentos:\n");
        exibirTabuleiro(tab);
    } else {
        printf("\nNenhum caminho encontrado com a profundidade especificada.\n");
    }
}

// Função recursiva para verificar se o Rei está em xeque
int verificarXequeRecursivo(Tabuleiro *tab, Posicao rei, int direcaoLinha,
                            int direcaoColuna, int distancia) {
    int novaLinha = rei.linha + (direcaoLinha * distancia);
    int novaColuna = rei.coluna + (direcaoColuna * distancia);

    // Se saiu do tabuleiro, não há ameaça nesta direção
    if (!posicaoValida(novaLinha, novaColuna)) {
        return 0;
    }

    char peca = tab->casas[novaLinha][novaColuna];

    // Se encontrou uma peça adversária que pode atacar nesta direção
    if (peca == 'T' || peca == 'R') {
        // Torre e Rainha podem atacar em linha reta
        if ((direcaoLinha == 0 || direcaoColuna == 0)) {
            tab->casas[novaLinha][novaColuna] = '!';
            return 1;
        }
    }

    if (peca == 'B' || peca == 'R') {
        // Bispo e Rainha podem atacar na diagonal
        if (direcaoLinha != 0 && direcaoColuna != 0) {
            tab->casas[novaLinha][novaColuna] = '!';
            return 1;
        }
    }

    // Se encontrou uma peça qualquer, para a busca nesta direção
    if (peca != '.') {
        return 0;
    }

    // Continua buscando recursivamente
    return verificarXequeRecursivo(tab, rei, direcaoLinha, direcaoColuna, distancia + 1);
}

// Função para verificar xeque usando recursão
void verificarXeque(Tabuleiro *tab, Posicao rei) {
    printf("=== VERIFICAÇÃO DE XEQUE (RECURSIVA) ===\n");
    printf("Posição do Rei: (%d, %d)\n", rei.linha, rei.coluna);

    tab->casas[rei.linha][rei.coluna] = 'K';

    printf("\nTabuleiro:\n");
    exibirTabuleiro(tab);

    int emXeque = 0;

    // Verifica todas as 8 direções recursivamente
    int direcoes[][2] = {{-1,0}, {1,0}, {0,-1}, {0,1}, {-1,-1}, {-1,1}, {1,-1}, {1,1}};

    for (int i = 0; i < 8; i++) {
        if (verificarXequeRecursivo(tab, rei, direcoes[i][0], direcoes[i][1], 1)) {
            emXeque = 1;
        }
    }

    if (emXeque) {
        printf("\n*** XEQUE! O Rei está sob ataque! ***\n");
        printf("Peças ameaçadoras marcadas com '!'\n");
        exibirTabuleiro(tab);
    } else {
        printf("\nO Rei está seguro.\n");
    }
}

// ============================================================================
// MENU PRINCIPAL
// ============================================================================

void exibirMenu() {
    printf("\n");
    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║         MATECHECK - XADREZ PROGRAMÁVEL                 ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  OBJETIVO 1: Movimentos Básicos (Loops Simples)       ║\n");
    printf("║  [1] Torre  - Movimento horizontal/vertical            ║\n");
    printf("║  [2] Bispo  - Movimento diagonal                       ║\n");
    printf("║  [3] Rainha - Combinação Torre + Bispo                 ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  OBJETIVO 2: Movimento do Cavalo (Loops Aninhados)    ║\n");
    printf("║  [4] Cavalo - Movimento em L                           ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  OBJETIVO 3: Movimentos Avançados (Recursividade)     ║\n");
    printf("║  [5] Busca de Caminho do Cavalo (Recursiva)            ║\n");
    printf("║  [6] Verificação de Xeque (Recursiva)                  ║\n");
    printf("╠════════════════════════════════════════════════════════╣\n");
    printf("║  [0] Sair                                              ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");
    printf("\nEscolha uma opção: ");
}

int main() {
    Tabuleiro tabuleiro;
    int opcao;
    Posicao origem, destino;

    printf("╔════════════════════════════════════════════════════════╗\n");
    printf("║         BEM-VINDO AO MATECHECK!                        ║\n");
    printf("║    Aprenda programação através do xadrez              ║\n");
    printf("╚════════════════════════════════════════════════════════╝\n");

    do {
        exibirMenu();
        scanf("%d", &opcao);

        switch(opcao) {
            case 1: // Torre
                printf("\nMOVIMENTO DA TORRE\n");
                printf("Digite posição de origem (linha coluna): ");
                scanf("%d %d", &origem.linha, &origem.coluna);
                printf("Digite posição de destino (linha coluna): ");
                scanf("%d %d", &destino.linha, &destino.coluna);
                moverTorre(&tabuleiro, origem, destino);
                break;

            case 2: // Bispo
                printf("\nMOVIMENTO DO BISPO\n");
                printf("Digite posição de origem (linha coluna): ");
                scanf("%d %d", &origem.linha, &origem.coluna);
                printf("Digite posição de destino (linha coluna): ");
                scanf("%d %d", &destino.linha, &destino.coluna);
                moverBispo(&tabuleiro, origem, destino);
                break;

            case 3: // Rainha
                printf("\nMOVIMENTO DA RAINHA\n");
                printf("Digite posição de origem (linha coluna): ");
                scanf("%d %d", &origem.linha, &origem.coluna);
                printf("Digite posição de destino (linha coluna): ");
                scanf("%d %d", &destino.linha, &destino.coluna);
                moverRainha(&tabuleiro, origem, destino);
                break;

            case 4: // Cavalo
                printf("\nMOVIMENTO DO CAVALO\n");
                printf("Digite posição de origem (linha coluna): ");
                scanf("%d %d", &origem.linha, &origem.coluna);
                printf("Digite posição de destino (linha coluna): ");
                scanf("%d %d", &destino.linha, &destino.coluna);
                moverCavalo(&tabuleiro, origem, destino);
                break;

            case 5: // Busca recursiva Cavalo
                printf("\nBUSCA DE CAMINHO DO CAVALO (RECURSIVA)\n");
                printf("Digite posição de origem (linha coluna): ");
                scanf("%d %d", &origem.linha, &origem.coluna);
                printf("Digite posição de destino (linha coluna): ");
                scanf("%d %d", &destino.linha, &destino.coluna);
                buscarCaminhoCavalo(&tabuleiro, origem, destino);
                break;

            case 6: // Verificação de Xeque
                printf("\nVERIFICAÇÃO DE XEQUE\n");
                inicializarTabuleiro(&tabuleiro);
                printf("Digite posição do Rei (linha coluna): ");
                scanf("%d %d", &origem.linha, &origem.coluna);

                printf("\nAdicione peças adversárias no tabuleiro:\n");
                printf("Quantas peças adversárias? ");
                int numPecas;
                scanf("%d", &numPecas);

                for (int i = 0; i < numPecas; i++) {
                    char tipoPeca;
                    int linha, coluna;
                    printf("Peça %d - Tipo (T=Torre, B=Bispo, R=Rainha): ", i + 1);
                    scanf(" %c", &tipoPeca);
                    printf("Posição (linha coluna): ");
                    scanf("%d %d", &linha, &coluna);
                    tabuleiro.casas[linha][coluna] = tipoPeca;
                }

                verificarXeque(&tabuleiro, origem);
                break;

            case 0:
                printf("\nObrigado por jogar MateCheck!\n");
                printf("Continue praticando programação! 🚀\n");
                break;

            default:
                printf("\nOpção inválida! Tente novamente.\n");
        }

        if (opcao != 0) {
            printf("\n----------------------------------------\n");
        }

    } while(opcao != 0);

    return 0;
}
