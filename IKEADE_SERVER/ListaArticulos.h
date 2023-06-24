#ifndef LISTAARTICULOS_H_
#define LISTAARTICULOS_H_

#include "Articulo.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    Articulo** articulos;
    int cantidad;
} ListaArticulos;

ListaArticulos* crearListaArticulos();
void anyadirListaArticulos(ListaArticulos* lista, Articulo* articulo);
void eliminarListaArticulos(ListaArticulos* lista, int id);
Articulo* obtenerArticuloMasCaro(const ListaArticulos* lista);
Articulo* obtenerArticuloMasBarato(const ListaArticulos* lista);
void ordenarArticulosPorPrecio(ListaArticulos* lista);
void imprimirListaArticulos(const ListaArticulos* lista);
char* convertirListaArticuloAString(const ListaArticulos* lista);
void liberarListaArticulos(ListaArticulos* lista);

#endif
