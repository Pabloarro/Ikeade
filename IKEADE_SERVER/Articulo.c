#include "Articulo.h"

Articulo* crearArticulo(int id, const char* nombre, float precio) {
	Articulo* articulo = (Articulo*)malloc(sizeof(Articulo));
	    articulo->id = id;
	    articulo->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
	    strcpy(articulo->nombre, nombre);
	    articulo->precio = precio;
	    return articulo;
}

void anyadirArticulo(Articulo** listaArticulos, int* cantidadArticulos, Articulo* nuevoArticulo) {
    *listaArticulos = (Articulo*)realloc(*listaArticulos, (*cantidadArticulos + 1) * sizeof(Articulo));
    (*listaArticulos)[*cantidadArticulos] = *nuevoArticulo;
    (*cantidadArticulos)++;
}


void modificarArticulo(Articulo* articulo, const char* nombre, float precio) {
    free(articulo->nombre);
    articulo->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
    strcpy(articulo->nombre, nombre);
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
    printf("ID: %d, Nombre: %s, Precio: %.2f\n", articulo->id, articulo->nombre, articulo->precio);
}

void liberarArticulo(Articulo* articulo) {
    free(articulo);
}
