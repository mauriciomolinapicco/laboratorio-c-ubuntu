#ifndef _ARCHIVOS
#define _ARCHIVOS

int inAbrirArchivo(char *szNombre,char *szModo);
void voCerrarArchivo(void);
int inLeerArchivo(char *szTextoADevolver, int sizeTexto);
int inEscribirArchivo(char *szTexto);
int inRenombrarArchivo(char *szNombreViejo, char *szNombreNuevo);
int inFinArchivo(void);

#endif
