#ifndef ARCHIVOS_H
#define ARCHIVOS_H

FILE* abrir_archivo(const char* nombre, const char* modo);
int cerrar_archivo(FILE* archivo);
int leer_archivo(FILE* archivo, void* buffer, size_t tamano, size_t elementos);
int escribir_archivo(FILE* archivo, const void* buffer, size_t tamano, size_t elementos);

#endif
