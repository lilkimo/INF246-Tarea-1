
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>


void crear_carpeta(char *direccion, char *carpeta){
   mkdir(strcat(direccio, carpeta),S_IRUSR); // El segundo parametro son los permisos, el que coloque es temporal
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
   //remove(origen); elimina el archivo de origen, dejar comentado hasta probar todo

   return;
}