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
#define ARCHIVOSBUFFER 255
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
    strcpy(juegoDefault.archivo, nombreArchivo);
    juegoDefault.nombre[0] = juegoDefault.autor[0] = juegoDefault.resumen[0] = juegoDefault.cantidadCategorias = 0;
    return juegoDefault;
}

int criterioOrdenamiento(const void *juego1, const void *juego2) {
    return -(*(juego*)juego2).cantidadCategorias + (*(juego*)juego1).cantidadCategorias;
}

int indexar(char* direccion, char contenido[STRINGBUFFER][ARCHIVOSBUFFER]) {
    DIR *dir;
    struct dirent *ent;

    int largo = 0;
    if((dir = opendir(direccion)) != NULL){
        while ((ent = readdir(dir)) != NULL)
            if (ent->d_name[0] != '.')
                strcpy(contenido[largo++], ent->d_name);
        closedir(dir);
    }
    else
        printf("Error al indexar el directorio %s\n",direccion);
    
    return largo;
}

int main() {
    char dirBibloteca[] = "./juegos/";
    char dirCategorias[] = "./categorias/";
    
    juego juegos[ARCHIVOSBUFFER];
    int largoJuegos = obtenerJuegos(juegos, dirBibloteca);

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
    
    char origen[STRINGBUFFER], destino[STRINGBUFFER];
    for (int i = 0; i < largoJuegos; i++)
        for (int j = 0; j < largoCategorias; j++)
            if (strcmp(juegos[i].categorias[0], categorias[j]) == 0) {
                strcpy(origen, dirBibloteca);
                strcat(origen, juegos[i].archivo);

                strcpy(destino, dirCategorias);
                strcat(destino, categorias[j]);

                copiar_archivo(destino, origen, 1);
            }

    int flag = 1, largoContenido, largoComando;
    char *extension, direccion[255] = "./",
    comando[255],
    contenido[ARCHIVOSBUFFER][STRINGBUFFER];
    while(flag){
        largoContenido = indexar(direccion, contenido);
        printf("%s> ", direccion);

        fgets(comando, 255, stdin);
        largoComando = strlen(comando);
        comando[--largoComando] = 0;

        if (!strncmp(comando, "cd ", 3)){
            chopN(comando, 3);
            largoComando -= 3;

            if (comando[largoComando - 1] != '/') {
                largoComando++;
                strcat(comando,"/");
            }

            if (strcmp(comando, "./")) {
                if (!strcmp(comando, "../")) {
                    for (int i = strlen(direccion) - 2; i > 0; i--) {
                        if (direccion[i] == '/') {
                            direccion[i+1] = 0;
                            break;
                        }
                    }
                }
                else {
                    existe = 0;
                    for (int i = 0; i < largoContenido; i++) {
                        if (!strncmp(comando, contenido[i], largoComando-1)) {
                            existe = 1;
                            break;
                        }
                    }
                    if (!existe) {
                        printf("El directorio seleccionado no existe.\n");
                        continue;
                    }
                    else
                        strcat(direccion, comando);
                }
            }
        }
        else if (strncmp(comando, "open ", 5) == 0){
            chopN(comando, 5);
            largoComando -= 5;
            
            existe = 0;
            for (int i = 0; i < largoContenido; i++)
                if (!strcmp(comando, contenido[i])) {
                    existe = 1;
                    break;
                }
            if (!existe) {
                printf("El archivo solicitado no existe.\n");
                continue;
            }

            extension = strrchr(comando, '.');
            if (!extension || strcmp(extension, ".txt")) {
                printf("El archivo solicitado no es un juego (debe terminar en .txt).\n");
                continue;
            }

            juego juegoSolicitado = encontrarJuego(comando, juegos, largoJuegos);
            if (juegoSolicitado.cantidadCategorias == 0) {
                printf("No se puede abrir %s (Revise que la estructura pertenezca a la de un Juego.)\n", comando);
            }
            printf("%s\n%s", juegoSolicitado.nombre, juegoSolicitado.categorias[0]);
            
            for (int i = 1; i < juegoSolicitado.cantidadCategorias; i++)
                printf(", %s", juegoSolicitado.categorias[i]);
            printf("\n%s\n%s\n", juegoSolicitado.autor, juegoSolicitado.resumen);
        }
        else if(!strcmp(comando, "ls")) {
            int largoJI = 0;
            juego juegosIndexados[ARCHIVOSBUFFER];
            for (int i = 0; i < largoContenido; i++) {
                extension = strrchr(contenido[i], '.');
                if (extension && !strcmp(extension, ".txt"))
                    juegosIndexados[largoJI++] = encontrarJuego(contenido[i], juegos, largoJuegos);
                else
                    printf("%s\n", contenido[i]);
            }

            qsort(juegosIndexados, largoJI, sizeof(juego), criterioOrdenamiento);
            for (int i = 0; i < largoJI; i++)
                printf("%s\n", juegosIndexados[i].archivo);
        }
        else if (!strcmp(comando, "exit"))
            flag = 0;
        else {
            printf("%s no es una sentencia válida.\n", comando);
            continue;
        }
    }
    
    return 0;
}