Ejecutar el comando "make"

Para ejecutar el productor
./productor

Para ejecutar cada uno de los sistemas que procesan los menues:
./consumidor 1
./consumidor 2
./consumidor 3

Cada consumidor N lee de su correspondiente archivo panelN.txt los datos.
Se han usado semaforos para el acceso sincronizado a los archivos

Se pueden correr los procesos en cualquier orden.

Se han utilizado señales, por lo tanto si se ejecuta control C se terminaran los procesos liberando la memoria utilizada.