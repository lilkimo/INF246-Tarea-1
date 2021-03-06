
/*
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <dirent.h>
*/

/*
void consola (){
    DIR *dr;
    struct dirent *en;
    int flag = 1;
    char direccion[255] = "./juegos/";
    while(flag){
        char comando[255];
        printf("Escriba un comando: ");
        scanf("%s",comando);
        if (strncmp(comando, "cd", 2) == 0){
            strcpy(direccion,cd(comando));
        }
        else if(strcmp(comando, "ls") == 0){
            ls(direccion);
        }
        else{
            if (strncmp(comando, "open", 4) == 0){
                abrir_texto();
            }
        }

    }
    return;
}

char * cd(char *comando){
    char nueva_direccion[255];
    if (strlen(comando) == 2){
        strcat(nueva_direccion, comando);
    }
    else{
        char *nuevo_comando = comando + 3;
        strcat(nuevo_comando,"/");
        strcat(nueva_direccion, nuevo_comando);
    }
    return nueva_direccion;
}

juego * ls(char *direccion) {
    int indice;
    juego *juegos;
    juego juego_actual;
    juego *juegos_cat;
    DIR *dir;
    struct dirent *ent;

    if((dir = opendir(direccion)) != NULL) {
        juegos = (juego *)malloc(sizeof(juego)*largo);
    
        while ((ent = readdir(dir)) != NULL) {
            extension = strrchr(ent->d_name, '.');
            if (extension && !strcmp(extension, ".txt")) {
                juego_actual = encontrarJuego(ent->d_name, juegos, largo);
                juegos_cat[indice++] = juego_actual;
            }
        }
    closedir(dir);
    }
    return juegos;
}
*/

void crear_carpeta(char *direccion, char *carpeta){
    char direccionFinal[255];
    strcpy(direccionFinal, direccion);
    if (direccion[strlen(direccion) - 1] != '/' && carpeta[0] != '/')
        strcat(direccionFinal, "/");
    strcat(direccionFinal, carpeta);
    
    mkdir(direccionFinal, S_IRWXU | S_IRWXG | S_IRWXO); // https://www.gnu.org/software/libc/manual/html_node/Permission-Bits.html
    return;
}

void copiar_archivo(char *destino, char *origen, int borrar) {
    char ch;
    FILE *source, *target;
    source = fopen(origen, "r");
    if( source == NULL ) {
        printf("Error al abrir el archivo %s\n", origen);
        exit(EXIT_FAILURE);
    }
    
    char ruta[255];
    strcpy(ruta, destino);
    if (ruta[strlen(ruta) - 1] != '/')
        strcat(ruta, "/");
    
    char nombre[255], copiaOrigen[255];
    strcpy(copiaOrigen, origen);
    char *ptr = strtok(copiaOrigen, "/");
    while (ptr != NULL) {
        strcpy(nombre, ptr);
        ptr = strtok(NULL, "/");
    }   
    
    strcat(ruta, nombre);

    target = fopen(ruta, "w");
    if(target == NULL ) {
        fclose(source);
        printf("Error al crear el archivo %s\n", ruta);
        exit(EXIT_FAILURE);
    }
    while( ( ch = fgetc(source) ) != EOF )
        fputc(ch, target);
    fclose(source);
    fclose(target);
    
    if (borrar) 
        remove(origen); // elimina el archivo de origen.

    return;
}