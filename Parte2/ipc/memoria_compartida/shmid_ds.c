/*
estructura shmid_ds contiene información importante sobre la memoria compartida
*/
struct shmid_ds {
    struct ipc_perm shm_perm; // Permisos de la memoria compartida
    size_t shm_segsz;         // Tamaño de la memoria compartida en bytes
    time_t shm_atime;         // Última vez que fue accedida
    time_t shm_dtime;         // Última vez que fue detachada
    time_t shm_ctime;         // Última vez que se cambió la memoria
    pid_t shm_cpid;           // ID del proceso que creó la memoria
    pid_t shm_lpid;           // ID del último proceso que la usó
    shmatt_t shm_nattch;      // Número de procesos que están usando la memoria
};
