#ifndef ARTICULO_H_
#define ARTICULO_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int id;
    char* nombre;
    float precio;
} Articulo;

Articulo* crearArticulo(int id, const char* nombre, float precio);
void anyadirArticulo(Articulo** listaArticulos, int* cantidadArticulos, Articulo* nuevoArticulo);
void eliminarArticulo(Articulo** listaArticulos, int* cantidadArticulos, int id);
void imprimirArticulo(const Articulo* articulo);
void liberarArticulo(Articulo* articulo);

#endif
