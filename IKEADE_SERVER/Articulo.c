#include "Articulo.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void Articulo_init(struct Articulo* articulo, const int id, const char* nombre, float precio) {
    articulo->id = id;
    articulo->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
    strcpy(articulo->nombre, nombre);
    articulo->precio = precio;
}

void Articulo_copy(struct Articulo* destino, const struct Articulo* origen) {
    destino->id = origen->id;
    destino->nombre = (char*)malloc((strlen(origen->nombre) + 1) * sizeof(char));
    strcpy(destino->nombre, origen->nombre);
    destino->precio = origen->precio;
}

void Articulo_destroy(struct Articulo* articulo) {
    free(articulo->nombre);
}

char* Articulo_getNombre(struct Articulo* articulo) {
    return articulo->nombre;
}

void Articulo_setNombre(struct Articulo* articulo, const char* nombre) {
    free(articulo->nombre);
    articulo->nombre = (char*)malloc((strlen(nombre) + 1) * sizeof(char));
    strcpy(articulo->nombre, nombre);
}

int Articulo_getID(const struct Articulo* articulo) {
    return articulo->id;
}

float Articulo_getPrecio(const struct Articulo* articulo) {
    return articulo->precio;
}

void Articulo_imprimirArticulo(const struct Articulo* articulo) {
    printf("Id: %d\n", articulo->id);
    printf("Nombre: %s\n", articulo->nombre);
    printf("Precio: %.2f\n", articulo->precio);
}
