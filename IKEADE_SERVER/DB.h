#ifndef DB_H_
#define DB_H_

#include "sqlite3.h"
#include "Articulo.h"
#include "Cliente.h"
#include "ListaArticulos.h"

typedef struct {
    sqlite3* db;
} Database;

Database* createDatabase(const char* filename);
void closeDatabase(Database* database);
int insertarCliente(Database* database, const Cliente* cliente);
int insertarArticulo(Database* database, const Articulo* articulo);
int modificarArticuloDB(Database* database, int idArticulo, float nuevoPrecio);
int eliminarArticulo(Database* database, int idArticulo);
int insertarListaArticulos(Database* database, const ListaArticulos* listaArticulos);
int agregarArticuloCarritoDB(Database* database, int idCliente, int idArticulo);
int eliminarArticuloCarritoDB(Database* database, int idCliente, int idArticulo);
ListaArticulos* obtenerArticulosCarrito(Database* database, int idCliente);

#endif
