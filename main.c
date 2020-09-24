#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Llamadas al Sistema
#include <sys/syscall.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <dirent.h> // Sirve para acceder a las carpetas.

#define STRINGBUFFER 255
#define JUEGOSBUFFER 255

typedef struct {
    char nombre[STRINGBUFFER];
    char categoria[STRINGBUFFER];
    char autor[STRINGBUFFER];
    char resumen[STRINGBUFFER];
    
    int cantidadCategorias;
} juego;

juego obtenerJuego(char* direccion) {
    juego juego;
    
    FILE *fp;
    char linea[STRINGBUFFER];
    fp = fopen(direccion, "r");
    if (fp == NULL) {
        printf("Error al abrir el archivo %s", direccion);   
        exit(1);             
    }

    fgets(linea, 255, fp);
    linea[strcspn(linea, "\n")] = 0;
    strcpy(juego.nombre, linea);
    
    fgets(linea, STRINGBUFFER, fp);
    char *ptr = strtok(linea, ", ");
    strcpy(juego.categoria, ptr);
    juego.categoria[strcspn(juego.categoria, "\n")] = 0;

    juego.cantidadCategorias = 0;
    while (ptr != NULL) {
        juego.cantidadCategorias++;
		ptr = strtok(NULL, ",");
    }

    fgets(linea, STRINGBUFFER, fp);
    linea[strcspn(linea, "\n")] = 0;
    strcpy(juego.autor, linea);
    
    fgets(linea, STRINGBUFFER, fp);
    linea[strcspn(linea, "\n")] = 0;
    strcpy(juego.resumen, linea);
    

    fclose(fp);
    return juego;
}

juego * obtenerJuegos(int *largo) {
    juego *juegos;
    int indice = 0;

    char raiz[] = "./juegos/";
    char direccion[STRINGBUFFER];
    char *extension;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(raiz)) != NULL) {
        juegos = (juego *)malloc(sizeof(juego)*JUEGOSBUFFER);
        
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
        perror("Error al abrir la carpeta juegos");
    
    *largo = indice;
    return juegos;
}
void crear_carpeta(char *carpeta){
    mkdir(carpeta,S_IRUSR); // El segundo parametro son los permisos, el que coloque es temporal
    return;
}

void copiar_archivo(char *destino, char *origen) {
   char ch;
   FILE *source, *target;
   source = fopen(origen, "r");
   if( source == NULL ) {
      printf("Error al abrir el archivo\n");
      exit(EXIT_FAILURE);
   }
   target = fopen(destino, "w");
   if( target == NULL ) {
      fclose(source);
      printf("Error al crear el archivo\n");
      exit(EXIT_FAILURE);
   }
   while( ( ch = fgetc(source) ) != EOF )
      fputc(ch, target);
   fclose(source);
   fclose(target);
   return;
}




int main() {
    int largo;
    juego *juegos = obtenerJuegos(&largo);
    /*
    for (int i = 0; i < largo; i++) {
        printf("%s\n", juegos[i].nombre);
        for (int j = 0; j < juegos[i].cantidadCategorias; j++)
            printf("%s, ", juegos[i].categorias[j]);
        printf("\n");
        printf("%s\n", juegos[i].autor);
        printf("%s\n", juegos[i].resumen);
    }
    */

    return 0;
}