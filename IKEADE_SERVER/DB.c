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
                "INSERT INTO Cliente VALUES(123, 'Alex',  '111','235689');"
				"INSERT INTO Cliente VALUES(987654, 'Pablo', '123' ,'666666');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS articulos;"
                "CREATE TABLE articulos(id INT, nombre TEXT, precio INT, stock INT);"
            	"INSERT INTO articulos VALUES(1, 'Cama Malm', 250, 10);"
				"INSERT INTO articulos VALUES(2, 'Mesa marron', 120, 13);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS Venta;"
                "CREATE TABLE Venta(id INT, nombre TEXT,  cantidad INT);"
            	"INSERT INTO Venta VALUES(1, 'Alex', 250);"
				"INSERT INTO Venta VALUES(2, 'Pablo', 120);";

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


int eliminarArticulo(int id){
	 sqlite3* db;
	    char* err_msg = 0;

	    int rc = sqlite3_open("db.db", &db);

	    if (rc != SQLITE_OK) {

	        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
	        sqlite3_close(db);

	        return 1;
	    }

	    char append[100];

	    sprintf(append,"DELETE FROM articulos where id= %d",id);

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

	    char append[100];
	    imprimirArticulo(articulo);
	    sprintf(append,"INSERT INTO articulos VALUES(%d,'%s',%d,%d);",articulo->id,articulo->nombre,articulo->precio,articulo->stock);

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

	    char append[100];

	   	    sprintf(append,"INSERT INTO Venta VALUES(%d,'%s',%d);",venta->id,venta->cliente,venta->cantidad);

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
