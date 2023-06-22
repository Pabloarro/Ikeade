/*
 * Fecha.h
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */

#ifndef FECHA_H_
#define FECHA_H_

struct Fecha {
    int dia;
    int mes;
    int anio;
};

void Fecha_getFecha(struct Fecha* fecha, int dia, int mes, int anio);
void Fecha_imprimirFecha(const struct Fecha* fecha);

#endif /* FECHA_H_ */
