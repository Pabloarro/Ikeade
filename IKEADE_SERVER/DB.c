#include "DB.h"
#include <stdio.h>

Database* createDatabase(const char* filename) {
    Database* database = (Database*)malloc(sizeof(Database));
    int rc = sqlite3_open(filename, &(database->db));
    if (rc != SQLITE_OK) {
        printf("Error opening database: %s\n", sqlite3_errmsg(database->db));
        free(database);
        return NULL;
    }
    return database;
}

void closeDatabase(Database* database) {
    if (database != NULL) {
        sqlite3_close(database->db);
        free(database);
    }
}

int insertarCliente(Database* database, const Cliente* cliente) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO clientes (dni, nombre, telefono) VALUES (%d, '%s', '%s')",
             cliente->dni, cliente->nombre, cliente->telefono);

    char* errMsg;
    int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error inserting client: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

int insertarArticulo(Database* database, const Articulo* articulo) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO articulos (id, nombre, precio) VALUES (%d, '%s', %.2f)",
             articulo->id, articulo->nombre, articulo->precio);

    char* errMsg;
    int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error inserting article: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

int insertarListaArticulos(Database* database, const ListaArticulos* listaArticulos) {
    for (int i = 0; i < listaArticulos->cantidad; i++) {
        const Articulo* articulo = listaArticulos->articulos[i];

        char sql[256];
        snprintf(sql, sizeof(sql), "INSERT INTO lista_articulos (id_articulo) VALUES (%d)", articulo->id);

        char* errMsg;
        int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
        if (rc != SQLITE_OK) {
            printf("Error inserting article into list: %s\n", errMsg);
            sqlite3_free(errMsg);
            return 0;
        }
    }
    return 1;
}
