#ifndef FECHA_H_
#define FECHA_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int dia;
    int mes;
    int anio;
} Fecha;

void imprimirFecha(const Fecha* fecha);
void pedirFecha(Fecha** fecha);
void liberarFecha(Fecha* fecha);

#endif
