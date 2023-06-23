#include "ListaArticulos.h"
#include <stdio.h>
#include <stdlib.h>

void ListaArticulos_CrearLista(struct ListaArticulos* lista) {
    lista->primero = NULL;
}

void ListaArticulos_ImprimirLista(const struct ListaArticulos* lista) {
    struct Nodo* actual = lista->primero;

    while (actual != NULL) {
        Articulo_imprimirArticulo(&actual->articulo);
        actual = actual->siguiente;
    }
}

void ListaArticulos_AnyadirArticulo(struct ListaArticulos* lista, const struct Articulo* articulo) {
    struct Nodo* nuevoNodo = (struct Nodo*)malloc(sizeof(struct Nodo));
    Articulo_copy(&nuevoNodo->articulo, articulo);
    nuevoNodo->siguiente = NULL;

    if (lista->primero == NULL) {
        lista->primero = nuevoNodo;
    } else {
        struct Nodo* actual = lista->primero;

        while (actual->siguiente != NULL) {
            actual = actual->siguiente;
        }

        actual->siguiente = nuevoNodo;
    }
}

void ListaArticulos_EliminarArticulo(struct ListaArticulos* lista, int id) {
    struct Nodo* actual = lista->primero;
    struct Nodo* anterior = NULL;

    while (actual != NULL) {
        if (Articulo_getID(&actual->articulo) == id) {
            if (anterior == NULL) {
                lista->primero = actual->siguiente;
            } else {
                anterior->siguiente = actual->siguiente;
            }

            Articulo_destroy(&actual->articulo);
            free(actual);
            return;
        }

        anterior = actual;
        actual = actual->siguiente;
    }
}

struct Articulo* ListaArticulos_ObtenerArticuloMasCaro(const struct ListaArticulos* lista) {
    struct Nodo* actual = lista->primero;
    struct Articulo* masCaro = &actual->articulo;
    float precioMasCaro = Articulo_getPrecio(masCaro);

    while (actual != NULL) {
        if (Articulo_getPrecio(&actual->articulo) > precioMasCaro) {
            masCaro = &actual->articulo;
            precioMasCaro = Articulo_getPrecio(masCaro);
        }

        actual = actual->siguiente;
    }

    return masCaro;
}

struct Articulo* ListaArticulos_ObtenerArticuloMasBarato(const struct ListaArticulos* lista) {
    struct Nodo* actual = lista->primero;
    struct Articulo* masBarato = &actual->articulo;
    float precioMasBarato = Articulo_getPrecio(masBarato);

    while (actual != NULL) {
        if (Articulo_getPrecio(&actual->articulo) < precioMasBarato) {
            masBarato = &actual->articulo;
            precioMasBarato = Articulo_getPrecio(masBarato);
        }

        actual = actual->siguiente;
    }

    return masBarato;
}

void ListaArticulos_OrdenarArticulosPorPrecio(struct ListaArticulos* lista) {
    int intercambioRealizado = 1;

    while (intercambioRealizado) {
        intercambioRealizado = 0;
        struct Nodo* actual = lista->primero;
        struct Nodo* anterior = NULL;

        while (actual != NULL && actual->siguiente != NULL) {
            struct Nodo* siguiente = actual->siguiente;

            if (Articulo_getPrecio(&actual->articulo) > Articulo_getPrecio(&siguiente->articulo)) {
                if (anterior == NULL) {
                    lista->primero = siguiente;
                } else {
                    anterior->siguiente = siguiente;
                }

                actual->siguiente = siguiente->siguiente;
                siguiente->siguiente = actual;

                anterior = siguiente;
                siguiente = actual->siguiente;
                intercambioRealizado = 1;
            } else {
                anterior = actual;
                actual = siguiente;
            }
        }
    }
}
