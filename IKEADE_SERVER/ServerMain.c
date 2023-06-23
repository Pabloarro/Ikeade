#include <stdio.h>
#include "DB.H"

int main(){

	Database* database = createDatabase("db.db");

	printf("HOla");

	closeDatabase(database);

	return 0;
}
