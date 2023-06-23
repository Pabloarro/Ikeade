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

