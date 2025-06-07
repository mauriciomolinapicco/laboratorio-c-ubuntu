#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("INICIANDO PANEL DE RUGBY...\n");

    // Usar xterm (más compatible con sistemas antiguos)
    system("xterm -hold -e ./marcador &");
    system("xterm -hold -e ./equipo 1 &");
    system("xterm -hold -e ./equipo 2 &");

    printf("Todos los procesos han sido lanzados.\n");
    return 0;
}