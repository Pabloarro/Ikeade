#ifndef DB_H_
#define DB_H_

#include "sqlite3.h"
#include "Articulo.h"
#include "Cliente.h"
#include "Venta.h"


typedef struct {
    sqlite3* db;
} Database;

int crearTablas();
int llamada(void *NotUsed, int argc, char **argv, char **azColName);
int insertarCliente(const Cliente* cliente);
int insertarArticulo(const Articulo* articulo);
int eliminarArticulo(int id);
int insertarVenta(const Venta* venta);


void closeDatabase(Database* database);
int ComprobarInicioSes(char* nom, char* pass);
int mostrarData();
int mostrarVentas();
int mostrarVentasPorCliente(char* nombre);
#endif
