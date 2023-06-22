/*
 * DB.c
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */

#include <stdio.h>
#include <string.h>

#include "sqlite3.h"

int crearTablas() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("../db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "DROP TABLE IF EXISTS Usuario;"
                "CREATE TABLE Usuario(Name TEXT, Pass TEXT, Loc INT);"
                "INSERT INTO Usuario VALUES('juan', 'mxdq', 1);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS Loc;"
                "CREATE TABLE Loc(Id INT, Ciudad TEXT, Prov TEXT);"
                "INSERT INTO Loc VALUES(1, 'Bilbao', 'Bizkaia');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS Partida;"
                "CREATE TABLE Partida(TipoBarco TEXT, Jug TEXT);"
                "INSERT INTO Partida VALUES('1', 'juan');";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK ) {

        fprintf(stderr, "SQL error: %s\n", err_msg);

        sqlite3_free(err_msg);
        sqlite3_close(db);

        return 1;
    }

	sql = "DROP TABLE IF EXISTS Barco;"
                "CREATE TABLE Barco(Tipo TEXT);"
                "INSERT INTO Barco VALUES('1');"
                "INSERT INTO Barco VALUES('2');"
                "INSERT INTO Barco VALUES('3');"
                "INSERT INTO Barco VALUES('4');";

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

int insertarData(char* nom, char* pass) {
	sqlite3 *db;
    char *err_msg = 0;

    int rc = sqlite3_open("../db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    char append[100] = "INSERT INTO Usuario VALUES('";
	strcat(append, nom);
	strcat(append, "','");
	strcat(append, pass);
	strcat(append, "', 1);");
    char sql[110];
	strcpy(sql, append);

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

int insertPart(char* tipo, char* nom) {
    sqlite3* db;
    char* err_msg = 0;

    int rc = sqlite3_open("../db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }
    char append[100] = "INSERT INTO Partida VALUES('";
    strcat(append, tipo);
    strcat(append, "','");
    strcat(append, nom);
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

    int rc = sqlite3_open("../db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n",
                sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char *sql = "SELECT * FROM Usuario";

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

int checkPass(char* nom, char* pass) {
    sqlite3* db;
    char* err_msg = 0;
    sqlite3_stmt* res;

    int rc = sqlite3_open("../db.db", &db);

    if (rc != SQLITE_OK) {

        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);

        return 1;
    }

    char sql[100] = "SELECT Name, Pass FROM Usuario WHERE Name = '";
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
