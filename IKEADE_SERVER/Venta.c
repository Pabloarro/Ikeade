#include "Venta.h"

Venta* crearVenta(Cliente* cliente, Fecha* fecha) {
    Venta* nuevaVenta = (Venta*)malloc(sizeof(Venta));
    if (nuevaVenta == NULL) {
        return NULL;
    }

    nuevaVenta->cliente = cliente;
    nuevaVenta->articulos = crearListaArticulos();
    nuevaVenta->fecha = fecha;
    nuevaVenta->precioTotal = 0.0;

    return nuevaVenta;
}

void agregarArticulo(Venta* venta, Articulo* articulo) {
    anyadirListaArticulos(venta->articulos, articulo);
}

void calcularPrecioTotal(Venta* venta) {
    venta->precioTotal = 0.0;
    for (int i = 0; i < venta->articulos->cantidad; i++) {
        venta->precioTotal += venta->articulos->articulos[i]->precio;
    }
}

void imprimirVenta(Venta* venta) {
    printf("Venta:\n");
    printf("Cliente: %s\n", venta->cliente->nombre);
    printf("Fecha: %d/%d/%d\n", venta->fecha->dia, venta->fecha->mes, venta->fecha->anio);
    printf("Articulos:\n");
    imprimirListaArticulos(venta->articulos);
    printf("Precio Total: %.2f\n", venta->precioTotal);
}

void liberarVenta(Venta* venta) {
    liberarListaArticulos(venta->articulos);
    liberarCliente(venta->cliente);
    liberarFecha(venta->fecha);
    free(venta);
}
