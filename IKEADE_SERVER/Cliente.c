#include "Cliente.h"

Cliente* crearCliente(int dni, const char* nombre, const char* telefono, const char* contrasena) {
    Cliente* cliente = (Cliente*)malloc(sizeof(Cliente));
    cliente->dni = dni;
    cliente->nombre = strdup(nombre);
    cliente->telefono = strdup(telefono);
    cliente->contrasena = strdup(contrasena);
    return cliente;
}

int iniciarSesion(const char* filename) {
    char dni[10];
    char contrasena[50];

    printf("Introduzca su DNI: ");
    scanf("%9s", dni);

    printf("Introduzca su contraseña: ");
    scanf("%49s", contrasena);

    FILE* archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }

    char line[256];
    while (fgets(line, sizeof(line), archivo)) {
        int dni_file;
        char contrasena_file[50];
        sscanf(line, "DNI: %d, Contraseña: %49s", &dni_file, contrasena_file);

        if (strcmp(dni, dni_file) == 0 && strcmp(contrasena, contrasena_file) == 0) {
            fclose(archivo);
            printf("Se ha iniciado sesion\n");
            return 2;
        }
    }

    fclose(archivo);
    printf("Datos incorrectos\n");
    return 1;
}

void registrarCliente(Cliente** clientes, int* numClientes) {
    printf("Ingrese los datos del cliente:\n");

    Cliente cliente;

    printf("DNI: ");
    scanf("%d", &(cliente.dni));

    printf("Nombre: ");
    char nombre[50];
    scanf("%s", nombre);
    cliente.nombre = strdup(nombre);

    printf("Telefono: ");
    char telefono[20];
    scanf("%s", telefono);
    cliente.telefono = strdup(telefono);

    printf("Contraseña: ");
    char contrasena[50];
    scanf("%s", contrasena);
    cliente.contrasena = strdup(contrasena);

    *clientes = (Cliente*)realloc(*clientes, (*numClientes + 1) * sizeof(Cliente));
    (*clientes)[*numClientes] = cliente;
    (*numClientes)++;

    printf("Cliente registrado correctamente.\n");

    FILE* archivo = fopen("clientes.txt", "a");
    if (archivo == NULL) {
        printf("Error al abrir el archivo clientes.txt\n");
        return;
    }

    fprintf(archivo, "DNI: %d, Nombre: %s, Telefono: %s, Contrasena: %s\n", cliente.dni, cliente.nombre, cliente.telefono, cliente.contrasena);

    fclose(archivo);
}

void pedirCliente(Cliente** cliente) {
    int dni;
    char nombre[100];
    char contrasena[50];
    char telefono[20];


    char dniStr[20];
    char nombreStr[100];
    char contrasenaStr[50];
    char telefonoStr[20];

    printf("Ingrese el DNI del cliente: ");
    fgets(dniStr, sizeof(dniStr), stdin);
    sscanf(dniStr, "%d", &dni);

    printf("Ingrese el nombre del cliente: ");
    fgets(nombreStr, sizeof(nombreStr), stdin);
    sscanf(nombreStr, " %[^\n]s", nombre);

    printf("Ingrese la contraseña del cliente: ");
	fgets(contrasena, sizeof(contrasena), stdin);
	sscanf(contrasenaStr, " %[^\n]s", contrasena);

    printf("Ingrese el teléfono del cliente: ");
    fgets(telefonoStr, sizeof(telefonoStr), stdin);
    sscanf(telefonoStr, " %[^\n]s", telefono);


    *cliente = crearCliente(dni, nombre, contrasena, telefono);
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
