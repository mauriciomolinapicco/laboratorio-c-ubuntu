# Sistema de medicamentos
Este proyecto simula un sistema gestion de medicamentos, con control distribuido por cantidad de medicamentos. Está desarrollado en C, pensado para ser compilado en Linux con `gcc` versión 4.1.3.

## Descripción
Cada medicamento se empaqueta en 5, 10 o 20 pastillas, ademas tiene un tipo y un color


Cada consumidor:
- Lee los medicamentos que le corresponden desde el archivo.
- Imprime en pantalla cada pedido procesado y un resumen total de los pedidos de su tipo.
- Revisa si hay nuevos medicamentos cada 100 ms.
- Usa semáforos para sincronizar el acceso al archivo y evitar condiciones de carrera.

## Compilación
El proyecto incluye un `Makefile` el cual se compila utilizando el comando "make"

## Ejecución
./productor
./consumidor A
./consumidor B
./consumidor C