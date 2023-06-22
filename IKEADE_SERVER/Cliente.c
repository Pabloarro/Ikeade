/*
 * Cliente.c
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */
#include "cliente.h"
#include <stdio.h>
#include <string.h>

void Cliente_getCliente(struct Cliente* cliente, const char* nombre, const char* contrasena, int edad) {
    strncpy(cliente->nombre, nombre, sizeof(cliente->nombre) - 1);
    strncpy(cliente->contrasena, contrasena, sizeof(cliente->contrasena) - 1);
    cliente->nombre[sizeof(cliente->nombre) - 1] = '\0';
    cliente->contrasena[sizeof(cliente->contrasena) - 1] = '\0';
    cliente->edad = edad;
}

void Cliente_imprimirCliente(const struct Cliente* cliente) {
    printf("Nombre: %s\n", cliente->nombre);
    printf("Contraseña: %s\n", cliente->contrasena);
    printf("Edad: %d\n", cliente->edad);
}


