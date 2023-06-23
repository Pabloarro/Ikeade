#include "carrito.h"
#include <stdio.h>
#include <stdlib.h>

void inicializarCarrito(Carrito* carrito) {
    carrito->articulos = (Articulo**)malloc(10 * sizeof(Articulo*));
    carrito->cantidad = 0;
}

void agregarArticuloCarrito(Carrito* carrito, Articulo* articulo) {
    if (carrito->cantidad >= 10) {
        printf("El carrito está lleno. No se puede agregar más artículos.\n");
        return;
    }

    carrito->articulos[carrito->cantidad] = articulo;
    carrito->cantidad++;
}

void eliminarArticuloCarrito(Carrito* carrito, int indice) {
    if (indice >= 0 && indice < carrito->cantidad) {
        free(carrito->articulos[indice]);

        for (int i = indice; i < carrito->cantidad - 1; i++) {
            carrito->articulos[i] = carrito->articulos[i + 1];
        }

        carrito->cantidad--;
    } else {
        printf("Índice inválido. No se puede eliminar el artículo.\n");
    }
}

void modificarArticuloCarrito(Carrito* carrito, int indice, float nuevoPrecio) {
    if (indice >= 0 && indice < carrito->cantidad) {
        carrito->articulos[indice]->precio = nuevoPrecio;
    } else {
        printf("Índice inválido. No se puede modificar el artículo.\n");
    }
}
