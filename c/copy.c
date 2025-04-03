#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void) {
    /* CREAR UNA COPIA QUE REFERENCIA AL MISMO OBJETO */
    char s[] = "hola";

    char *t = s;

    // compruebo que len de t es mayor a 0
    if (strlen(t) > 0) {
        // Hago la primera letra de t mayuscula
        t[0] = toupper(t[0]);
    }
    

    //compruebo que el cambio afecto a ambos
    printf("%s\n", s);
    printf("%s\n", t);

    /*-----------------*/

    /* CREAR UNA COPIA EN SERIO, QUE TIENE OTRO ESPACIO DE MEMORIA*/
    char s2[] = "hola";

    /*
    malloc = memory allocate
    arg = cantidad de bytes que quiero que reserve
    devuelve NULL si no hay memoria suficiente
    */
    char *t2 = malloc(strlen(s2) + 1); //se agrega uno por el \0
    if (t2 == NULL) 
    {
        return 1;
    }
    
    strcpy(t, s); //is the same as:
    // for (int i = 0, n = strlen(s2); i <= n; i++) 
    // {
    //     t2[i] = s2[i];
    // }

    if (strlen(t2) > 0) 
    {
        t2[0] = toupper(t2[0]);
    }
    
    printf("%s\n", s2); //hola
    printf("%s\n", t2); //Hola

    free(t2);
    // Siempre liberar cuando usamos malloc
    return(0);
}