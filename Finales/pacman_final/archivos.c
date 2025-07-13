#include <stdio.h>
#include "archivos.h"

FILE* abrir_archivo(const char* nombre, const char* modo) {
    FILE* archivo = fopen(nombre, modo);
    if (archivo == NULL) {
        perror("Error al abrir el archivo");
        return NULL;
    }
    return archivo;
}

int cerrar_archivo(FILE* archivo) {
    int resultado;
    if (archivo == NULL) {
        return -1;
    }
    resultado = fclose(archivo);
    if (resultado != 0) {
        perror("Error al cerrar el archivo");
        return -1;
    }
    return 0;
}

int leer_archivo(FILE* archivo, void* buffer, size_t tamano, size_t elementos) {
    size_t leidos;
    if (archivo == NULL || buffer == NULL) {
        return -1;
    }
    leidos = fread(buffer, tamano, elementos, archivo);
    if (leidos != elementos && ferror(archivo)) {
        perror("Error al leer el archivo");
        return -1;
    }
    return (int)leidos; 
}

int escribir_archivo(FILE* archivo, const void* buffer, size_t tamano, size_t elementos) {
    size_t escritos;
    if (archivo == NULL || buffer == NULL) {
        return -1;
    }
    escritos = fwrite(buffer, tamano, elementos, archivo);
    if (escritos != elementos) {
        perror("Error al escribir en el archivo");
        return -1;
    }
    return (int)escritos;
}
