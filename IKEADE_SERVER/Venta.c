#include "Venta.h"
#include "Articulo.h"

Venta* crearVenta(int id, char* cliente, int cantidad ) {
    Venta* nuevaVenta = (Venta*)malloc(sizeof(Venta));
    if (nuevaVenta == NULL) {
        return NULL;
    }


    nuevaVenta->id = id;

    nuevaVenta->cliente = cliente;
    nuevaVenta->cantidad=cantidad;

    return nuevaVenta;
}





