#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char * strip(char *string) {
    char caracteresInvalidos[2] = {' ', '\n'};
    
    int largo = strlen(string), inicio = -1, final = -1, esInvalido;
    
    esInvalido = 0;
    for (int i = 0; i < largo; i++) {
        esInvalido = 0;
        for (int j = 0; j < 2; j++)
            if (string[i] == caracteresInvalidos[j])
                esInvalido = 1;
        if (!esInvalido) {
            inicio = i;
            break;
        }
    }
    esInvalido = 0;
    for (int i = largo-1; i >= 0; i--) {
        esInvalido = 0;
        for (int j = 0; j < 2; j++)
            if (string[i] == caracteresInvalidos[j])
                esInvalido = 1;
        if (!esInvalido) {
            final = i;
            break;
        }
    }
    
    char *strippedString = malloc(sizeof(char)*(final - inicio + 2));
    strippedString[final - inicio + 1] = 0;

    for (int i = inicio, j = 0; i <= final; i++)
        strippedString[j++] = string[i];

    return strippedString;
}