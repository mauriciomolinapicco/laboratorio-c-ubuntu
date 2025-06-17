#ifndef DEF_H
#define DEF_H

#define CLAVE_BASE 33

/*
Por ahora uso define normal
typedef enum {
    EVT_NINGUNO,
    EVT_INICIO,
    EVT_DISPARO,
    EVT_SALVADO,
    EVT_FIN,
} Mensaje; */

#define EVT_NINGUNO 0
#define EVT_INICIO 1
#define EVT_TIRO 2
#define EVT_GOL 3
#define EVT_PALO 4
#define EVT_TRAVESANO 5
#define EVT_FUERA 6

#define MSG_NADIE 0
#define MSG_ARQUERO 1
#define MSG_PATEADOR 2

typedef struct {
    int nro_pateador;
    int id_cola_mensaje;
} DatosPateador;

typedef struct {
    int tiro;
} Pateador;

#endif

