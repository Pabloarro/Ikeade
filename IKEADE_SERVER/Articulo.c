#include "Articulo.h"

Articulo* crearArticulo(int id, const char* nombre, int precio, int stock) {
	Articulo* articulo = (Articulo*)malloc(sizeof(Articulo));
	    articulo->id = id;
	    articulo->nombre = strdup(nombre);
	    articulo->precio = precio;
	    articulo->stock=stock;
	    return articulo;
}

void anyadirArticulo(Articulo** listaArticulos, int* cantidadArticulos, Articulo* nuevoArticulo) {
    *listaArticulos = (Articulo*)realloc(*listaArticulos, (*cantidadArticulos + 1) * sizeof(Articulo));
    (*listaArticulos)[*cantidadArticulos] = *nuevoArticulo;
    (*cantidadArticulos)++;
}


void modificarArticulo(Articulo* articulo, float precio) {

    articulo->precio = precio;
}

void eliminarArticuloPorId(Articulo** listaArticulos, int* cantidadArticulos, int id) {
    int indice = -1;
    for (int i = 0; i < *cantidadArticulos; i++) {
        if ((*listaArticulos)[i].id == id) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        for (int i = indice; i < (*cantidadArticulos - 1); i++) {
            (*listaArticulos)[i] = (*listaArticulos)[i + 1];
        }
        (*cantidadArticulos)--;
        *listaArticulos = (Articulo*)realloc(*listaArticulos, (*cantidadArticulos) * sizeof(Articulo));
    }
}

void imprimirArticulo(const Articulo* articulo) {
	printf("ID: %d, Nombre: %s, Precio: %d, Stock: %d\n", articulo->id, articulo->nombre, articulo->precio, articulo->stock);
}

void liberarArticulo(Articulo* articulo) {
    free(articulo);
}
