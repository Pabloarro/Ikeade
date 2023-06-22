/*
 * ListaArticulos.h
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */

#ifndef LISTAARTICULOS_H_
#define LISTAARTICULOS_H_

#include "Articulo.h"

struct Nodo {
    struct Articulo articulo;
    struct Nodo* siguiente;
};

struct ListaArticulos {
    struct Nodo* primero;
};

void ListaArticulos_CrearLista(struct ListaArticulos* lista);
void ListaArticulos_ImprimirLista(const struct ListaArticulos* lista);
void ListaArticulos_AnyadirArticulo(struct ListaArticulos* lista, const struct Articulo* articulo);
void ListaArticulos_EliminarArticulo(struct ListaArticulos* lista, int id);
struct Articulo* ListaArticulos_ObtenerArticuloMasCaro(const struct ListaArticulos* lista);
struct Articulo* ListaArticulos_ObtenerArticuloMasBarato(const struct ListaArticulos* lista);
void ListaArticulos_OrdenarArticulosPorPrecio(struct ListaArticulos* lista);

#endif /* LISTAARTICULOS_H_ */
