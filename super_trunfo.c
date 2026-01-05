#include <stdio.h>
#include <string.h>

typedef struct {
    char estado[50];
    char codigo[10];
    char cidade[50];
    int populacao;
    float pib;
    float area;
    int pontos_turisticos;
    float densidade;
    float pib_per_capita;
} Carta;

void calcular_derivados(Carta *carta) {
    if (carta->area > 0) {
        carta->densidade = carta->populacao / carta->area;
    }
    if (carta->populacao > 0) {
        carta->pib_per_capita = (carta->pib * 1000000000) / carta->populacao;
    }
}

void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void cadastrar_carta(Carta *carta) {
    printf("\n=== CADASTRO DE CARTA ===\n");
    printf("Estado: ");
    scanf("%49s", carta->estado);

    printf("Código: ");
    scanf("%9s", carta->codigo);

    printf("Cidade: ");
    limpar_buffer();
    fgets(carta->cidade, sizeof(carta->cidade), stdin);
    carta->cidade[strcspn(carta->cidade, "\n")] = 0;

    printf("População: ");
    scanf("%d", &carta->populacao);

    printf("PIB (bilhões): ");
    scanf("%f", &carta->pib);

    printf("Área (km²): ");
    scanf("%f", &carta->area);

    printf("Pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);

    calcular_derivados(carta);
}

void exibir_carta(Carta carta) {
    printf("\n[%s-%s] %s", carta.estado, carta.codigo, carta.cidade);
    printf("\n  População: %d | PIB: %.2f | Área: %.2f", carta.populacao, carta.pib, carta.area);
    printf("\n  Turismo: %d | Densidade: %.2f hab/km² | PIB/capita: %.2f\n",
           carta.pontos_turisticos, carta.densidade, carta.pib_per_capita);
}

void comparar_atributo_simples(Carta c1, Carta c2, int atributo) {
    char *nome;
    char *vencedor;

    if (atributo == 1) {
        nome = "POPULAÇÃO";
        vencedor = (c1.populacao > c2.populacao) ? c1.cidade :
                   (c2.populacao > c1.populacao) ? c2.cidade : "EMPATE";
        printf("\n%s (%d) vs %s (%d)\n", c1.cidade, c1.populacao, c2.cidade, c2.populacao);
    } else if (atributo == 2) {
        nome = "PIB";
        vencedor = (c1.pib > c2.pib) ? c1.cidade :
                   (c2.pib > c1.pib) ? c2.cidade : "EMPATE";
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.pib, c2.cidade, c2.pib);
    } else if (atributo == 3) {
        nome = "ÁREA";
        vencedor = (c1.area > c2.area) ? c1.cidade :
                   (c2.area > c1.area) ? c2.cidade : "EMPATE";
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.area, c2.cidade, c2.area);
    } else if (atributo == 4) {
        nome = "PONTOS TURÍSTICOS";
        vencedor = (c1.pontos_turisticos > c2.pontos_turisticos) ? c1.cidade :
                   (c2.pontos_turisticos > c1.pontos_turisticos) ? c2.cidade : "EMPATE";
        printf("\n%s (%d) vs %s (%d)\n", c1.cidade, c1.pontos_turisticos, c2.cidade, c2.pontos_turisticos);
    } else if (atributo == 5) {
        nome = "DENSIDADE POPULACIONAL";
        vencedor = (c1.densidade > c2.densidade) ? c1.cidade :
                   (c2.densidade > c1.densidade) ? c2.cidade : "EMPATE";
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.densidade, c2.cidade, c2.densidade);
    } else {
        nome = "PIB PER CAPITA";
        vencedor = (c1.pib_per_capita > c2.pib_per_capita) ? c1.cidade :
                   (c2.pib_per_capita > c1.pib_per_capita) ? c2.cidade : "EMPATE";
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.pib_per_capita, c2.cidade, c2.pib_per_capita);
    }

    printf("=== COMPARAÇÃO: %s ===\n", nome);
    printf("Resultado: %s\n", vencedor);
}

void comparar_multiplos_atributos(Carta c1, Carta c2) {
    int opcao;
    printf("\n=== ESCOLHA O ATRIBUTO PARA COMPARAR ===\n");
    printf("1. População\n");
    printf("2. PIB\n");
    printf("3. Área\n");
    printf("4. Pontos Turísticos\n");
    printf("5. Densidade Populacional\n");
    printf("6. PIB per Capita\n");
    printf("Escolha (1-6): ");
    scanf("%d", &opcao);

    if (opcao >= 1 && opcao <= 6) {
        comparar_atributo_simples(c1, c2, opcao);
    } else {
        printf("✗ Opção inválida!\n");
    }
}

void comparar_dois_atributos_ternario(Carta c1, Carta c2) {
    printf("\n=== COMPARAÇÃO DE DOIS ATRIBUTOS (OPERADOR TERNÁRIO) ===\n");
    printf("Comparando: População + PIB\n\n");

    printf("POPULAÇÃO:\n");
    printf("  %s: %d vs %s: %d\n", c1.cidade, c1.populacao, c2.cidade, c2.populacao);
    char *vencedor_pop = (c1.populacao > c2.populacao) ? c1.cidade :
                         (c2.populacao > c1.populacao) ? c2.cidade : "EMPATE";
    printf("  → %s\n", vencedor_pop);

    printf("\nPIB:\n");
    printf("  %s: %.2f vs %s: %.2f\n", c1.cidade, c1.pib, c2.cidade, c2.pib);
    char *vencedor_pib = (c1.pib > c2.pib) ? c1.cidade :
                         (c2.pib > c1.pib) ? c2.cidade : "EMPATE";
    printf("  → %s\n", vencedor_pib);

    printf("\nRESULTADO FINAL:\n");
    int pontos1 = (c1.populacao > c2.populacao ? 1 : 0) + (c1.pib > c2.pib ? 1 : 0);
    int pontos2 = (c2.populacao > c1.populacao ? 1 : 0) + (c2.pib > c1.pib ? 1 : 0);

    printf("  %s: %d pontos | %s: %d pontos\n", c1.cidade, pontos1, c2.cidade, pontos2);
    char *campeao = (pontos1 > pontos2) ? c1.cidade :
                    (pontos2 > pontos1) ? c2.cidade : "EMPATE";
    printf("  🏆 Campeão: %s\n", campeao);
}

int main() {
    Carta cartas[32];
    int opcao_principal, num_cartas = 0;

    while (1) {
        printf("\n╔════════ SUPER TRUNFO - VERSÃO COMPLETA ════════╗\n");
        printf("║ 1. Cadastrar carta                              ║\n");
        printf("║ 2. Exibir cartas cadastradas                    ║\n");
        printf("║ 3. Comparar uma carta (um atributo)             ║\n");
        printf("║ 4. Comparar cartas (escolher atributo)          ║\n");
        printf("║ 5. Comparar cartas (dois atributos - ternário)  ║\n");
        printf("║ 6. Sair                                         ║\n");
        printf("╚═══════════════════════════════════════════════════╝\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao_principal);

        switch (opcao_principal) {
            case 1:
                if (num_cartas < 32) {
                    cadastrar_carta(&cartas[num_cartas]);
                    num_cartas++;
                    printf("✓ Carta cadastrada com sucesso!\n");
                } else {
                    printf("✗ Limite de 32 cartas atingido!\n");
                }
                break;

            case 2:
                if (num_cartas > 0) {
                    printf("\n╔════ CARTAS CADASTRADAS ════╗\n");
                    for (int i = 0; i < num_cartas; i++) {
                        printf("\n[Carta %d]", i + 1);
                        exibir_carta(cartas[i]);
                    }
                    printf("\n╚═════════════════════════════╝\n");
                } else {
                    printf("✗ Nenhuma carta cadastrada!\n");
                }
                break;

            case 3:
                if (num_cartas >= 2) {
                    int idx1, idx2;
                    printf("\nEscolha primeira carta (1-%d): ", num_cartas);
                    scanf("%d", &idx1);
                    printf("Escolha segunda carta (1-%d): ", num_cartas);
                    scanf("%d", &idx2);

                    if (idx1 > 0 && idx1 <= num_cartas &&
                        idx2 > 0 && idx2 <= num_cartas &&
                        idx1 != idx2) {
                        printf("\n=== COMPARAÇÃO SIMPLES (if/if-else) ===\n");
                        comparar_atributo_simples(cartas[idx1 - 1], cartas[idx2 - 1], 1);
                    } else {
                        printf("✗ Indices inválidos ou cartas iguais!\n");
                    }
                } else {
                    printf("✗ Cadastre pelo menos 2 cartas!\n");
                }
                break;

            case 4:
                if (num_cartas >= 2) {
                    int idx1, idx2;
                    printf("\nEscolha primeira carta (1-%d): ", num_cartas);
                    scanf("%d", &idx1);
                    printf("Escolha segunda carta (1-%d): ", num_cartas);
                    scanf("%d", &idx2);

                    if (idx1 > 0 && idx1 <= num_cartas &&
                        idx2 > 0 && idx2 <= num_cartas &&
                        idx1 != idx2) {
                        printf("\n=== COMPARAÇÃO COM MENU (if-else if/switch) ===\n");
                        comparar_multiplos_atributos(cartas[idx1 - 1], cartas[idx2 - 1]);
                    } else {
                        printf("✗ Indices inválidos ou cartas iguais!\n");
                    }
                } else {
                    printf("✗ Cadastre pelo menos 2 cartas!\n");
                }
                break;

            case 5:
                if (num_cartas >= 2) {
                    int idx1, idx2;
                    printf("\nEscolha primeira carta (1-%d): ", num_cartas);
                    scanf("%d", &idx1);
                    printf("Escolha segunda carta (1-%d): ", num_cartas);
                    scanf("%d", &idx2);

                    if (idx1 > 0 && idx1 <= num_cartas &&
                        idx2 > 0 && idx2 <= num_cartas &&
                        idx1 != idx2) {
                        printf("\n=== COMPARAÇÃO AVANÇADA (operador ternário) ===\n");
                        comparar_dois_atributos_ternario(cartas[idx1 - 1], cartas[idx2 - 1]);
                    } else {
                        printf("✗ Indices inválidos ou cartas iguais!\n");
                    }
                } else {
                    printf("✗ Cadastre pelo menos 2 cartas!\n");
                }
                break;

            case 6:
                printf("\nAté logo! 👋\n");
                return 0;

            default:
                printf("✗ Opção inválida!\n");
        }
    }
}
