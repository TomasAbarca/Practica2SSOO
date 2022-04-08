Buscador SSOOIIGLE
·EXPLICACIÓN:

El objetivo del programa es la búsqueda paralela de una palabra por parte de N hilos dentro de un archivo. El número de hilos que se creen deberá especificarse por parámetros, además de la ruta donde se encuentre el documento en el que queremos buscar la palabra y la palabra en si. 

Antes de ejecutar el make podemos observar dos directorios, el directorio "include" donde se encuentrann las librerias, y el directorio "src", donde se encuentra el código del programa. 


·EJECUCIÓN DEL PROGRAMA:

-Crear los directorios necesarios para la ejecución del programa: "make dirs"
-Crear los archivos de codigo objeto del programa: "make ssooiigle"
-Combinar los archivos objeto para crear el archivo ejecutable: "make exe"

-Todo lo anterior puede ser creado con la orden "make all".

Hemos creado 3 test que se pueden ejecutar de la siguiente forma:
-make test_a --> Creará 7 hilos que buscarán la palabra "escuela" en el libro "ACTITUD-DE-VENDEDOR.txt".
-make test_b --> Creará 14 hilos que buscarán la palabra "carecen" en el libro "25-MANERAS-DE-GANARSE-A-LA-GENTE.txt".
-make test_c --> Creará 20 hilos que buscarán la palabra "usted" en el libro "SEAMOS-PERSONAS-DE-INFLUENCIA.txt".
-make clean --> Borrará todo lo creado por la funcion make

Si desea ejecutar el programa con otros parámetros el formato a seguir es el siguiente:
./ssooiigle <path_file> <word> <n_threads>

