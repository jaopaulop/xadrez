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
    carta->densidade = carta->populacao / carta->area;
    carta->pib_per_capita = (carta->pib * 1000000000) / carta->populacao;
}

void cadastrar_carta(Carta *carta) {
    printf("\n=== CADASTRO DE CARTA ===\n");
    printf("Estado: ");
    scanf("%s", carta->estado);
    printf("Código: ");
    scanf("%s", carta->codigo);
    printf("Cidade: ");
    scanf("%s", carta->cidade);
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
    printf("\n[%s-%s] %s\n", carta.estado, carta.codigo, carta.cidade);
    printf("  População: %d | PIB: %.2f | Área: %.2f\n", carta.populacao, carta.pib, carta.area);
    printf("  Turismo: %d | Densidade: %.2f | PIB/capita: %.2f\n",
           carta.pontos_turisticos, carta.densidade, carta.pib_per_capita);
}

char* comparar_com_ternario(Carta c1, Carta c2, int attr1, int attr2) {
    if (attr1 == 1 && attr2 == 2) {
        int pontos1 = (c1.populacao > c2.populacao) + (c1.pib > c2.pib);
        int pontos2 = (c2.populacao > c1.populacao) + (c2.pib > c1.pib);
        return (pontos1 > pontos2) ? c1.cidade : (pontos2 > pontos1) ? c2.cidade : "EMPATE";
    }
    return "ERRO";
}

void mostrar_comparacao_dupla(Carta c1, Carta c2, int attr1, int attr2) {
    printf("\n=== COMPARAÇÃO DE DOIS ATRIBUTOS ===\n");

    if (attr1 == 1 && attr2 == 2) {
        printf("POPULAÇÃO:\n");
        printf("  %s: %d vs %s: %d\n", c1.cidade, c1.populacao, c2.cidade, c2.populacao);
        printf("  → %s vence\n", (c1.populacao > c2.populacao) ? c1.cidade :
               (c2.populacao > c1.populacao) ? c2.cidade : "Empate");

        printf("\nPIB:\n");
        printf("  %s: %.2f vs %s: %.2f\n", c1.cidade, c1.pib, c2.cidade, c2.pib);
        printf("  → %s vence\n", (c1.pib > c2.pib) ? c1.cidade :
               (c2.pib > c1.pib) ? c2.cidade : "Empate");

        printf("\nRESULTADO FINAL:\n");
        int p1 = (c1.populacao > c2.populacao) + (c1.pib > c2.pib);
        int p2 = (c2.populacao > c1.populacao) + (c2.pib > c1.pib);

        printf("Pontos %s: %d | Pontos %s: %d\n", c1.cidade, p1, c2.cidade, p2);
        printf("Vencedor: %s\n", (p1 > p2) ? c1.cidade : (p2 > p1) ? c2.cidade : "EMPATE");
    }
}

int main() {
    Carta cartas[32];
    int opcao, num_cartas = 0;

    while (1) {
        printf("\n========== SUPER TRUNFO - DESAFIO 3 ==========\n");
        printf("1. Cadastrar carta\n");
        printf("2. Exibir cartas\n");
        printf("3. Comparar duas cartas (com 2 atributos)\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (num_cartas < 32) {
                    cadastrar_carta(&cartas[num_cartas]);
                    num_cartas++;
                    printf("✓ Carta cadastrada!\n");
                } else {
                    printf("✗ Limite de 32 cartas atingido!\n");
                }
                break;

            case 2:
                if (num_cartas > 0) {
                    printf("\n=== CARTAS CADASTRADAS ===\n");
                    for (int i = 0; i < num_cartas; i++) {
                        printf("\n[Carta %d] ", i + 1);
                        exibir_carta(cartas[i]);
                    }
                } else {
                    printf("✗ Nenhuma carta cadastrada!\n");
                }
                break;

            case 3:
                if (num_cartas >= 2) {
                    int idx1, idx2, attr1, attr2;
                    printf("\nEscolha primeira carta (1-%d): ", num_cartas);
                    scanf("%d", &idx1);
                    printf("Escolha segunda carta (1-%d): ", num_cartas);
                    scanf("%d", &idx2);

                    if (idx1 > 0 && idx1 <= num_cartas && idx2 > 0 && idx2 <= num_cartas && idx1 != idx2) {
                        printf("\n=== ESCOLHA DOIS ATRIBUTOS ===\n");
                        printf("Atributos disponíveis:\n");
                        printf("1. População\n");
                        printf("2. PIB\n");
                        printf("3. Área\n");
                        printf("4. Pontos Turísticos\n");
                        printf("5. Densidade Populacional\n");
                        printf("6. PIB per Capita\n");
                        printf("Primeiro atributo (1-6): ");
                        scanf("%d", &attr1);
                        printf("Segundo atributo (1-6): ");
                        scanf("%d", &attr2);

                        if ((attr1 >= 1 && attr1 <= 6) && (attr2 >= 1 && attr2 <= 6) && attr1 != attr2) {
                            if ((attr1 == 1 && attr2 == 2) || (attr1 == 2 && attr2 == 1)) {
                                int a1 = (attr1 == 1) ? 1 : 2;
                                int a2 = (attr1 == 1) ? 2 : 1;
                                mostrar_comparacao_dupla(cartas[idx1 - 1], cartas[idx2 - 1], a1, a2);
                            } else {
                                printf("✗ Combinação de atributos não implementada!\n");
                                printf("   (Use População e PIB para a versão atual)\n");
                            }
                        } else {
                            printf("✗ Atributos inválidos ou iguais!\n");
                        }
                    } else {
                        printf("✗ Cartas inválidas!\n");
                    }
                } else {
                    printf("✗ Cadastre pelo menos 2 cartas!\n");
                }
                break;

            case 4:
                printf("\nAté logo!\n");
                return 0;

            default:
                printf("✗ Opção inválida!\n");
        }
    }
}
