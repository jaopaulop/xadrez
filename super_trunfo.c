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

void cadastrar_carta(Carta *carta) {
    printf("\n=== CADASTRO DE CARTA ===\n");

    printf("Estado: ");
    scanf("%s", carta->estado);

    printf("Código da carta: ");
    scanf("%s", carta->codigo);

    printf("Cidade: ");
    scanf("%s", carta->cidade);

    printf("População: ");
    scanf("%d", &carta->populacao);

    printf("PIB (em bilhões): ");
    scanf("%f", &carta->pib);

    printf("Área (em km²): ");
    scanf("%f", &carta->area);

    printf("Pontos turísticos: ");
    scanf("%d", &carta->pontos_turisticos);

    carta->densidade = carta->populacao / carta->area;
    carta->pib_per_capita = (carta->pib * 1000000000) / carta->populacao;
}

void exibir_carta(Carta carta) {
    printf("\n=== CARTA ===\n");
    printf("Estado: %s\n", carta.estado);
    printf("Código: %s\n", carta.codigo);
    printf("Cidade: %s\n", carta.cidade);
    printf("População: %d\n", carta.populacao);
    printf("PIB: %.2f bilhões\n", carta.pib);
    printf("Área: %.2f km²\n", carta.area);
    printf("Pontos turísticos: %d\n", carta.pontos_turisticos);
    printf("Densidade populacional: %.2f hab/km²\n", carta.densidade);
    printf("PIB per capita: %.2f\n", carta.pib_per_capita);
}

void comparar_cartas(Carta carta1, Carta carta2) {
    printf("\n=== COMPARAÇÃO DE CARTAS ===\n");
    printf("%s x %s\n\n", carta1.cidade, carta2.cidade);

    printf("População: ");
    printf(carta1.populacao > carta2.populacao ? "%s vence!\n" :
           carta1.populacao < carta2.populacao ? "%s vence!\n" : "Empate!\n",
           carta1.populacao > carta2.populacao ? carta1.cidade : carta2.cidade);

    printf("PIB: ");
    printf(carta1.pib > carta2.pib ? "%s vence!\n" :
           carta1.pib < carta2.pib ? "%s vence!\n" : "Empate!\n",
           carta1.pib > carta2.pib ? carta1.cidade : carta2.cidade);

    printf("Área: ");
    printf(carta1.area > carta2.area ? "%s vence!\n" :
           carta1.area < carta2.area ? "%s vence!\n" : "Empate!\n",
           carta1.area > carta2.area ? carta1.cidade : carta2.cidade);

    printf("Densidade: ");
    printf(carta1.densidade > carta2.densidade ? "%s vence!\n" :
           carta1.densidade < carta2.densidade ? "%s vence!\n" : "Empate!\n",
           carta1.densidade > carta2.densidade ? carta1.cidade : carta2.cidade);

    printf("PIB per capita: ");
    printf(carta1.pib_per_capita > carta2.pib_per_capita ? "%s vence!\n" :
           carta1.pib_per_capita < carta2.pib_per_capita ? "%s vence!\n" : "Empate!\n",
           carta1.pib_per_capita > carta2.pib_per_capita ? carta1.cidade : carta2.cidade);
}

int main() {
    Carta cartas[32];
    int opcao, num_cartas = 0;

    while (1) {
        printf("\n=== SUPER TRUNFO - PAÍSES ===\n");
        printf("1. Cadastrar carta\n");
        printf("2. Exibir cartas\n");
        printf("3. Comparar duas cartas\n");
        printf("4. Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                if (num_cartas < 32) {
                    cadastrar_carta(&cartas[num_cartas]);
                    num_cartas++;
                    printf("\nCarta cadastrada com sucesso!\n");
                } else {
                    printf("\nLimite de cartas atingido!\n");
                }
                break;

            case 2:
                if (num_cartas > 0) {
                    for (int i = 0; i < num_cartas; i++) {
                        printf("\n--- Carta %d ---", i + 1);
                        exibir_carta(cartas[i]);
                    }
                } else {
                    printf("\nNenhuma carta cadastrada!\n");
                }
                break;

            case 3:
                if (num_cartas >= 2) {
                    int carta1, carta2;
                    printf("\nEscolha a primeira carta (1-%d): ", num_cartas);
                    scanf("%d", &carta1);
                    printf("Escolha a segunda carta (1-%d): ", num_cartas);
                    scanf("%d", &carta2);

                    if (carta1 > 0 && carta1 <= num_cartas &&
                        carta2 > 0 && carta2 <= num_cartas &&
                        carta1 != carta2) {
                        comparar_cartas(cartas[carta1 - 1], cartas[carta2 - 1]);
                    } else {
                        printf("\nCartas inválidas!\n");
                    }
                } else {
                    printf("\nCadastre pelo menos 2 cartas!\n");
                }
                break;

            case 4:
                printf("\nAté logo!\n");
                return 0;

            default:
                printf("\nOpção inválida!\n");
        }
    }
}
