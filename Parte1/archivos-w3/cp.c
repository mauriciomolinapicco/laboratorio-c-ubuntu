#include <stdio.h>
#include <stdint.h>

/*
Programa que me copia un archivo byte a byte
Le paso como parametro el nombre del archivo a 
copiar y el destino a donde se va a copiar
*/

// uint8_t = unsigned integer de 8 bits
typedef uint8_t BYTE;

int main(int argc, char *argv[]) 
{
    FILE *src = fopen(argv[1], "rb"); // rb=read binary
    FILE *dst = fopen(argv[2], "wb");

    BYTE b;

    // lee byte por byte y si contiene algo (la funcion devuelve != 0) sigo escribiendo
    while (fread(&b, sizeof(b), 1, src) != 0)
    {
        fwrite(&b, sizeof(b), 1, dst);
    }

    fclose(dst);
    fclose(src);
}