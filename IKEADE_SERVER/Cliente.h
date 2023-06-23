#ifndef CLIENTE_H_
#define CLIENTE_H_

struct Cliente {
    char nombre[50];
    char contrasena[20];
    int edad;
};

void Cliente_getCliente(struct Cliente* cliente, const char* nombre, const char* contrasena, int edad);
void Cliente_imprimirCliente(const struct Cliente* cliente);

#endif
