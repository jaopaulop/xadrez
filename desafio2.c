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

void comparar_atributos(Carta c1, Carta c2, int atributo) {
    char *nome_atributo;
    char *vencedor;

    if (atributo == 1) {
        nome_atributo = "POPULAÇÃO";
        if (c1.populacao > c2.populacao) {
            vencedor = c1.cidade;
        } else if (c1.populacao < c2.populacao) {
            vencedor = c2.cidade;
        } else {
            vencedor = "EMPATE";
        }
        printf("\n%s (%d) vs %s (%d)\n", c1.cidade, c1.populacao, c2.cidade, c2.populacao);
    } else if (atributo == 2) {
        nome_atributo = "PIB";
        if (c1.pib > c2.pib) {
            vencedor = c1.cidade;
        } else if (c1.pib < c2.pib) {
            vencedor = c2.cidade;
        } else {
            vencedor = "EMPATE";
        }
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.pib, c2.cidade, c2.pib);
    } else if (atributo == 3) {
        nome_atributo = "ÁREA";
        if (c1.area > c2.area) {
            vencedor = c1.cidade;
        } else if (c1.area < c2.area) {
            vencedor = c2.cidade;
        } else {
            vencedor = "EMPATE";
        }
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.area, c2.cidade, c2.area);
    } else if (atributo == 4) {
        nome_atributo = "PONTOS TURÍSTICOS";
        if (c1.pontos_turisticos > c2.pontos_turisticos) {
            vencedor = c1.cidade;
        } else if (c1.pontos_turisticos < c2.pontos_turisticos) {
            vencedor = c2.cidade;
        } else {
            vencedor = "EMPATE";
        }
        printf("\n%s (%d) vs %s (%d)\n", c1.cidade, c1.pontos_turisticos, c2.cidade, c2.pontos_turisticos);
    } else if (atributo == 5) {
        nome_atributo = "DENSIDADE POPULACIONAL";
        if (c1.densidade > c2.densidade) {
            vencedor = c1.cidade;
        } else if (c1.densidade < c2.densidade) {
            vencedor = c2.cidade;
        } else {
            vencedor = "EMPATE";
        }
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.densidade, c2.cidade, c2.densidade);
    } else if (atributo == 6) {
        nome_atributo = "PIB PER CAPITA";
        if (c1.pib_per_capita > c2.pib_per_capita) {
            vencedor = c1.cidade;
        } else if (c1.pib_per_capita < c2.pib_per_capita) {
            vencedor = c2.cidade;
        } else {
            vencedor = "EMPATE";
        }
        printf("\n%s (%.2f) vs %s (%.2f)\n", c1.cidade, c1.pib_per_capita, c2.cidade, c2.pib_per_capita);
    }

    printf("=== COMPARAÇÃO: %s ===\n", nome_atributo);
    printf("Resultado: %s\n", vencedor);
}

int main() {
    Carta cartas[32];
    int opcao, num_cartas = 0;

    while (1) {
        printf("\n========== SUPER TRUNFO - DESAFIO 2 ==========\n");
        printf("1. Cadastrar carta\n");
        printf("2. Exibir cartas\n");
        printf("3. Comparar cartas\n");
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
                    int idx1, idx2, atributo;
                    printf("\nEscolha primeira carta (1-%d): ", num_cartas);
                    scanf("%d", &idx1);
                    printf("Escolha segunda carta (1-%d): ", num_cartas);
                    scanf("%d", &idx2);

                    if (idx1 > 0 && idx1 <= num_cartas && idx2 > 0 && idx2 <= num_cartas && idx1 != idx2) {
                        printf("\n=== ESCOLHA O ATRIBUTO ===\n");
                        printf("1. População\n");
                        printf("2. PIB\n");
                        printf("3. Área\n");
                        printf("4. Pontos Turísticos\n");
                        printf("5. Densidade Populacional\n");
                        printf("6. PIB per Capita\n");
                        printf("Escolha: ");
                        scanf("%d", &atributo);

                        if (atributo >= 1 && atributo <= 6) {
                            comparar_atributos(cartas[idx1 - 1], cartas[idx2 - 1], atributo);
                        } else {
                            printf("✗ Atributo inválido!\n");
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
