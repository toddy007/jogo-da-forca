#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>
#include <time.h>
#include <string.h>
#include "palavras.h"

char *palavra;
int tamanho;
char letras_chutadas[26] = {0};
int acertos = 0;
int erros = 0;

bool includes(char array[], char letter, int length) {
    for (int i = 0; i < length; i++) {
        if (letter == array[i]) {
            return 1;
        }
    }
    
    return 0;
}

void verificar_chute(char letra) {
    int length = sizeof(letras_chutadas) / sizeof(letras_chutadas[0]);
    bool ja_chutou = includes(letras_chutadas, letra, length);
    if (ja_chutou) {
        printf("Você já chutou essa letra\n");
        return;
    }
    
    bool acertou = 0;
    for (int i = 0; i < tamanho; i++) {
        if (letra == palavra[i]) {
            acertos++;
            
            if (!acertou) {
                acertou = 1;
            }
        }
    }
    
    for (int i = 0; i < 26; i++) {
        if (letras_chutadas[i] != 0) {
            continue;
        }
        
        letras_chutadas[i] = letra;
        break;
    }

    if (acertou) {
        printf("Letra certa\n");
        return;
    }
    
    erros++;
    printf("Letra errada\n");
};

void desenhar_forca(void) {
    char *cabeca = erros >= 1 ? "(_)" : "";
    char *corpo = erros >= 2 ? "|" : "";
    char *braco1 = erros >= 3 ? "\\" : " ";
    char *braco2 = erros >= 3 ? "/" : "";
    char *corpo_resto = erros >= 4 ? "|" : "";
    char *perna1 = erros >= 5 ? "/" : "";
    char *perna2 = erros >= 6 ? "\\" : "";
    
    int length = sizeof(letras_chutadas) / sizeof(letras_chutadas[0]);
    for (int i = 0; i < tamanho; i++) {
        if (includes(letras_chutadas, palavra[i], length)) {
            printf(" %c ", palavra[i]);
        } else {
            printf(" _ ");
        }
    }

    printf("\n_________\n");
    printf("|/      |\n");
    printf("|      %s\n", cabeca);
    printf("|      %s%s%s\n", braco1, corpo, braco2);
    printf("|       %s\n", corpo_resto);
    printf("|      %s %s\n", perna1, perna2);
    printf("|\n");
    printf("|___\n");
    printf("Digite uma letra:\n");
    
    char entrada[16];
    scanf("%15s", entrada);
    if (entrada[1] != '\0') {
        printf("Letra invalída\n");
        return;
    } // tive que fazer assim por conta de um comportamento do C

    char letra_chute = tolower(entrada[0]);
    
    if (!isalpha(letra_chute)) {
        printf("Letra invalída\n");
        return;
    }
    
    verificar_chute(letra_chute);
};

bool ganhou(void) {
    if (acertos == tamanho) {
        return 1;
    }

    return 0;
}

bool perdeu(void) {
    if (erros == 6) {
        return 1;
    }
    
    return 0;
}

int main(void) {
    srand(time(NULL));
    int index = rand() % tamanho_palavras;
    palavra = palavras[index];
    tamanho = strlen(palavra);

    do {
        desenhar_forca();

        if (ganhou()) {
            printf("\nJogo acabou, você ganhou\n");
        }
        
        if (perdeu()) {
            printf("\nJogo acabou, você perdeu\n");
        }
        
        if (ganhou() || perdeu()) {
            printf("A palavra era: %s\n", palavra);
        }
    } while ((!ganhou()) && (!perdeu()));
    
    return 0;
};