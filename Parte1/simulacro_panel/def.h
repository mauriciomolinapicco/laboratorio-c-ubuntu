#ifndef DEF_H
#define DEF_H

#define INTERVALO 100000 /* 100ms en microsegundos */
#define CLAVE_BASE 33
#define ROJO 0
#define VERDE 1
#define LARGO_MENSAJE 100
#define DEFAULT_MSG "default"


typedef struct {
    int nro_panel;
    char mensaje[LARGO_MENSAJE];
} Panel;

#endif
