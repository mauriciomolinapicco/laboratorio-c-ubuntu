#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROJO                0          //‑‑Valores “semáforo en rojo / verde”
#define VERDE               1
#define CANTIDAD            100        // Elementos del vector compartido
#define DESDE_IMPORTE       10         // Rango de importes aleatorios
#define HASTA_IMPORTE       50
#define DESDE_CHEQUE        0          // 0 = efectivo, 1 = cheque
#define HASTA_CHEQUE        1
#define INTERVALO           5000       // ms entre iteraciones (default)
#define SEMAFORO0           0
#define CANT_SEMAFORO       1
#define CANT_MAX_CAJEROS    3

/* —— Estructura que vive en la memoria compartida — */
typedef struct {
    int cajero;   // Nº de cajero que hizo el depósito (1–3)
    int importe;  // Monto depositado
    int cheque;   // 0 = efectivo | 1 = cheque
    int listo;    // 1 = registro listo para procesar, 0 = ya tomado
} dato;

/* —— Utilidades de memoria compartida — */
static key_t creo_clave(void) {
    key_t clave = ftok("/bin/ls", 33);              // misma clave para SHM y SEM
    if (clave == (key_t)-1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }
    return clave;
}

static void *creo_memoria(size_t size, int *id_memoria) {
    *id_memoria = shmget(creo_clave(), size, 0777 | IPC_CREAT);
    if (*id_memoria == -1) { perror("shmget"); exit(EXIT_FAILURE); }

    void *ptr = shmat(*id_memoria, NULL, 0);
    if (ptr == (void *)-1) { perror("shmat"); exit(EXIT_FAILURE); }
    return ptr;
}

/* —— Utilidades de semáforos — */
static int creo_semaforo(void) {
    int id = semget(creo_clave(), CANT_SEMAFORO, 0600 | IPC_CREAT);
    if (id == -1) { perror("semget"); exit(EXIT_FAILURE); }
    return id;
}
static void inicia_semaforo(int id, int valor)  { semctl(id, 0, SETVAL, valor); }
static void espera_semaforo(int id)             { struct sembuf op={0,-1,0}; semop(id,&op,1); }
static void levanta_semaforo(int id)            { struct sembuf op={0, 1,0}; semop(id,&op,1); }

/* —— Proceso TESORERO —— */
int main(int argc, char *argv[])
{
    int intervalo = (argc>1) ? atoi(argv[1]) : INTERVALO;

    /* 1.  Preparo sincronización y memoria */
    int id_memoria, id_sem = creo_semaforo();
    inicia_semaforo(id_sem, VERDE);                // sem = 1 → región libre
    dato *mem = (dato *)creo_memoria(sizeof(dato)*CANTIDAD, &id_memoria);

    /* 2. Inicializo vector de registros */
    for (int i=0;i<CANTIDAD;i++) mem[i].listo = 0;

    /* 3. Acumuladores globales y por cajero */
    int TCD=0,TCE=0,TCC=0,T$D=0,T$E=0,T$C=0;
    int vTCD[3]={0}, vTCE[3]={0}, vTCC[3]={0};
    int v$D [3]={0}, v$E [3]={0}, v$C [3]={0};

    /* 4. Bucle principal */
    for (;; usleep(intervalo*1000)) {
        espera_semaforo(id_sem);                   // entra a zona crítica

        for (int i=0; i<CANTIDAD; i++) {
            if (mem[i].listo == 1 && mem[i].cajero<=CANT_MAX_CAJEROS) {
                /* Toma registro y acumula */
                mem[i].listo = 0;
                int k = mem[i].cajero-1;
                TCD++;             vTCD[k]++;
                T$D += mem[i].importe; v$D[k] += mem[i].importe;

                if (mem[i].cheque==0) {            // efectivo
                    TCE++;             vTCE[k]++;
                    T$E += mem[i].importe; v$E[k] += mem[i].importe;
                } else {                           // cheque
                    TCC++;             vTCC[k]++;
                    T$C += mem[i].importe; v$C[k] += mem[i].importe;
                }
            }
        }

        /* Muestra de estadísticas (limpia pantalla) */
        system("clear");
        printf("=== Totales generales ===\n");
        printf("Depósitos: %d  $%d\n", TCD, T$D);
        printf("   Efectivo: %d  $%d\n", TCE, T$E);
        printf("   Cheques : %d  $%d\n\n", TCC, T$C);

        for(int k=0;k<CANT_MAX_CAJEROS;k++){
            printf("-- Cajero %d --\n",k+1);
            printf("Depósitos: %d  $%d\n", vTCD[k], v$D[k]);
            printf("   Efectivo: %d  $%d\n", vTCE[k], v$E[k]);
            printf("   Cheques : %d  $%d\n\n", vTCC[k], v$C[k]);
        }
        levanta_semaforo(id_sem);           // libera zona crítica
    }

    /* Nunca llega, pero incluir limpieza es buena práctica */
    shmdt(mem);
    shmctl(id_memoria, IPC_RMID, NULL);
    return 0;
}
