/*
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <dirent.h> // Sirve para acceder a las carpetas.

// Modulos Propios
#include "string++.h"
*/

//#define STRINGBUFFER 255
//#define ARCHIVOSBUFFER 255

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

    char copiaDireccion[255];
    strcpy(copiaDireccion, direccion);
    char *ptr = strtok(copiaDireccion, "/");
    while (ptr != NULL) {
        strcpy(juego.archivo, ptr);
        ptr = strtok(NULL, "/");
    }

    fgets(linea, 255, fp);
    strtrp(juego.nombre, linea);
    
    juego.cantidadCategorias = 0;
    fgets(linea, STRINGBUFFER, fp);
    ptr = strtok(linea, ",");
    while (ptr != NULL) {
        strtrp(juego.categorias[juego.cantidadCategorias++], ptr);
        ptr = strtok(NULL, ",");
    }

    fgets(linea, STRINGBUFFER, fp);
    strtrp(juego.autor, linea);
    
    fgets(linea, STRINGBUFFER, fp);
    linea[strcspn(linea, "\n")] = 0;
    strtrp(juego.resumen, linea);
    

    fclose(fp);
    return juego;
}

int obtenerJuegos(juego *juegos, char *directorio) {
    int indice = 0;

    char direccion[STRINGBUFFER];
    char *extension;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(directorio)) != NULL) {
        while ((ent = readdir(dir)) != NULL) {
            extension = strrchr(ent->d_name, '.');
            if (extension && !strcmp(extension, ".txt")) {
                strcpy(direccion, directorio);
                strcat(direccion, ent->d_name);
                
                juegos[indice++] = obtenerJuego(direccion);
            }
        }
        closedir(dir);
    }
    else 
        perror("Error al abrir la carpeta juegos");
    
    return indice;
}