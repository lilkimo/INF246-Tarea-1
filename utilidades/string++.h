/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
*/

char * strip(char *string) {
    char caracteresInvalidos[] = {' ', '\n', '\r'};
    int cantCarInv = 3;
    
    int largo = strlen(string),
    inicio = -1,
    final = -1,
    esValido;

    for (int i = 0; i < largo; i++) {
        esValido = 1;
        for (int j = 0; j < cantCarInv; j++)
            if (string[i] == caracteresInvalidos[j]) {
                esValido = 0;
                break;
            }
        if (esValido) {
            inicio = i;
            break;
        }
    }
    for (int i = largo-1; i >= 0; i--) {
        esValido = 1;
        for (int j = 0; j < cantCarInv; j++)
            if (string[i] == caracteresInvalidos[j]) {
                esValido = 0;
                break;
            }
        if (esValido) {
            final = i;
            break;
        }
    }

    if (inicio == final && inicio == -1)
        return "";
    
    char *strippedString = malloc(sizeof(char)*(final - inicio + 2));
    strippedString[final - inicio + 1] = 0;

    for (int i = inicio, j = 0; i <= final; i++)
        strippedString[j++] = string[i];

    return strippedString;
}