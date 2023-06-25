#include "Cliente.h"
#include "DB.h"
Cliente* crearCliente(int dni, const char* nombre, const char* contrasena,const char* telefono) {
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
    cliente->dni = dni;
    cliente->nombre = strdup(nombre);
    cliente->contrasena = strdup(contrasena);
    cliente->telefono = strdup(telefono);

    return cliente;
}





void imprimirCliente(const Cliente* cliente) {
    printf("DNI: %d, Nombre: %s, Teléfono: %s\n", cliente->dni, cliente->telefono, cliente->nombre);
}

void liberarCliente(Cliente* cliente) {
    free(cliente->nombre);
    free(cliente->telefono);
    free(cliente->contrasena);
    free(cliente);
}
int iniSesion(char* nom, char* con) {
  int res;
  res = ComprobarInicioSes(nom, con);
  return res;
}
