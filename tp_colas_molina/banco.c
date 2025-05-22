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
    int i;
    int opcion;
    int codigo_recibido;
    int saldo_recibido;
    char mensaje_cola[100];
    mensaje msg;
    Cliente clientes[CANTIDAD_CLIENTES];

    msg.int_evento=0;

    id_cola_mensajes = creo_id_cola_mensajes(CLAVE_BASE);
    borrar_mensajes(id_cola_mensajes);

    printf("\n --- BANCO ---\n");

    for (i=0;i<100;i++)
    {
        clientes[i].codigo = i;
        clientes[i].saldo = generar_numero_random(0,10000);
    }
    printf("\nClientes generados...\n");


    while(msg.int_evento!=EVT_FIN)
    {
        recibir_mensaje(id_cola_mensajes, MSG_BANCO, &msg);
        // printf("Interaccion recibida de cajero: %d\n", msg.int_rte);

  		switch (msg.int_evento) {
            case EVT_CONSULTA_SALDO:
                if (atoi(msg.char_mensaje) < 0 || atoi(msg.char_mensaje) > CANTIDAD_CLIENTES-1) {
                    sprintf(mensaje_cola, "%d|Cliente no encontrado", atoi(msg.char_mensaje));
                    enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_SALDO_NOK, mensaje_cola);
                    break;
                }
                sprintf(mensaje_cola, "%s|%d", msg.char_mensaje, clientes[atoi(msg.char_mensaje)].saldo);
                enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_SALDO, mensaje_cola);
                break;
            
            case EVT_DEPOSITO:
                printf("Depositando $%d al cliente %d...\n", saldo_recibido, codigo_recibido);
                sscanf(msg.char_mensaje, "%d|%d", &codigo_recibido, &saldo_recibido);
                if (codigo_recibido < 0 || codigo_recibido > CANTIDAD_CLIENTES-1) {
                    sprintf(mensaje_cola, "%d|Cliente no existente",codigo_recibido);
                    enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_DEPOSITO_NOK, mensaje_cola);
                    printf("Cliente no existe\n");
                    break;
                }

                clientes[codigo_recibido].saldo += saldo_recibido;
                sprintf(mensaje_cola, "%d|%d", codigo_recibido, saldo_recibido);
                enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_DEPOSITO_OK, mensaje_cola);
                break;

            case EVT_EXTRACCION:
                printf("Extrayendo $%d del cliente %d...\n", saldo_recibido, codigo_recibido);
                sscanf(msg.char_mensaje, "%d|%d", &codigo_recibido, &saldo_recibido);

                if (codigo_recibido < 0 || codigo_recibido > CANTIDAD_CLIENTES-1) {
                    sprintf(mensaje_cola, "%d|Cliente no existente",codigo_recibido);
                    enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, mensaje_cola);
                    printf("Cliente no existe\n");
                    break;
                }

                if (clientes[codigo_recibido].saldo >= saldo_recibido) {
                    clientes[codigo_recibido].saldo -= saldo_recibido;
                    sprintf(mensaje_cola, "%d|%d", codigo_recibido, saldo_recibido);
                    enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_EXTRACCION_OK, mensaje_cola);
                } else {
                    sprintf(mensaje_cola, "%d|Saldo insuficiente",codigo_recibido, saldo_recibido);
                    enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_RTA_EXTRACCION_NOK, mensaje_cola);
                }
                
                break;

            case EVT_INICIO:
                enviar_mensaje(id_cola_mensajes, MSG_CAJERO, MSG_BANCO, EVT_INICIO, "");
                break;

            default:
                printf("Evento invalido");
                break;
        }

    }

    return 0;
}

