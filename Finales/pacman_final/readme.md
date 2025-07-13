make para compilar 

./panel => para ejecutar el panel, que muestra lo que va ocurriendo

./jugadores => se debe ejecutar para correr el programa jugadores. Este es el que lanza un thread por jugador. Cada thread tiene su logica individual y se sincronizan con mutex. Por otro lado comparten una variable (se le pasa el puntero) llamada termino para que ambos sepan cuando terminar

Se usa memoria compartida para que el inicio de los programas por lo tanto los procesos se pueden correr en cualquier orden y semaforos para restringir el acceso a memoria compartida.
Tambien se usa para comunicar entre procesos la cantidad de pasos que deben realizar para ganar la partida

La comunicacion entre procesos durante el juego se realiza mediante cola de mensajes.


