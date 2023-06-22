/*
 * Fecha.c
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */


#include "fecha.h"
#include <stdio.h>

void Fecha_getFecha(struct Fecha* fecha, int dia, int mes, int anio) {
    fecha->dia = dia;
    fecha->mes = mes;
    fecha->anio = anio;
}

void Fecha_imprimirFecha(const struct Fecha* fecha) {
    printf("Fecha: %02d/%02d/%04d\n", fecha->dia, fecha->mes, fecha->anio);
}
