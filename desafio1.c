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
} Carta;

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
}

void exibir_carta(Carta carta) {
    printf("\n[%s-%s] %s\n", carta.estado, carta.codigo, carta.cidade);
    printf("  População: %d | PIB: %.2f | Área: %.2f | Turismo: %d\n",
           carta.populacao, carta.pib, carta.area, carta.pontos_turisticos);
}

void comparar_populacao(Carta c1, Carta c2) {
    printf("\n=== COMPARAÇÃO: POPULAÇÃO ===\n");
    printf("%s (%d) vs %s (%d)\n", c1.cidade, c1.populacao, c2.cidade, c2.populacao);

    if (c1.populacao > c2.populacao) {
        printf("Vencedor: %s!\n", c1.cidade);
    } else if (c1.populacao < c2.populacao) {
        printf("Vencedor: %s!\n", c2.cidade);
    } else {
        printf("Resultado: Empate!\n");
    }
}

int main() {
    Carta cartas[32];
    int opcao, num_cartas = 0;

    while (1) {
        printf("\n========== SUPER TRUNFO - DESAFIO 1 ==========\n");
        printf("1. Cadastrar carta\n");
        printf("2. Exibir cartas cadastradas\n");
        printf("3. Comparar população de duas cartas\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        if (opcao == 1) {
            if (num_cartas < 32) {
                cadastrar_carta(&cartas[num_cartas]);
                num_cartas++;
                printf("✓ Carta cadastrada com sucesso!\n");
            } else {
                printf("✗ Limite de 32 cartas atingido!\n");
            }
        } else if (opcao == 2) {
            if (num_cartas > 0) {
                printf("\n=== CARTAS CADASTRADAS ===\n");
                for (int i = 0; i < num_cartas; i++) {
                    printf("\n[Carta %d] ", i + 1);
                    exibir_carta(cartas[i]);
                }
            } else {
                printf("✗ Nenhuma carta cadastrada!\n");
            }
        } else if (opcao == 3) {
            if (num_cartas >= 2) {
                int idx1, idx2;
                printf("\nEscolha primeira carta (1-%d): ", num_cartas);
                scanf("%d", &idx1);
                printf("Escolha segunda carta (1-%d): ", num_cartas);
                scanf("%d", &idx2);

                if (idx1 > 0 && idx1 <= num_cartas && idx2 > 0 && idx2 <= num_cartas && idx1 != idx2) {
                    comparar_populacao(cartas[idx1 - 1], cartas[idx2 - 1]);
                } else {
                    printf("✗ Indices inválidos ou cartas iguais!\n");
                }
            } else {
                printf("✗ Cadastre pelo menos 2 cartas!\n");
            }
        } else if (opcao == 4) {
            printf("\nAté logo!\n");
            break;
        } else {
            printf("✗ Opção inválida!\n");
        }
    }

    return 0;
}
