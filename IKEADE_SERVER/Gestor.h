#ifndef GESTOR_H_
#define GESTOR_H_

#include "Articulo.h"
#include "ListaArticulos.h"
#include "Venta.h"


typedef struct {
    Venta** ventas;
    int cantidadVentas;
    int capacidadVentas;
} Gestor;

void guardarArticulos(const ListaArticulos* lista, const char* nombreArchivo);
void cargarArticulos(ListaArticulos* lista, const char* nombreArchivo);

void aniadirArticuloFich(Articulo* articulo);
void eliminarArticuloFich(Articulo* articulo);
void imprimirArticuloFichero(FILE* pf, Articulo* articulo);
void imprimirFechaActualFichero(FILE * pf);
void visualizarVentas(const Gestor* gestor);
void visualizarVentasPorCliente(const Gestor* gestor);



#endif
