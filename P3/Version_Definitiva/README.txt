En este documento vamos a comentar el funcionamiento de todas las clases, así como muchas decisiones de diseño que
hemos tomado y hemos tenido que implementar.

Terminaremos con una breve demostración de lo que tendríamos que poner en la consola para ejecutar nuestra
práctica.

-----------------------------
FUNCIONAMIENTO DE LA PRÁCTICA
-----------------------------

SSOOIIGLE.cpp - Es el .cpp principal de la práctica. Aquí es donde hemos tomado las primeras decisiones de diseño.
                Cada cliente que creamos es un hilo (hay tantos clientes como la variable definida en "Lib.h", 
                CLIENTS nos indica). Por otro lado, también creamos buscadores. Cada buscador será un hilo, 
                y habrá tantos como N réplicas pueden ejecutarse, y según el enunciado son 4. 
                Esto lo controlamos con otra variable en "Lib.h", CONCURRENT_CLIENTS. 
                Aquí también creamos el sistema de pago, mediante un único hilo.

Client.cpp - Esta clase será la que almacene todos los datos propios de un cliente, así como tendrá implementados
             los métodos que sean necesarios para controlar el funcionamiento correcto del sistema. 
             El funcionamiento de esta clase consistirá en que los clientes realizarán una petición que consiste 
             en una búsqueda a través de los libros. Tras hacer esta petición, quedarán bloqueados 
             hasta que consigamos los resultados oportunos. Los resultados, tanto de tiempo como de coincidencias, 
             aparecerán en el directorio de cada cliente situado en la carpeta creada en tiempo de ejecución "Clients". 
             Aparecerán en formato txt.

SearchRequest.cpp - Aquí almacenaremos la información sobre la petición que haga el cliente. Según hemos simplificado con
                    el enunciado, sus atributos serán el id del cliente, la palabra que desea buscar y la prioridad 
                    (prioridad, que según el enunciado hemos dividido en 2 posibles valores: 
                    0 para los usuarios de cuenta gratuita, y 1 para los usuarios premium con límite de saldo 
                    y los usuarios premium sin límite de saldo).

ProtectedSearchVector.cpp - El propósito de esta clase es proteger el vector de peticiones. Lo hacemos a través de un
                            semáforo.

SearchSystem.cpp - Es una de las clases más importantes. Aquí, cogeremos las peticiones realizadas por los clientes, y con
                   una prioridad del 80%-20% realizaremos las diferentes búsquedas en los diferentes libros.
                   Cabe destacar que, el buscador estará bloquedao si no hay peticiones que tratar.

PaymentReload.cpp - Esta clase está implementada para poder recargar el saldo de los usuarios premium con límite de saldo.

PaySystem.cpp - Es otra clase importantísima para el desarrollo de nuestra práctica. Aquí nos encargamos de permanecer
                bloqueados a la espera de que un cliente nos necesite. Destacamos que no es un servicio anónimo, ya que
                el sistema de pago conoce la identidad del cliente.

MediatorySearch.cpp - Esta clase intermediaria es creada para mandar los resultados desde el sistema de búsqueda a
                      los usuarios. Los resultados se almacenan en un vector.

ProtectedMediatoryVector.cpp - El objetivo de esta clase es proteger el vector anterior con un semáforo.

LineResult.cpp - Esta clase se encarga de guardar los resultados de las búsquedas y mostrarlos.

ThreadResult.cpp - Esta clase es muy parecida a la anterior, solo que guarda los resultados por la parte del hilo.

SearchLibrary.cpp - Aquí implementamos muchos de los métodos que en la práctica son importantes, ya que realizamos
                    varias operaciones sobre los libros en los que buscamos.

OrderQueue.cpp - Esta clase simplemente ordena las instancias de la cola.

Lib.h - Es un archivo de cabecera donde se encuentran las diferentes variables definidas que nos ayudan a no tener
        líneas de código en el main innecesarias.

--------------------------------------------
COMO EJECUTAR LA PRÁCTICA EN NUESTRA MÁQUINA
--------------------------------------------

Primero, destacar que la práctica lee en todos los libros que le indiquemos en "Lib.h". No obstante,
para hacer pruebas solo hemos utilizado 4 de ellos.

Con el fin de facilitar la ejecución del proyecto, hemos creado un archivo Makefile, con el que,
a través de comandos muy sencillos, podremos compilar, ejecutar y borrar directorios de nuestra práctica.

1.- Nos situamos en el directorio donde tengamos descargado nuestro proyecto.
2.- Escribimos "make all". Con esto compilaremos los archivos necesarios para la ejecución.
3.- Escribimos "make execute". Tras esto, se iniciará la ejecución de nuestra práctica.
4.- Para terminar el programa (podremos hacerlo en cualquier momento), pulsamos la combinación de teclas "CTRL + C".
5.- Una vez finalizada la ejecución, si deseamos volver a ejecutar lo más apropiado es escribir "make clean", que
    se encargará de borrar carpetas y archivos innecesarios.
