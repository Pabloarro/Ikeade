/*
 * DB.h
 *
 *  Created on: 22 jun 2023
 *      Author: pablo
 */

#ifndef BBDD_H_
#define BBDD_H_

#include "sqlite3.h"

int crearTablas();
int insertarData(char* nom, char* pass);
int insertPart(char* tipo, char* nom);
int llamada(void *, int, char **, char **);
int mostrarData();
int checkPass(char* nom, char* pass);

#endif
