#include <sys/shm.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ROJO               0      //‑‑Valores útiles si quisieras 2 estados
#define VERDE              1
#define CANTIDAD           100    // Tamaño del vector compartido
#define DESDE_IMPORTE      10
#define HASTA_IMPORTE      50
#define DESDE_CHEQUE       0      // 0 = efectivo, 1 = cheque
#define HASTA_CHEQUE       1
#define DESDE_INTERVALO    1000   // ms entre depósitos aleatorios
#define HASTA_INTERVALO    2500
#define CANT_SEMAFORO      1
#define CAJERO             1      // Nº por defecto

typedef struct {
    int cajero;   // Nº de cajero
    int importe;  // Monto
    int cheque;   // 0‑efectivo 1‑cheque
    int listo;    // 1 = registro listo para tesorero
} dato;

/* —— Herramientas de IPC ————————————————————————————————*/
static key_t  creo_clave(void) {
    key_t k = ftok("/bin/ls", 33);
    if (k==(key_t)-1){ perror("ftok"); exit(EXIT_FAILURE); }
    return k;
}
static void *creo_memoria(size_t size, int *id) {
    *id = shmget(creo_clave(), size, 0777|IPC_CREAT);
    if (*id==-1){ perror("shmget"); exit(EXIT_FAILURE); }
    void *p = shmat(*id,NULL,0);
    if (p==(void*)-1){ perror("shmat"); exit(EXIT_FAILURE); }
    return p;
}
static int   creo_semaforo(void){
    int id = semget(creo_clave(), CANT_SEMAFORO, 0600|IPC_CREAT);
    if(id==-1){ perror("semget"); exit(EXIT_FAILURE); }
    return id;
}
static void  espera_semaforo (int id){ struct sembuf op={0,-1,0}; semop(id,&op,1); }
static void  levanta_semaforo(int id){ struct sembuf op={0, 1,0}; semop(id,&op,1); }

/* —— Proceso CAJERO ————————————————————————————————*/
int main(int argc,char *argv[])
{
    int cajero = (argc>1)? atoi(argv[1]): CAJERO;
    printf("Cajero %d en marcha\n", cajero);

    srand(time(NULL)-cajero);           // semilla distinta por cajero

    int id_mem, id_sem = creo_semaforo();
    dato *mem = (dato*)creo_memoria(sizeof(dato)*CANTIDAD, &id_mem);

    for(;;){
        /* Genera un “depósito” aleatorio */
        int importe = rand()%(HASTA_IMPORTE-DESDE_IMPORTE+1)+DESDE_IMPORTE;
        int cheque  = rand()%(HASTA_CHEQUE -DESDE_CHEQUE +1)+DESDE_CHEQUE;

        /* Entra a zona crítica y busca hueco libre */
        espera_semaforo(id_sem);
        int pos=-1;
        for(int i=0;i<CANTIDAD && pos==-1;i++){
            if(mem[i].listo==0){          // ranura libre
                pos=i;
                mem[pos].cajero  = cajero;
                mem[pos].importe = importe;
                mem[pos].cheque  = cheque;
                mem[pos].listo   = 1;     // marca “dato listo”
            }
        }
        levanta_semaforo(id_sem);         // sale de zona crítica

        /* Salida por pantalla para ver qué hizo */
        if(pos!=-1){
            printf("[Cajero %d] -> pos %d | $%d | %s\n",
                   cajero,pos,importe, cheque?"cheque":"efectivo");
        }

        /* Espera aleatoria antes del próximo depósito */
        int pausa = rand()%(HASTA_INTERVALO-DESDE_INTERVALO+1)+DESDE_INTERVALO;
        usleep(pausa*1000);
    }
    return 0;
}
