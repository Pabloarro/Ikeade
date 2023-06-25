#include "Venta.h"

Venta* crearVenta(Cliente* cliente, Fecha* fecha) {
    Venta* nuevaVenta = (Venta*)malloc(sizeof(Venta));
    if (nuevaVenta == NULL) {
        return NULL;
    }

    nuevaVenta->cliente = cliente;

    nuevaVenta->fecha = fecha;
    nuevaVenta->precioTotal = 0.0;

    return nuevaVenta;
}

void agregarArticulo(Venta* venta, Articulo* articulo) {

}

void calcularPrecioTotal(Venta* venta) {
    venta->precioTotal = 0.0;

}

void imprimirVenta(Venta* venta) {
    printf("Venta:\n");
    printf("Cliente: %s\n", venta->cliente->nombre);
    printf("Fecha: %d/%d/%d\n", venta->fecha->dia, venta->fecha->mes, venta->fecha->anio);
    printf("Articulos:\n");

    printf("Precio Total: %.2f\n", venta->precioTotal);
}

void liberarVenta(Venta* venta) {

    liberarCliente(venta->cliente);
    liberarFecha(venta->fecha);
    free(venta);
}
