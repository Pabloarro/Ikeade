#include "Venta.h"

Venta* crearVenta(Cliente* cliente) {
    Venta* nuevaVenta = (Venta*)malloc(sizeof(Venta));
    if (nuevaVenta == NULL) {
        return NULL;
    }

    nuevaVenta->cliente = cliente;


    nuevaVenta->precioTotal = 0.0;

    return nuevaVenta;
}

Venta* crearVenta2(char* cliente) {
    Venta* nuevaVenta = (Venta*)malloc(sizeof(Venta));
    if (nuevaVenta == NULL) {
        return NULL;
    }

    nuevaVenta->nombre = strdup(cliente);


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

    printf("Articulos:\n");

    printf("Precio Total: %.2f\n", venta->precioTotal);
}

void liberarVenta(Venta* venta) {

    liberarCliente(venta->cliente);

    free(venta);
}
