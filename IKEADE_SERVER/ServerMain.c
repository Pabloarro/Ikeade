#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "Cliente.h"
#include "Articulo.h"
#include "sqlite3.h"
#include "DB.h"
#include "Carrito.h"


#include "log.h"
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000

int main(int argc, char *argv[]) {
    WSADATA wsaData;
    SOCKET conn_socket;
    SOCKET comm_socket;
    struct sockaddr_in server;
    struct sockaddr_in client;
    char sendBuff[512], recvBuff[512];

    Database* database;

    if (FALSE){
    	crearTablas();
    }

    printf("\nInitialising Winsock...\n");
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        printf("Failed. Error Code: %d", WSAGetLastError());
        return -1;
    }

    printf("Initialised.\n");

    if ((conn_socket = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        printf("Could not create socket : %d", WSAGetLastError());
        WSACleanup();
        return -1;
    }

    printf("Socket created.\n");

    server.sin_addr.s_addr = inet_addr(SERVER_IP);
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);

    if (bind(conn_socket, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
        printf("Bind failed with error code: %d", WSAGetLastError());
        closesocket(conn_socket);
        WSACleanup();
        return -1;
    }

    printf("Bind done.\n");

    if (listen(conn_socket, 1) == SOCKET_ERROR) {
        printf("Listen failed with error code: %d", WSAGetLastError());
        closesocket(conn_socket);
        WSACleanup();
        return -1;
    }

    printf("Waiting for incoming connections...\n");
    int stsize = sizeof(struct sockaddr);
    comm_socket = accept(conn_socket, (struct sockaddr*) &client, &stsize);
    if (comm_socket == INVALID_SOCKET) {
        printf("accept failed with error code : %d", WSAGetLastError());
        closesocket(conn_socket);
        WSACleanup();
        return -1;
    }
    printf("Incomming connection from: %s (%d)\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

    closesocket(conn_socket);
    int fin = 0;

    iniciarLogger();
    loggear("Conexion realizada entre servidor y cliente\n");

    char nom[20], con[20],dni[20],tlf[20],art[20];
    int resul,id,stock,cantidad,opcion,opcionC, opcionA,precio;

    do {



            recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
            sscanf(recvBuff, "%d", &opcion);
            switch (opcion) {
                case '1':
                	//REGISTRARSE
                	  loggear("Registrar Usuario\n");
                	  printf("Registrar Usuario\n");

                	  recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                	  sscanf(recvBuff, "%s", dni);
                	  loggear("Dni Usuario recibido: ");
                	  loggear(dni);
                	  loggear("\n");
                	  recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                	  sscanf(recvBuff, "%s", nom);
                	  loggear("Nombre Usuario recibido: ");
                	  loggear(nom);
                	  loggear("\n");
                	  recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                	  sscanf(recvBuff, "%s",con);
                	  loggear("Contraseña recibida: ");
                	  loggear(con);
                	  loggear("\n");
                	  recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                	  sscanf(recvBuff,"%s",tlf );
                	  loggear("Telefono recibido: ");
                	  loggear(tlf);
                	  loggear("\n");
                	  Cliente* c =crearCliente(dni, nom, con, tlf);
                	  insertarCliente(c);

                	 continue;
                case '2':
                	//INICIAR SESION
                	loggear("Iniciar Sesion\n");
                	printf("Inicio Sesion\n");
                	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                	sscanf(recvBuff, "%s", nom);
                	loggear("Nombre Usuario recibido: ");
                	loggear(nom);
                	loggear("\n");
                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                    sscanf(recvBuff, "%s", con);
                    loggear("Contraseña recibida: ");
                    loggear(con);
                    loggear("\n");

                    if (strcmp(nom, "ADMIN") == 0 && strcmp(con, "ADMIN") == 0) {
                        resul = 1;
                        sprintf(sendBuff, "%d", resul);
                        send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                        loggear("Inicio Sesion ADMIN Exitoso\n");


                        	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        	sscanf(recvBuff, "%d", &opcionA);
                        	do{
                        switch(opcionA){

                        	case 1:
                        		printf("case 1");
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%d",&id);
								printf("%d \n", id);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf( recvBuff, "%s",art);
								printf("%s \n", art);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%d", &precio);
								printf("%d \n", precio);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf( recvBuff, "%d", &stock);
								printf("%d \n", stock);

								Articulo* a =crearArticulo(id, art, precio, stock);
								insertarArticulo(a);


								break;
                        	case 2:
                        		mostrarData();
                        		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        		sscanf(recvBuff, "%d",&id);

                        		eliminarArticulo(id);

                        		break;

                        	case 3:
                        		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        		sscanf(recvBuff, "%d",&id);

                        	    eliminarArticulo(id);

                        	    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%d",&id);

								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf( recvBuff, "%s",art);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf(recvBuff, "%d", &precio);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sscanf( recvBuff, "%d", &stock);

								 Articulo* ar=crearArticulo(id, art, precio, stock);

								 insertarArticulo(ar);


                        	case 4:
                        		mostrarVentas();
                        		break;
                        	case 5:
                        		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        		sprintf(nom, "%s", recvBuff);

                        		mostrarVentasPorCliente(nom);

                        		break;


                        	case 0: break;

                        	}
                        	}while(opcionA!=0);

                    } else if (iniSesion(nom, con) == 0) {
                    	do{
                        resul = 2;
                        sprintf(sendBuff, "%d", resul);
                        send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                        loggear("Inicio Sesion cliente Exitoso\n");

                        	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        	sscanf(recvBuff, "%d", &opcionC);
                            switch (opcionC) {
                                case 1:
                                    // COMPRAR ARTICULOS
                                	mostrarData();
                                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                    sscanf(recvBuff, "%d",&id);

                                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                    sscanf(recvBuff, "%d", &cantidad);

                                    Venta* venta= crearVenta(id,nom,cantidad);
                                    insertarVenta(venta);
                                    break;


                                case 2:
                                    // VER COMPRAS

                                	mostrarVentasPorCliente(nom);
                                    break;
                                case 0:
                                    break;
                                default:
                                    printf("La opcion no es correcta\n");
                                    break;

                        }

                    	}while(opcionC!=0);
                    } else {
                        resul = 0;
                        loggear("Inicio Sesion Fallido\n");
                    }

                    continue;
                case '0':
                    fin = 1;
                    printf("FIN DE LA CONEXIÓN");
                    break;

            }


    } while (fin == 0);
    loggear("Programa Finalizado\n\n");
    printf("Programa Finalizado\n");
    closesocket(comm_socket);
    WSACleanup();

    return 0;
}
