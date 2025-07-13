make para compilar

./panel => para ejecutar el panel, que muestra lo que va ocurriendo

./jugadores => se debe ejecutar para correr el programa jugadores. Este es el que lanza un thread por jugador 6 en total. Cada thread tiene su logica individual y se sincronizan con mutex. Por otro lado se comparten variables pasadas por punteros 

Los procesos se pueden correr en cualquier orden porque usan memoria compartida y semaforos para sincronizar el inicio

Se usa memoria compartida para que el inicio de los programas por lo tanto los procesos se pueden correr en cualquier orden y semaforos para restringir el acceso a memoria compartida.
Tambien se usa para comunicar entre procesos la cantidad de metros que deben los peces para salvarse (o los pulpos/tiburones para comerlos o danarlos)

La comunicacion entre procesos durante el juego se realiza mediante cola de mensajes y memoria compartida para comunicarse la cantidad de metros

Consideraciones:
Para el juego se considera que si a los atacantes les sale 1 el pez o los peces danado/s (que esten en el radio) se muere/n 

