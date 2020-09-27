//#include <string.h>
void strctrp(char *destino, const char *origen, char *caracteresInvalidos) {
    int largo = strlen(origen),
    cantCarInv = strlen(caracteresInvalidos),
    inicio = -1,
    final = -1,
    esValido;

    for (int i = 0; i < largo; i++) {
        esValido = 1;
        for (int j = 0; j < cantCarInv; j++)
            if (origen[i] == caracteresInvalidos[j]) {
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
            if (origen[i] == caracteresInvalidos[j]) {
                esValido = 0;
                break;
            }
        if (esValido) {
            final = i;
            break;
        }
    }

    if (inicio == final && inicio == -1)
        return;
    
    int largo2 = 0;
    for (int i = inicio; i <= final; i++)
        destino[largo2++] = origen[i];
    destino[largo2] = 0;
}

//Borra los primeros n caracteres de str
size_t chopN(char *str, size_t n)
{
    size_t len = strlen(str);
    if (n > len)
        n = len;
    memmove(str, str+n, len - n + 1);
    return(len - n);
}

// strip
void strtrp(char *destino, const char *origen) {
    strctrp(destino, origen, " \n\r");
}