#include "ListaArticulos.h"

ListaArticulos* crearListaArticulos() {
    ListaArticulos* nuevaLista = (ListaArticulos*)malloc(sizeof(ListaArticulos));
    if (nuevaLista == NULL) {
        return NULL;
    }

    nuevaLista->articulos = NULL;
    nuevaLista->cantidad = 0;

    return nuevaLista;
}

void anyadirListaArticulos(ListaArticulos* lista, Articulo* articulo) {
    lista->articulos = (Articulo**)realloc(lista->articulos, (lista->cantidad + 1) * sizeof(Articulo*));
    lista->articulos[lista->cantidad] = articulo;
    lista->cantidad++;
}

void eliminarListaArticulos(ListaArticulos* lista, int id) {
    int indice = -1;
    for (int i = 0; i < lista->cantidad; i++) {
        if (lista->articulos[i]->id == id) {
            indice = i;
            break;
        }
    }

    if (indice != -1) {
        for (int i = indice; i < (lista->cantidad - 1); i++) {
            lista->articulos[i] = lista->articulos[i + 1];
        }
        lista->cantidad--;
        lista->articulos = (Articulo**)realloc(lista->articulos, lista->cantidad * sizeof(Articulo*));
    }
}

Articulo* obtenerArticuloMasCaro(const ListaArticulos* lista) {
    if (lista->cantidad == 0) {
        return NULL;
    }

    Articulo* masCaro = lista->articulos[0];
    for (int i = 1; i < lista->cantidad; i++) {
        if (lista->articulos[i]->precio > masCaro->precio) {
            masCaro = lista->articulos[i];
        }
    }

    return masCaro;
}

Articulo* obtenerArticuloMasBarato(const ListaArticulos* lista) {
    if (lista->cantidad == 0) {
        return NULL;
    }

    Articulo* masBarato = lista->articulos[0];
    for (int i = 1; i < lista->cantidad; i++) {
        if (lista->articulos[i]->precio < masBarato->precio) {
            masBarato = lista->articulos[i];
        }
    }

    return masBarato;
}

void ordenarArticulosPorPrecio(ListaArticulos* lista) {
    for (int i = 0; i < lista->cantidad - 1; i++) {
        for (int j = 0; j < lista->cantidad - i - 1; j++) {
            if (lista->articulos[j]->precio > lista->articulos[j + 1]->precio) {
                Articulo* temp = lista->articulos[j];
                lista->articulos[j] = lista->articulos[j + 1];
                lista->articulos[j + 1] = temp;
            }
        }
    }
}

void imprimirListaArticulos(const ListaArticulos* lista) {
    printf("Lista de Articulos:\n");
    for (int i = 0; i < lista->cantidad; i++) {
        printf("ID: %d, Nombre: %s, Precio: %.2f\n", lista->articulos[i]->id, lista->articulos[i]->nombre, lista->articulos[i]->precio);
    }
}

char* convertirListaArticuloAString(const ListaArticulos* lista, char* listaComprasStr) {
    int tamanoTotal = 0;
    for (int i = 0; i < lista->cantidad; i++) {
        Articulo* articulo = lista->articulos[i];
        tamanoTotal += snprintf(NULL, 0, "ID: %d, Nombre: %s, Precio: %.2f, Cantidad: %d\n",
                               articulo->id, articulo->nombre, articulo->precio, articulo->stock);
    }

    if (listaComprasStr == NULL) {
        listaComprasStr = (char*)malloc((tamanoTotal + 1) * sizeof(char));
    }

    char* posicionActual = listaComprasStr;

    for (int i = 0; i < lista->cantidad; i++) {
        Articulo* articulo = lista->articulos[i];
        posicionActual += snprintf(posicionActual, tamanoTotal + 1, "ID: %d, Nombre: %s, Precio: %.2f, Cantidad: %d\n",
                                   articulo->id, articulo->nombre, articulo->precio, articulo->stock);
    }

    return listaComprasStr;
}

void liberarListaArticulos(ListaArticulos* lista) {
    for (int i = 0; i < lista->cantidad; i++) {
        liberarArticulo(lista->articulos[i]);
    }
    free(lista->articulos);
    free(lista);
}
