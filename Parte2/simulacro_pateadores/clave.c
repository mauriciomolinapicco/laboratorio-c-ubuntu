#include <sys/types.h>
#include <sys/ipc.h>
#include <stdio.h>
#include <stdlib.h>
#include "def.h"
#include "clave.h"

key_t creo_clave(int clave_base) {
    key_t clave;
    clave = ftok("/bin/ls", clave_base);
    if (clave == (key_t)-1) {
        printf("No puedo conseguir clave de semaforo\n");
        exit(0);
    }
    return clave;
}
