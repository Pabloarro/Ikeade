#ifndef CARRITO_H_
#define CARRITO_H_

#include "Articulo.h"

typedef struct {
    Articulo** articulos;
    int cantidad;
} Carrito;

void inicializarCarrito(Carrito* carrito);
void agregarArticuloCarrito(Carrito* carrito, Articulo* articulo);
void eliminarArticuloCarrito(Carrito* carrito, int indice);
void modificarArticuloCarrito(Carrito* carrito, int indice, float nuevoPrecio);


#endif
