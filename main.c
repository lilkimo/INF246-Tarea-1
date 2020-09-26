// Modulos default.
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Modulos para hacer llamadas al sistema.
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h>
#include <unistd.h> // verificar

#define STRINGBUFFER 255
#define JUEGOSBUFFER 255
// Modulos Propios
#include "./utilidades/string++.h"
#include "./utilidades/juego.h"
#include "./utilidades/sistema.h"

int infoJuego(juego juego) {
    if (juego.cantidadCategorias > 0 && juego.cantidadCategorias < 6) {
        printf("%s\n", juego.nombre);
        
        printf("%s", juego.categorias[0]);
        for (int j = 1; j < juego.cantidadCategorias; j++)
            printf(", %s", juego.categorias[j]);
        printf("\n");
        
        printf("%s\n", juego.autor);
        printf("%s\n", juego.resumen);
        
        return 0;
    }
    return 1;
}

juego encontrarJuego(char *nombreArchivo, juego *juegos, int largo) {
    for (int i = 0; i < largo; i++)
        if (strcmp(nombreArchivo, juegos[i].archivo) == 0)
            return juegos[i];
    
    juego juegoDefault;
    juegoDefault.archivo[0] = juegoDefault.nombre[0] = juegoDefault.autor[0] = juegoDefault.resumen[0] = juegoDefault.cantidadCategorias = 0;
    return juegoDefault;
}

int criterioOrdenamiento(const void *juego1, const void *juego2) {
    return (*(juego*)juego2).cantidadCategorias - (*(juego*)juego1).cantidadCategorias;
}

int main() {
    char dirBibloteca[] = "./juegos/";
    char dirCategorias[] = "./categorias/";
    
    int largoJuegos;
    juego *juegos = obtenerJuegos(dirBibloteca, &largoJuegos);

    crear_carpeta("./", "categorias");
    int largoCategorias, existe;
    char categorias[5][STRINGBUFFER], categoria[STRINGBUFFER];
    for (int i = 0; i < largoJuegos; i++) {
        strcpy(categoria, juegos[i].categorias[0]);
        existe = 0;

        for (int j = 0; j < largoCategorias; j++)
            if (strcmp(categorias[j], categoria) == 0) {
                existe = 1;
                break;
            }
        if (!existe) {
            strcpy(categorias[largoCategorias++], categoria);
            crear_carpeta(dirCategorias, categoria);
        }
    }
    
    char origen[255], destino[255];
    for (int i = 0; i < largoJuegos; i++)
        for (int j = 0; j < largoCategorias; j++)
            if (strcmp(juegos[i].categorias[0], categorias[j]) == 0) {
                strcpy(origen, dirBibloteca);
                strcat(origen, juegos[i].archivo);

                strcpy(destino, dirCategorias);
                strcat(destino, categorias[j]);

                copiar_archivo(destino, origen, 1);
            }
    /*
    qsort(juegos, largoJuegos, sizeof(juego), criterioOrdenamiento);
    printf("Con QuickSort:\n");
    for (int i = 0; i < largoJuegos; i++) {
        printf("%s\n", juegos[i].nombre);
    }
    */
    free(juegos);
    return 0;
}