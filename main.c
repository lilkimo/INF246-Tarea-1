#include <stdio.h>
#include <stdlib.h>

#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> // Sirve para acceder a las carpetas.
#include <string.h>

typedef struct {
    char nombre[255];
    char categorias[5][255];
    char autor[255];
    char resumen[255];
} juego;

juego obtenerJuego(char* direccion) {
    juego juego;
    
    FILE *fp;
    char linea[255];
    
    fp = fopen(direccion, "r");
    fgets(linea, 255, fp);
    strcpy(juego.nombre, strtok(linea, "\n"));
    
    
    //fgets(linea, 255, fp);
    //strcpy(juego.nombre, linea);
    
    

    fgets(linea, 255, fp);
    strcpy(juego.autor, strtok(linea, "\n"));
    
    fgets(linea, 255, fp);
    strcpy(juego.resumen, strtok(linea, "\n"));

    fclose(fp);

    /*
    printf("%s\n", juego.nombre);
    printf("%s\n", juego.autor);
    printf("%s\n", juego.resumen);
    */

    return juego;
}

juego * obtenerJuegos(int *largo) {
    juego *juegos;
    int indice = 0;

    char raiz[] = "./juegos/";
    char direccion[255];
    char *extension;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(raiz)) != NULL) {
        juegos = (juego *)malloc(sizeof(juego)*255);
        while ((ent = readdir(dir)) != NULL) {
            extension = strrchr(ent->d_name, '.');
            if (extension && !strcmp(extension, ".txt")) {
                strcpy(direccion, raiz);
                strcat(direccion, ent->d_name);
                juegos[indice++] = obtenerJuego(direccion);
            }
        }
        closedir(dir);
        juegos = (juego *)realloc(juegos, sizeof(juego)*indice);
    }
    else 
        perror ("Error al abrir la carpeta juegos");
    
    *largo = indice;
    return juegos;
}


int main() {
    int largo;
    juego *juegos = obtenerJuegos(&largo);
    for (int i = 0; i < largo; i++) {
        printf("%s\n", juegos[i].nombre);
    }

    return 0;
}