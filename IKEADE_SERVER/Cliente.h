#ifndef CLIENTE_H_
#define CLIENTE_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	int dni;
	char* nombre;
	char* contrasena;
	char* telefono;

}Cliente;

Cliente* crearCliente(int dni, const char* nombre, const char* contrasena, const char* telefono);
int iniciarSesion(const char* filename);
void registrarCliente(Cliente** clientes, int* numClientes);
void pedirCliente(Cliente** cliente);
void imprimirCliente(const Cliente* cliente);
void liberarCliente(Cliente* cliente);
int iniSesion(char* nom, char* con);
#endif
