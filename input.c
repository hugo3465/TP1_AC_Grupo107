#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "input.h"

#define VALOR_INVALIDO "Introduziu um valor invalido"
#define PAUSE "\n\nClique no enter para continuar."

void pause() {
    char ch;
    printf(PAUSE);
    while ((ch = getchar()) != '\n') {
        limparBuffer();
    }
}

void limparBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF) {
    }
}

void mensagem(char *msg) {
    system("clear || cls");

    printf("%s", msg);

    pause();
}

int obterInt(int minVal, int maxVal, char *msg) {
    int valor;

    printf(msg);

    while (scanf("%d", &valor) != 1 || valor < minVal || valor > maxVal) {
        puts(VALOR_INVALIDO);
        limparBuffer();
        printf(msg);
    }
    limparBuffer();

    return valor;
}

float obterFloat(float minVal, float maxVal, char *msg) {
    float valor;

    printf(msg);

    while (scanf("%f", &valor) != 1 || valor < minVal || valor > maxVal) {
        puts(VALOR_INVALIDO);
        limparBuffer();
        printf(msg);
    }
    limparBuffer();

    return valor;
}

double obterDouble(double minVal, double maxVal, char *msg) {
    double valor;

    printf(msg);

    while (scanf("%lf", &valor) != 1 || valor < minVal || valor > maxVal) {
        puts(VALOR_INVALIDO);
        limparBuffer();
        printf(msg);
    }
    limparBuffer();

    return valor;
}

char obterChar(char *msg) {
    char ch;

    printf(msg);
    ch = getchar();
    limparBuffer();

    return ch;
}

void obterString(char *string, int tamanho, char *msg) {
    printf(msg);

    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            limparBuffer();
        }
    }
}

void criarCodigo(char tipoCod, char *array, int numCaracteres) {
    // TipoCod e a variavel que e usada no comeco do codigo e ela serve para identificar o tipo do codigo

    char alfabeto[] = "abcdefghijklmnopqrstuvwxyz";
    char numeros[] = "0123456789";
    char codigo[numCaracteres];

    codigo[0] = tipoCod; // Colocar o caracter inicial

    for (int i = 1; i < numCaracteres - 1; i++) {
        // Gera num entre 0 e 1, 1 = numero; 0 = letra
        int numOuLetra = rand() % 2;

        // Gera letra
        if (numOuLetra == 0) {
            int randLetra = rand() % 26; // Gera letra entre A e F
            codigo[i] = alfabeto[randLetra];
        } else { // Gera numero
            int randNum = rand() % 10; // Gera um numero entre 0 e 9
            codigo[i] = numeros[randNum];
        }
    }

    codigo[numCaracteres] = '\0';


    strcpy(array, codigo);
}

void printArrayListagens(Listagens *listagens, int size) {
    int i;
    
    printf("=================================\n"); // separador
    
    for (i = 0; i < size; i++) {
        printf("\t%dº: %s\n", i + 1, listagens[i].nome);
    }
    
    printf("================================="); // separador
}

void ordenarListagens(Listagens *listagens, int size) {
    int i, j, position;
    Listagens swap;
    
    for (i = 0; i < (size - 1); i++) {
        position = i;
        for (j = i + 1; j < size; j++) {
            if (listagens[position].contador < listagens[j].contador) {
                position = j;
            }
        }
        if (position != i) {
            swap = listagens[i];
            listagens[i] = listagens[position];
            listagens[position] = swap;
        }
    }
}