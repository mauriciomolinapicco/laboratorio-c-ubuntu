Ejecutar el comando "make"

Para ejecutar el panel
./panel

Para ejecutar cada uno de los sistemas que procesan los menues:
./avion 1
./avion 2
./avion 3

El panel lee los datos del archivo aviones.txt, al que escriben los aviones. 
Se han usado semaforos para el acceso sincronizado a los archivos

Se pueden correr los procesos en cualquier orden.

Se han utilizado señales, por lo tanto si se ejecuta control C se terminaran los procesos liberando la memoria utilizada.