#include "Articulo.h"

Articulo* crearArticulo(int id, const char* nombre, float precio) {
    Articulo* nuevoArticulo = (Articulo*)malloc(sizeof(Articulo));
    if (nuevoArticulo == NULL) {
        return NULL;
    }

    nuevoArticulo->id = id;
    nuevoArticulo->nombre = nombre;
    nuevoArticulo->precio = precio;

    return nuevoArticulo;
}

void anyadirArticulo(Articulo** listaArticulos, int* cantidadArticulos, Articulo* nuevoArticulo) {
    *listaArticulos = (Articulo*)realloc(*listaArticulos, (*cantidadArticulos + 1) * sizeof(Articulo));
    (*listaArticulos)[*cantidadArticulos] = *nuevoArticulo;
    (*cantidadArticulos)++;
}

void eliminarArticulo(Articulo** listaArticulos, int* cantidadArticulos, int id) {
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
    printf("ID: %d, Nombre: %s, Precio: %.2f\n", articulo->id, articulo->nombre, articulo->precio);
}

void liberarArticulo(Articulo* articulo) {
    free(articulo);
}
