# Integrantes
Camilo Gonzalez, 201873550-7

Zarko Kuljis, 201823523-7
# Consideraciones
Se asume como juego a todo archivo con la extensión .txt

Cada línea de los archivos debe tener 255 carácteres o menos.

Cada parámetro de los juegos (Nombre, Categorías, Empresa Autora y Resumen) debe ocupar exactamente una línea.

La Consola sólo indexa un directorio a la vez (Es decir, comandos como `open Shooter/Valorant.txt` no funcionarán, y se deberá actuar de la forma `cd Shooter` y luego `open Valorant.txt`).

**Al finalizar el programa se borrará todo el contenido dentro de la carpeta 'categorias'.** Esto para evitar conflictos con el uso posterior.

**Debe** usar el comando `exit`. Finalizar a la fuerza el programa puede ocasionar el **mal funcionamiento** del mismo.
Si usted se encuenta en esta situación una posible solución es **borrar la carpeta 'categorías'**.
# Comandos de Consola:
exit: Finaliza el programa.

ls: Muestra los contenidos de la carpeta actual.

cd \<Nombre de la carpeta\>: Avanza a la carpeta de nombre \<Nombre de la carpeta\>. Si es ' .. ', retrocede a la carpeta anterior.

open \<Nombre del Juego\>: Muestra los contenidos del juego, que deberá ser un .txt que cumpla los requisitos impuestos por el enunciado.