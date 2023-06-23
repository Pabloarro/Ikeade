#include "Cliente.h"

Cliente* crearCliente(int dni, const char* nombre, const char* telefono) {
    Cliente* nuevoCliente = (Cliente*)malloc(sizeof(Cliente));
    if (nuevoCliente == NULL) {
        return NULL;
    }

    nuevoCliente->dni = dni;
    nuevoCliente->nombre = strdup(nombre);
    nuevoCliente->telefono = strdup(telefono);

    return nuevoCliente;
}

void pedirCliente(Cliente** cliente) {
    int dni;
    char nombre[100];
    char telefono[20];

    char dniStr[20];
    char nombreStr[100];
    char telefonoStr[20];

    printf("Ingrese el DNI del cliente: ");
    fgets(dniStr, sizeof(dniStr), stdin);
    sscanf(dniStr, "%d", &dni);

    printf("Ingrese el nombre del cliente: ");
    fgets(nombreStr, sizeof(nombreStr), stdin);
    sscanf(nombreStr, " %[^\n]s", nombre);

    printf("Ingrese el teléfono del cliente: ");
    fgets(telefonoStr, sizeof(telefonoStr), stdin);
    sscanf(telefonoStr, " %[^\n]s", telefono);

    *cliente = crearCliente(dni, nombre, telefono);
}

void imprimirCliente(const Cliente* cliente) {
    printf("DNI: %d, Nombre: %s, Teléfono: %s\n", cliente->dni, cliente->nombre, cliente->telefono);
}

void liberarCliente(Cliente* cliente) {
    free(cliente->nombre);
    free(cliente->telefono);
    free(cliente);
}
