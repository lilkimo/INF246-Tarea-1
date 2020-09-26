/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h> // Sirve para acceder a las carpetas.

// Modulos Propios
#include "string++.h"
*/

#define STRINGBUFFER 255
#define JUEGOSBUFFER 255

typedef struct {
    char archivo[STRINGBUFFER];
    
    char nombre[STRINGBUFFER];
    char autor[STRINGBUFFER];
    char resumen[STRINGBUFFER];
    
    char categorias[5][255];
    int cantidadCategorias;
} juego;

juego obtenerJuego(char *direccion) {
    juego juego;
    
    FILE *fp;
    char linea[STRINGBUFFER];
    fp = fopen(direccion, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo %s", direccion);   
        exit(1);             
    }

    char *ptr = strtok(direccion, "/");
    while (ptr != NULL) {
        strcpy(juego.archivo, ptr);
        ptr = strtok(NULL, "/");
    }

    fgets(linea, 255, fp);
    strcpy(juego.nombre, strip(linea));
    
    juego.cantidadCategorias = 0;
    fgets(linea, STRINGBUFFER, fp);
    ptr = strtok(linea, ",");
    while (ptr != NULL) {
        strcpy(juego.categorias[juego.cantidadCategorias++], strip(ptr));
        ptr = strtok(NULL, ",");
    }

    fgets(linea, STRINGBUFFER, fp);
    strcpy(juego.autor, strip(linea));
    
    fgets(linea, STRINGBUFFER, fp);
    linea[strcspn(linea, "\n")] = 0;
    strcpy(juego.resumen, strip(linea));
    

    fclose(fp);
    return juego;
}

juego * obtenerJuegos(char *directorio, int *largo) {
    juego *juegos;
    int indice = 0;

    char direccion[STRINGBUFFER];
    char *extension;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directorio)) != NULL) {
        juegos = (juego *)malloc(sizeof(juego)*JUEGOSBUFFER);
        
        while ((ent = readdir(dir)) != NULL) {
            extension = strrchr(ent->d_name, '.');
            if (extension && !strcmp(extension, ".txt")) {
                strcpy(direccion, directorio);
                strcat(direccion, ent->d_name);
                
                juegos[indice++] = obtenerJuego(direccion);
            }
        }
        closedir(dir);
        
        juegos = (juego *)realloc(juegos, sizeof(juego)*indice);
    }
    else 
        perror("Error al abrir la carpeta juegos");
    
    *largo = indice;
    return juegos;
}