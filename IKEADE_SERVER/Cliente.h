#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int dni;
	char* nombre;
	char* telefono;

}Cliente;

Cliente* crearCliente(int dni, const char* nombre, const char* telefono);
void pedirCliente(Cliente** cliente);
void imprimirCliente(const Cliente* cliente);
void liberarCliente(Cliente* cliente);

#endif
