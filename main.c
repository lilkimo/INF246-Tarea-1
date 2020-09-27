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
    return -(*(juego*)juego2).cantidadCategorias + (*(juego*)juego1).cantidadCategorias;
}


char * cd(char *comando){
    printf("%s\n",comando);
    char *nueva_direccion = malloc(sizeof(char)*255);
    if (strlen(comando) == 2){
        strcat(comando, "/");
        strcat(nueva_direccion, comando);
    }
    else{
        char *nuevo_comando = comando + 3;
        strcat(nuevo_comando,"/");
        strcat(nueva_direccion, nuevo_comando);
    }
    return nueva_direccion;
}

void ls(char *direccion, juego *juegos, int largo) {
    char *extension;
    int indice = 0;
    juego juego_actual;
    juego juegos_cat[largo];
    DIR *dir;
    struct dirent *ent;
    dir = opendir(direccion);
    if(dir!= NULL){
        while ((ent = readdir(dir)) != NULL) {
            extension = strrchr(ent->d_name, '.');
            if (extension && !strcmp(extension, ".txt")) {
                juego_actual = encontrarJuego(ent->d_name, juegos, largo);
                juegos_cat[indice++] = juego_actual;
            }
            else{
                printf("%s\n",ent->d_name);
            }
        }
        closedir(dir);
    }
    else{
        printf("Error al abrir el directorio %s\n",direccion);
    }
    qsort(juegos_cat, indice, sizeof(juego), criterioOrdenamiento);
    for (int i = 0; i < indice; i++) {
        printf("%s\n", juegos_cat[i].archivo);
    }
    return;
}

void abrir_texto(){
    return;
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

                copiar_archivo(destino, origen, 0);
            }

    int flag = 1;
    char direccion[255] = "./";
    while(flag){
        char comando[255];
        printf("Escriba un comando: ");
        fgets(comando, 255, stdin);
        if (strncmp(comando, "cd", 2) == 0){
            strcpy(direccion,cd(comando));
        }
        else if(strncmp(comando, "ls", 2) == 0){
            ls(direccion, juegos, largoJuegos);
        }
        else{
            if (strncmp(comando, "open", 4) == 0){
                abrir_texto(comando);
            }
            else{
                flag = 0;
                printf("Hasta la proximaaaaaa...");
            }
        }
    }
    free(juegos);
    return 0;
}