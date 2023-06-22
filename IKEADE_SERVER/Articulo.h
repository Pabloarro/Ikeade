/*
 * Articulo.h
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */

#ifndef ARTICULO_H_
#define ARTICULO_H_

struct Articulo {
    int id;
    char* nombre;
    float precio;
};

void Articulo_init(struct Articulo* articulo, const int id, const char* nombre, float precio);
void Articulo_copy(struct Articulo* destino, const struct Articulo* origen);
void Articulo_destroy(struct Articulo* articulo);
char* Articulo_getNombre(struct Articulo* articulo);
void Articulo_setNombre(struct Articulo* articulo, const char* nombre);
int Articulo_getID(const struct Articulo* articulo);
float Articulo_getPrecio(const struct Articulo* articulo);
void Articulo_imprimirArticulo(const struct Articulo* articulo);

#endif /* ARTICULO_H_ */
