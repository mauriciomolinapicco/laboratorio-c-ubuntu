#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "clave.h"
#include "funciones.h"
#include "cola.h"
#include "def.h"

int main(int argc, char *argv[])
{
    int id_cola_mensajes;
    mensaje msg;
    Cliente clientes[CANTIDAD_CLIENTES];
    int i;
    int opcion;
    int codigo_cliente_ingresado;
    int saldo_ingresado;
    char mensaje_cola[100];
    char mensaje_recibido[50];
    int codigo_recibido;
    int saldo_recibido;

	id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
	borrar_mensajes(id_cola_mensajes);

    msg.int_evento=0;

    printf("---CAJERO--\n\n");

    enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_INICIO, "");

    while(msg.int_evento!=EVT_FIN)
    {
        printf("-----------------------------\n");
        
        recibir_mensaje(id_cola_mensajes, MSG_CAJERO, &msg);

  		switch (msg.int_evento)
        {
            case EVT_FIN:
                break;
            case EVT_INICIO:
                printf("\n --> Iniciando sesion...\n");
                break;

            case EVT_RTA_SALDO:
                sscanf(msg.char_mensaje, "%d|%d", &codigo_recibido, &saldo_recibido);
                printf("Saldo del cliente %d: $%d\n", codigo_recibido, saldo_recibido);
                break;

            case EVT_RTA_DEPOSITO_OK:
                sscanf(msg.char_mensaje, "%d|%d", &codigo_recibido, &saldo_recibido);
                printf("Cliente %d: se depositaron $%d\n", codigo_recibido, saldo_recibido);
                break;

            case EVT_RTA_EXTRACCION_OK:
                sscanf(msg.char_mensaje, "%d|%d", &codigo_recibido, &saldo_recibido);
                printf("Cliente %d: se extrajo $%d\n", codigo_recibido, saldo_recibido);
                break;

            case EVT_RTA_SALDO_NOK:
                sscanf(msg.char_mensaje, "%d|%[^|]", &codigo_recibido, mensaje_recibido);
                printf("Cliente %d, error: %s\n", codigo_recibido, mensaje_recibido);
                break;

            case EVT_RTA_EXTRACCION_NOK:
                sscanf(msg.char_mensaje, "%d|%[^|]", &codigo_recibido, mensaje_recibido);
                printf("Cliente %d, error al extraer: %s\n", codigo_recibido, mensaje_recibido);
                break;
    
            default:
                printf("\n%s\n", msg.char_mensaje);
                break;
        }

        printf("-----------------------------\n");
        printf("\n Menú \n");
        printf("1. Consultar saldo\n");
        printf("2. Depositar\n");
        printf("3. Extraer\n");
        printf("4. Salir\n");
        printf("Ingrese un número para seleccionar una opción: ");

        scanf("%d", &opcion);

        switch (opcion) {
            case 1:
                printf("CONSULTA DE SALDO\n\n");
                printf("Cual cliente queres consultar?\n");
                scanf("%d", &codigo_cliente_ingresado);
                /*paso el numero a string*/
                sprintf(mensaje_cola, "%d", codigo_cliente_ingresado);

                enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_CONSULTA_SALDO, mensaje_cola);
                break;

            case 2:    
                printf("DEPOSITO.\n");
                printf("A cual cliente depositar?\n");
                scanf("%d", &codigo_cliente_ingresado);
                printf("Cuanto?\n");
                scanf("%d", &saldo_ingresado);
                sprintf(mensaje_cola, "%d|%d", codigo_cliente_ingresado, saldo_ingresado);
                enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_DEPOSITO, mensaje_cola);
                break;

            case 3:
                printf("EXTRACCION.\n");
                printf("De cual cliente extraer?\n");
                scanf("%d", &codigo_cliente_ingresado);
                printf("Cuanto?\n");
                scanf("%d", &saldo_ingresado);
                sprintf(mensaje_cola, "%d|%d", codigo_cliente_ingresado, saldo_ingresado);
                enviar_mensaje(id_cola_mensajes, MSG_BANCO, MSG_CAJERO, EVT_EXTRACCION, mensaje_cola);
                break;

            case 4:
                msg.int_evento = EVT_FIN;
                printf("Saliendo del programa...\n");
                break;

            default:
                printf("Opción no válida. Intente de nuevo.\n");
                break;
        }
    }
    return 0;
}

