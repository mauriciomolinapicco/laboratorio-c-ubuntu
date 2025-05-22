#ifndef DEF_H
#define DEF_H

#define INTERVALO 100000 /* 100ms en microsegundos */
#define CLAVE_BASE 33
#define ROJO 0
#define VERDE 1
#define LARGO_CADENA 50

#define CANTIDAD_CLIENTES 100

/*codigos de evento*/
#define EVT_CONSULTA_SALDO 1
#define EVT_DEPOSITO 2
#define EVT_EXTRACCION 3
#define EVT_RTA_SALDO 4
#define EVT_RTA_SALDO_NOK 5
#define EVT_RTA_DEPOSITO_OK 6
#define EVT_RTA_DEPOSITO_NOK 7
#define EVT_RTA_EXTRACCION_OK 8
#define EVT_RTA_EXTRACCION_NOK 9
#define EVT_FIN 10
#define EVT_INICIO 11

/*codigos de remitentes*/
#define MSG_BANCO 1
#define MSG_CAJERO 100

typedef struct {
    int codigo;
    int saldo;
} Cliente;

#endif
