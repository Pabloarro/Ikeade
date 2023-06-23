#include "Venta.h"
#include <stdio.h>
#include <stdlib.h>

Venta* crearVenta(Cliente* cliente, Fecha* fecha) {
    Venta* venta = (Venta*)malloc(sizeof(Venta));
    venta->cliente = cliente;
    venta->articulos = crearListaArticulos();
    venta->fecha = fecha;
    venta->precioTotal = 0.0;
    return venta;
}

void agregarArticulo(Venta* venta, Articulo* articulo) {
    insertarArticulo(venta->articulos, articulo);
}

void calcularPrecioTotal(Venta* venta) {
    NodoArticulo* nodo = venta->articulos->primerNodo;
    venta->precioTotal = 0.0;
    while (nodo != NULL) {
        venta->precioTotal += nodo->articulo->precio;
        nodo = nodo->siguiente;
    }
}

void imprimirVenta(Venta* venta) {
    printf("Venta:\n");
    printf("Cliente: %s\n", venta->cliente->nombre);
    printf("Fecha: %d/%d/%d\n", venta->fecha->dia, venta->fecha->mes, venta->fecha->anio);
    printf("Artículos:\n");
    NodoArticulo* nodo = venta->articulos->primerNodo;
    while (nodo != NULL) {
        printf("- %s\n", nodo->articulo->nombre);
        nodo = nodo->siguiente;
    }
    printf("Precio Total: %.2f\n", venta->precioTotal);
}

void liberarVenta(Venta* venta) {
    liberarListaArticulos(venta->articulos);
    free(venta);
}
