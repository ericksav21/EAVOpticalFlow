Notas:
-Para usar este programa es necesario tener instalado el framework OpenCV.
-Los conjuntos de imágenes deben estar dentro de la carpeta 'images', la salida del programa se generará en la carpeta 'out'.
-El programa generará diversos archivos de salida para un cierto conjunto de imágenes, en específico: las imágenes de las derivadas espaciales y con respecto al tiempo, dos archivos de imagen conteniendo los vectores de flujo, un archivo de texto con el resumen de la ejecución.
-Si se quiere hacer pruebas de Ground Truth se requiere tener los archivos .flo dentro de la carpeta 'test'. Las imágenes que están en el conjunto de Ground Truth son: Crate, GrassSky, GroveSun y TxtR.
-Se puede usar cualquier formato válido de bitmap para generar el flujo, aunque el algoritmo siempre convertirá la imagen a escala de grises y en base a ella trabajará.

-Para compilar ejecuta el comando 'make' sin comillas.
-Para ver todas las opciones con las que cuenta el archivo Makefile escribe: 'make help' sin comillas.
-Para ver todos los parámetros que recibe el programa escribe: './main --help' sin comillas.
-Un ejemplo de ejecución es el siguiente:
Nos situamos en la carpeta raíz y escribimos:

./main -F1 TxtR1.png -F2 TxtR2.png --lambda 5000 -A GS --toler 0.01 --iter 3000 --scale 3 --test TxtR.flo

Para el ejemplo anterior estamos diciendo que el programa recibe la secuencia de imágenes: TxtR1.png y TxtR2.png, el parámetro lambda será de 5000, el algoritmo que se usará será Gauss-Seidel (Para gradiente por paso fijo escribir: GPF), se tomará una tolerancia máxima de 0.01 y un número máximo de 3000 iteraciones, se indica un valor de escalamiento de 3 para ver mejor los vectores de flujo. Por último se quiere hacer una prueba de Ground-Truth con el archivo TxtR.flo el cual está en la carpeta 'test'.

