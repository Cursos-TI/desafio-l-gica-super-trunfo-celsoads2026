/*
 * Created by Celso Andre on 30/01/26
 * Super Trunfo - Cadastro e Comparacao de Cartas
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* =========================
   STRUCT
=========================*/
typedef struct {
    char estado;
    char codigo[5];
    char *cidade;
    int populacao;
    float area;
    float pib;
    int pontosTuristicos;

    // Campos calculados
    float densidadePopulacional;
    float pibPerCapita;

} Carta;

/* =========================
   LIMPAR BUFFER
=========================*/
void clearBuffer(void) {
    while (getchar() != '\n');
}

/* =========================
   LEITURAS NUMERICAS
=========================*/
int readInt(const char *label) {
    int value;

    printf("%s", label);
    if (scanf("%d", &value) != 1) {
        printf("Entrada invalida! Usando 0.\n");
        clearBuffer();
        return 0;
    }
    return value;
}

float readFloat(const char *label) {
    float value;

    printf("%s", label);
    if (scanf("%f", &value) != 1) {
        printf("Entrada invalida! Usando 0.\n");
        clearBuffer();
        return 0.0f;
    }
    return value;
}

/* =========================
   STRING DINAMICA (WINDOWS)
=========================*/
char* readString(const char *label) {

    char buffer[1024];
    char *text;

    printf("%s", label);
    clearBuffer();

    fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';

    text = (char*) malloc(strlen(buffer) + 1);
    strcpy(text, buffer);

    return text;
}

/* =========================
   CADASTRAR CARTA
=========================*/
void cadastrarCarta(Carta *c, int numero) {

    printf("\n=== Cadastro da Carta %d ===\n", numero);

    printf("Estado (A-H): ");
    scanf(" %c", &c->estado);

    printf("Codigo da carta (ex: A01): ");
    scanf("%s", c->codigo);

    c->cidade = readString("Nome da cidade: ");

    c->populacao = readInt("Populacao: ");
    c->area = readFloat("Area (km2): ");
    c->pib = readFloat("PIB (em bilhoes): ");
    c->pontosTuristicos = readInt("Pontos turisticos: ");

    /* Calculos */
    if (c->area > 0)
        c->densidadePopulacional = c->populacao / c->area;
    else
        c->densidadePopulacional = 0;

    if (c->populacao > 0)
        c->pibPerCapita = c->pib / c->populacao;
    else
        c->pibPerCapita = 0;
}

/* =========================
   IMPRIMIR CARTA
=========================*/
void imprimirCarta(Carta c, int numero) {

    printf("\n===== CARTA %d =====\n", numero);
    printf("Estado: %c\n", c.estado);
    printf("Codigo: %s\n", c.codigo);
    printf("Cidade: %s\n", c.cidade);
    printf("Populacao: %d\n", c.populacao);
    printf("Area: %.2f km2\n", c.area);
    printf("PIB: %.2f bilhoes\n", c.pib);
    printf("Pontos Turisticos: %d\n", c.pontosTuristicos);
    printf("Densidade Populacional: %.2f hab/km2\n", c.densidadePopulacional);
    printf("PIB per capita: %.6f\n", c.pibPerCapita);
}

/* =========================
   COMPARAR CARTAS
   ATRIBUTO ESCOLHIDO: POPULACAO
=========================*/
void compararCartas(Carta c1, Carta c2) {

    printf("\n=== Comparacao de Cartas (Atributo: Populacao) ===\n");

    printf("Carta 1 - %s (%c): %d\n",
           c1.cidade, c1.estado, c1.populacao);

    printf("Carta 2 - %s (%c): %d\n",
           c2.cidade, c2.estado, c2.populacao);

    if (c1.populacao > c2.populacao) {
        printf("\nResultado: Carta 1 (%s) venceu!\n", c1.cidade);
    }
    else if (c2.populacao > c1.populacao) {
        printf("\nResultado: Carta 2 (%s) venceu!\n", c2.cidade);
    }
    else {
        printf("\nResultado: Empate!\n");
    }
}

/* =========================
   MAIN
=========================*/
int main(void) {

    Carta carta1;
    Carta carta2;

    cadastrarCarta(&carta1, 1);
    cadastrarCarta(&carta2, 2);

    imprimirCarta(carta1, 1);
    imprimirCarta(carta2, 2);

    compararCartas(carta1, carta2);

    free(carta1.cidade);
    free(carta2.cidade);

    return 0;
}
