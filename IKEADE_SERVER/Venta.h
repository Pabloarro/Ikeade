#ifndef VENTA_H_
#define VENTA_H_

#include "Cliente.h"
#include "Articulo.h"
#include "Fecha.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Cliente* cliente;
    float precioTotal;
    char* nombre;
} Venta;

Venta* crearVenta(Cliente* cliente);
Venta* crearVenta2(char* nombre);
void agregarArticulo(Venta* venta, Articulo* articulo);
void calcularPrecioTotal(Venta* venta);
void imprimirVenta(Venta* venta);
void liberarVenta(Venta* venta);

#endif
