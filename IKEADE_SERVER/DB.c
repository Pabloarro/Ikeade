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
    snprintf(sql, sizeof(sql), "INSERT INTO Cliente (dni, nombre, telefono,contrasena) VALUES (%d, '%s', '%s', '%s')",
             cliente->dni, cliente->nombre, cliente->telefono,cliente->contrasena);

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

int modificarArticuloDB(Database* database, int idArticulo, float nuevoPrecio) {
    char sql[256];
    snprintf(sql, sizeof(sql), "UPDATE articulos SET precio = %.2f WHERE id = %d", nuevoPrecio, idArticulo);

    char* errMsg;
    int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error modifying article: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

int eliminarArticulo(Database* database, int idArticulo) {
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM articulos WHERE id = %d", idArticulo);

    char* errMsg;
    int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error deleting article: %s\n", errMsg);
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

int agregarArticuloCarritoDB(Database* database, int idCliente, int idArticulo) {
    char sql[256];
    snprintf(sql, sizeof(sql), "INSERT INTO carrito (id_cliente, id_articulo) VALUES (%d, %d)", idCliente, idArticulo);

    char* errMsg;
    int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error adding article to cart: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

int eliminarArticuloCarritoDB(Database* database, int idCliente, int idArticulo) {
    char sql[256];
    snprintf(sql, sizeof(sql), "DELETE FROM carrito WHERE id_cliente = %d AND id_articulo = %d", idCliente, idArticulo);

    char* errMsg;
    int rc = sqlite3_exec(database->db, sql, NULL, 0, &errMsg);
    if (rc != SQLITE_OK) {
        printf("Error removing article from cart: %s\n", errMsg);
        sqlite3_free(errMsg);
        return 0;
    }
    return 1;
}

ListaArticulos* obtenerArticulosCarrito(Database* database, int idCliente) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT articulos.id, articulos.nombre, articulos.precio FROM articulos JOIN carrito ON articulos.id = carrito.id_articulo WHERE carrito.id_cliente = %d", idCliente);

    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(database->db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        printf("Error retrieving cart items: %s\n", sqlite3_errmsg(database->db));
        return NULL;
    }

    ListaArticulos* listaArticulos = crearListaArticulos();
    while (sqlite3_step(stmt) == SQLITE_ROW) {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* nombre = sqlite3_column_text(stmt, 1);
        float precio = sqlite3_column_double(stmt, 2);
        int stock = sqlite3_column_int(stmt, 3);

        Articulo* articulo = crearArticulo(id, nombre, precio, stock);
        agregarArticulo(listaArticulos, articulo);
    }

    sqlite3_finalize(stmt);
    return listaArticulos;
}
