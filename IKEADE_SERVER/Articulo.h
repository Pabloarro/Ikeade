#ifndef ARTICULO_H_
#define ARTICULO_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    int id;
    char* nombre;
    float precio;
    int stock;
} Articulo;

Articulo* crearArticulo(int id, const char* nombre, float precio,int stock);
void anyadirArticulo(Articulo** listaArticulos, int* cantidadArticulos, Articulo* nuevoArticulo);
void modificarArticulo(Articulo* articulo, float precio);
void eliminarArticuloPorId(Articulo** listaArticulos, int* cantidadArticulos, int id);
void imprimirArticulo(const Articulo* articulo);
void liberarArticulo(Articulo* articulo);

#endif
