#include "DB.h"
#include <stdio.h>

int crearTablas() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "DROP TABLE IF EXISTS Cliente;"
                "CREATE TABLE Cliente(dni INT, Name TEXT,  Pass TEXT, telefono TEXT);"
                "INSERT INTO Cliente VALUES(123, 'Alex',  '111','235689');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS articulos;"
                "CREATE TABLE articulos(id INT, nombre TEXT, precio INT, stock INT);"
                "INSERT INTO articulos VALUES(01, 'Cama Malm', 250, 10);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS Venta;"
                "CREATE TABLE Venta(id INT, cliente_nombre TEXT,  precio_total REAL);"
                "INSERT INTO Venta VALUES(001, 'Alex', 250.50);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS carrito;"
                "CREATE TABLE carrito(cliente_dni , articulo_id);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}
int llamada(void *NotUsed, int argc, char **argv, char **azColName) {

    NotUsed = 0;

    for (int i = 0; i < argc; i++) {

        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }

    printf("\n");

    return 0;
}
int mostrarData() {
	sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT * FROM articulos";

    rc = sqlite3_exec(db, sql, llamada, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}
int mostrarVentas() {
	sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT * FROM Venta";

    rc = sqlite3_exec(db, sql, llamada, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}
int mostrarVentasPorCliente(char* nombre) {
	sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char sql[110] = "SELECT * FROM Venta WHERE cliente_nombre = '";
    strcat(sql, nombre);
     strcat(sql, "'");
    rc = sqlite3_exec(db, sql, llamada, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}
int eliminarArticulo(int id) {
	sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    char sql[100] = "DELETE FROM articulos WHERE id = '";
        strcat(sql, id);
        strcat(sql, "'");


    rc = sqlite3_exec(db, sql, llamada, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "Failed to select data\n");
        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

    sqlite3_close(db);

    return 0;
}

int insertarCliente(const Cliente* cliente){
	 sqlite3* db;
	    char* err_msg = 0;

	    int rc = sqlite3_open("db.db", &db);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	        sqlite3_close(db);

	        return 1;
	    }

	    char append[100] = "INSERT INTO Cliente VALUES('";
	    strcat(append, cliente->dni);
	    strcat(append, "','");
	    strcat(append, cliente->nombre);
	    strcat(append, "','");
	    strcat(append, cliente->contrasena);
	    strcat(append, "','");
	    strcat(append, cliente->telefono);
	    strcat(append, "');");

	    char sql[110];
	    strcpy(sql, append);

	    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "SQL error: %s\n", err_msg);

	        sqlite3_free(err_msg);
	        sqlite3_close(db);

	        return 1;
	    }

	    sqlite3_close(db);

	    return 0;
	}


int insertarArticulo(const Articulo* articulo){
	 sqlite3* db;
	    char* err_msg = 0;

	    int rc = sqlite3_open("db.db", &db);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	        sqlite3_close(db);

	        return 1;
	    }

	    char append[100] = "INSERT INTO articulos VALUES('";
	    strcat(append, articulo->id);
	    strcat(append, "','");
	    strcat(append, articulo->nombre);
	    strcat(append, "','");
	    int precio=articulo->precio;
	    strcat(append, precio);
	    strcat(append, "','");
	    strcat(append, articulo->stock);
	    strcat(append, "');");

	    char sql[110];
	    strcpy(sql, append);

	    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "SQL error: %s\n", err_msg);

	        sqlite3_free(err_msg);
	        sqlite3_close(db);

	        return 1;
	    }

	    sqlite3_close(db);

	    return 0;
	}

int insertarVenta(const Venta* venta){
	 sqlite3* db;
	    char* err_msg = 0;

	    int rc = sqlite3_open("db.db", &db);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	        sqlite3_close(db);

	        return 1;
	    }

	    char append[100] = "INSERT INTO Venta VALUES('";
	    strcat(append, venta->cliente);
	    strcat(append, "','");
	    strcat(append, (int)venta->precioTotal);
	    strcat(append, "');");


	    char sql[110];
	    strcpy(sql, append);

	    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "SQL error: %s\n", err_msg);

	        sqlite3_free(err_msg);
	        sqlite3_close(db);

	        return 1;
	    }

	    sqlite3_close(db);

	    return 0;
	}




/*

int procesarDevolucion(Database* database, const char* articulo, int cantidad) {
    char query[100];
    int result;
    sprintf(query, "SELECT stock FROM articulos WHERE nombre='%s'", articulo);
    sqlite3_stmt* stmt;
    if (sqlite3_prepare_v2(database->db, query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error al preparar la consulta: %s\n", sqlite3_errmsg(database->db));
        return -1;
    }

    if (sqlite3_step(stmt) != SQLITE_ROW) {
        sqlite3_finalize(stmt);
        return 0;
    }

    int stock = sqlite3_column_int(stmt, 0);
    sqlite3_finalize(stmt);


    if (stock < cantidad) {
        return 0;
    }

    sprintf(query, "UPDATE articulos SET stock = stock - %d WHERE nombre = '%s'", cantidad, articulo);
    if (sqlite3_exec(database->db, query, NULL, NULL, NULL) != SQLITE_OK) {
        fprintf(stderr, "Error al ejecutar la consulta: %s\n", sqlite3_errmsg(database->db));
        return -1;
    }

    return 1;
}

*/
int ComprobarInicioSes(char* nom, char* pass) {
    sqlite3* db;
    char* err_msg = 0;
    sqlite3_stmt* res;

    int rc = sqlite3_open("db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char sql[100] = "SELECT Name, Pass FROM Cliente WHERE Name = '";
    strcat(sql, nom);
    strcat(sql, "'");

    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);

    if (rc == SQLITE_OK) {

        sqlite3_bind_int(res, 1, 3);
    }
    else {

        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
    }

    int step = sqlite3_step(res);

    int comp = 1;

    if (step == SQLITE_ROW) {

        comp = strcmp(nom, sqlite3_column_text(res, 0));
        comp += strcmp(pass, sqlite3_column_text(res, 1));
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    if (comp != 0) {
        return 1;
    }

    return 0;
}
void closeDatabase(Database* database) {
    if (database != NULL) {
        sqlite3_close(database->db);
        free(database);
    }
}
