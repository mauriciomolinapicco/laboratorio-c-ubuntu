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

#define ROJO 0
#define VERDE 1

#define EVT_NINGUNO 0
#define EVT_COMPRA 1
#define EVT_FINALIZAR 2

#define MSG_NADIE 0
#define MSG_SUPER 1
#define MSG_CAJA 2

typedef struct {
    int nro_caja;
    int id_cola_mensaje;
} DatosCaja;

typedef struct {
    int precio;
    char descripcion[100]
} Producto;

#endif

