#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>

// Modulos Propios
#include "./utilidades/string++.h"
#include "./utilidades/juego.h"

int main() {
    int largo;
    juego *juegos = obtenerJuegos("./juegos/", &largo);
    
    for (int i = 0; i < largo; i++) {
        printf("%s\n", juegos[i].nombre);
        printf("%s", juegos[i].categorias[0]);
        for (int j = 1; j < juegos[i].cantidadCategorias; j++)
            printf(", %s", juegos[i].categorias[j]);
        printf("\n");
        printf("%s\n", juegos[i].autor);
        printf("%s\n", juegos[i].resumen);
    }
    
    return 0;
}