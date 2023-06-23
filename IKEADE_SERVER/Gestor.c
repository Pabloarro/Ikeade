#include <stdio.h>
#include "Gestor.h"
#include <time.h>

void guardarArticulos(const ListaArticulos* lista, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo\n");
        return;
    }
    fwrite(&(lista->cantidad), sizeof(int), 1, archivo);

    for (int i = 0; i < lista->cantidad; i++) {
        fwrite(lista->articulos[i], sizeof(Articulo), 1, archivo);
    }

    fclose(archivo);
}

void cargarArticulos(ListaArticulos* lista, const char* nombreArchivo) {
    FILE* archivo = fopen(nombreArchivo, "rb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para lectura.\n");
        return;
    }

    int cantidadArticulos;
    fread(&cantidadArticulos, sizeof(int), 1, archivo);

    for (int i = 0; i < cantidadArticulos; i++) {
        Articulo articulo;
        fread(&articulo, sizeof(Articulo), 1, archivo);
        anyadirArticulo(&(lista->articulos), &(lista->cantidad), &articulo);
    }

    fclose(archivo);
}

void aniadirArticuloFich(Articulo* articulo) {
    FILE* pf = fopen("Articulos.txt", "a");
    if (pf != NULL) {
        imprimirFechaActualFichero(pf);
        fprintf(pf, "Se acaba de añadir un artículo nuevo:  ");
        imprimirArticuloFichero(pf, articulo);
        fprintf(pf, "\n");
        fprintf(pf, "----------------------------------------------------\n");
        fflush(pf);
        fclose(pf);
    }
}

void eliminarArticuloFich(Articulo* articulo) {
    FILE* pf = fopen("Articulos.txt", "a");
    if (pf != NULL) {
        imprimirFechaActualFichero(pf);
        fprintf(pf, "Se acaba de eliminar el artículo: ");
        imprimirArticuloFichero(pf, articulo);
        fprintf(pf, "\n");
        fprintf(pf, "----------------------------------------------------\n");
        fflush(pf);
        fclose(pf);
    }
}

void imprimirArticuloFichero(FILE* pf, Articulo* articulo) {
    fprintf(pf, "ID: %d\n", articulo->id);
    fprintf(pf, "Nombre: %s\n", articulo->nombre);
    fprintf(pf, "Precio: %.2f\n", articulo->precio);
}

void imprimirFechaActualFichero(FILE * pf){
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	 timeinfo = localtime ( &rawtime );
	 fprintf(pf,"%s",asctime (timeinfo));
}

void visualizarVentas(const Gestor* gestor) {
    printf("Ventas realizadas:\n");

    if (gestor->cantidadVentas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }

    for (int i = 0; i < gestor->cantidadVentas; i++) {
        Venta* venta = gestor->ventas[i];

        printf("Venta %d:\n", i + 1);
        printf("Fecha: ");
        imprimirFecha(venta->fecha);
        printf("Cliente: ");
        imprimirCliente(venta->cliente);
        printf("Artículos:\n");
        imprimirListaArticulos(venta->articulos);
        printf("Precio Total: %.2f\n", venta->precioTotal);
        printf("-----------------\n");
    }
}

void visualizarVentasPorCliente(const Gestor* gestor) {
    char nombreCliente[100];
    printf("Ingrese el nombre del cliente: ");
    fgets(nombreCliente, sizeof(nombreCliente), stdin);
    sscanf(nombreCliente, " %[^\n]s", nombreCliente);

    printf("Ventas realizadas por el cliente:\n");

    if (gestor->cantidadVentas == 0) {
        printf("No hay ventas registradas.\n");
        return;
    }

    int contadorVentas = 0;
    for (int i = 0; i < gestor->cantidadVentas; i++) {
        Venta* venta = gestor->ventas[i];

        if (strcmp(venta->cliente->nombre, nombreCliente) == 0) {
            contadorVentas++;
            printf("Venta %d:\n", contadorVentas);
            printf("Fecha: ");
            imprimirFecha(venta->fecha);
            printf("Cliente: ");
            imprimirCliente(venta->cliente);
            printf("Artículos:\n");
            imprimirListaArticulos(venta->articulos);
            printf("Precio Total: %.2f\n", venta->precioTotal);
            printf("-----------------\n");
        }
    }

    if (contadorVentas == 0) {
        printf("No se encontraron ventas para este cliente.\n");
    }
}
