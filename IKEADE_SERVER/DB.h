#ifndef DB_H_
#define DB_H_

#include "sqlite3.h"
#include "Articulo.h"
#include "Cliente.h"


typedef struct {
    sqlite3* db;
} Database;

int crearTablas();
/*Database* createDatabase(const char* filename);
int crearTablaCliente(Database* database);
int crearTablaArticulo(Database* database)*/
int insertarCliente(const Cliente* cliente);
int insertarArticulo(const Articulo* articulo);
int eliminarArticulo(int id);

int modificarArticuloDB(Database* database, int idArticulo, float nuevoPrecio);

int agregarArticuloCarritoDB(Database* database, int idCliente, int idArticulo);
int eliminarArticuloCarritoDB(Database* database, int idCliente, int idArticulo);
int procesarDevolucion(Database* database, const char* articulo, int cantidad);
void closeDatabase(Database* database);
int ComprobarInicioSes(char* nom, char* pass);
#endif
