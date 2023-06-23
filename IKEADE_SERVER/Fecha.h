#ifndef FECHA_H_
#define FECHA_H_

struct Fecha {
    int dia;
    int mes;
    int anio;
};

void Fecha_getFecha(struct Fecha* fecha, int dia, int mes, int anio);
void Fecha_imprimirFecha(const struct Fecha* fecha);

#endif
