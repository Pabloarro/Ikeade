#include "Fecha.h"

void imprimirFecha(const Fecha* fecha) {
    printf("%02d/%02d/%04d\n", fecha->dia, fecha->mes, fecha->anio);
}

void pedirFecha(Fecha** fecha) {
    int dia, mes, anio;

    printf("Ingrese el día: ");
    scanf("%d", &dia);

    printf("Ingrese el mes: ");
    scanf("%d", &mes);

    printf("Ingrese el año: ");
    scanf("%d", &anio);

    *fecha = crearFecha(dia, mes, anio);
}

void liberarFecha(Fecha* fecha) {
    free(fecha);
}
