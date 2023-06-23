#include "Fecha.h"

void imprimirFecha(const Fecha* fecha) {
    printf("%02d/%02d/%04d\n", fecha->dia, fecha->mes, fecha->anio);
}

void pedirFecha(Fecha** fecha) {
	*fecha = (Fecha*)malloc(sizeof(Fecha));
	if (*fecha == NULL) {
		return;
	}


    char diaStr[3];
    char mesStr[3];
    char anioStr[5];

    printf("Ingrese el dia: ");
    fgets(diaStr, sizeof(diaStr), stdin);
    sscanf(diaStr, "%d", &((*fecha)->dia));

    printf("Ingrese el mes: ");
    fgets(mesStr, sizeof(mesStr), stdin);
    sscanf(mesStr, "%d", &((*fecha)->mes));

    printf("Ingrese el anio: ");
    fgets(anioStr, sizeof(anioStr), stdin);
    sscanf(anioStr, "%d", &((*fecha)->anio));
}

void liberarFecha(Fecha* fecha) {
    free(fecha);
}
