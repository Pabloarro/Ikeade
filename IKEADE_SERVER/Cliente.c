#include "Cliente.h"
#include "DB.h"
Cliente* crearCliente(int dni, const char* nombre, const char* telefono, const char* contrasena) {
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
    cliente->dni = dni;
    cliente->nombre = strdup(nombre);
    cliente->telefono = strdup(telefono);
    cliente->contrasena = strdup(contrasena);
    return cliente;
}





void imprimirCliente(const Cliente* cliente) {
    printf("DNI: %d, Nombre: %s, Teléfono: %s\n", cliente->dni, cliente->nombre, cliente->telefono);
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
