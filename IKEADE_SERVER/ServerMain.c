#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <winsock2.h>
#include "Cliente.h"
#include "Articulo.h"
#include "DB.h"
#include "Gestor.h"
#include "ListaArticulos.h"
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
    Database* database= createDatabase("db.db");
    ListaArticulos* listaArt= crearListaArticulos();
    Gestor* gestor= crearGestor();
    crearTablaCliente(database);
    crearTablaArticulo(database);
    iniciarLogger();
    loggear("Conexion realizada entre servidor y cliente\n");
    do {
        char opcion,opcionC, opcionA;
        char nom[20], con[20],dni[20],tlf[20],art[20];
        int resul,id,stock,precio,nuevoPrecio, encontrado;

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
                	  insertarCliente(database, c);



                	  break;
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
                        do{

                        	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        	sscanf(recvBuff, "%d", &opcionA);
                        switch(opcionA){
                        	case '1':
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sprintf(id, "%d", recvBuff);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sprintf(art, "%s", recvBuff);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sprintf(precio, "%d", recvBuff);
								recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
								sprintf(stock, "%d", recvBuff);

								 Articulo* a =crearArticulo(id, art, precio, stock);
								 insertarArticulo(database, a);

								 break;
                        	case '2':
                        		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        		sprintf(id, "%s", recvBuff);

                        		eliminarListaArticulos(listaArt, id);

                        		imprimirListaArticulos(listaArt);
                        		break;

                        	case '3':
                        		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        	    sprintf(id, "%d", recvBuff);

                        	    Articulo* articulo = buscarArticuloPorId(listaArt, id);

                        	    if (articulo == NULL) {
                        	    	encontrado=0;
                        	    	 sprintf(sendBuff, "%d", encontrado);
                        	    	 send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                        	        printf("No se encontró el artículo con ID: %d\n", id);
                        	    } else {
                        	    	encontrado=1;
                        	    	sprintf(sendBuff, "%d", encontrado);
                        	    	send(comm_socket, sendBuff, sizeof(sendBuff), 0);


                        	    	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        	    	sprintf(nuevoPrecio, "%d", recvBuff);

                        	        // Modificar el artículo

                        	        modificarArticulo(articulo, nuevoPrecio);
                        	        modificarArticuloDB(database, id,nuevoPrecio);
                        	        printf("Artículo modificado:\n");
                        	        printf("ID: %d, Nombre: %s, Precio: %.2f\n", articulo->id, articulo->nombre, articulo->precio);
                        	    }

                        		break;

                        	case'4':
                        		visualizarVentas(gestor);
                        		break;
                        	case '5':
                        		recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        		sprintf(nom, "%s", recvBuff);
                        		visualizarVentasPorCliente(gestor);

                        		break;


                        	case '0': break;

                        	}
                        }while(opcionA!='0');

                    } else if (iniSesion(nom, con) == 0) {

                        resul = 2;
                        sprintf(sendBuff, "%d", resul);
                        send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                        loggear("Inicio Sesion cliente Exitoso\n");
                        do{
                        	recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                        	sscanf(recvBuff, "%d", &opcionC);
                            switch (opcionC) {
                                case '1':
                                    // COMPRAR ARTICULOS
                                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                    sprintf(art, "%s", recvBuff);
                                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                    int cantidad;
                                    sscanf(recvBuff, "%d", &cantidad);
                                    int resultado = procesarCompra(database, art, cantidad);

                                    sprintf(sendBuff, "%d", resultado);
                                    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                    break;
                                case '2':
                                    // DEVOLVER ARTICULO
                                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                    sprintf(art, "%s", recvBuff);
                                    recv(comm_socket, recvBuff, sizeof(recvBuff), 0);
                                    int cantidad_devolver;
                                    sscanf(recvBuff, "%d", &cantidad_devolver);
                                    int resultado_devolucion = procesarDevolucion(database, art, cantidad_devolver);

                                    sprintf(sendBuff, "%d", resultado_devolucion);
                                    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                    break;
                                case '3':
                                    // VER COMPRAS
                                    sprintf(sendBuff, "VER_COMPRAS");
                                    send(comm_socket, sendBuff, sizeof(sendBuff), 0);
                                    ListaArticulos* listaCompras = obtenerListaCompras(database);
                                    char listaComprasStr[512];
                                    convertirListaArticuloAString(listaCompras, listaComprasStr);
                                    send(comm_socket, listaComprasStr, sizeof(listaComprasStr), 0);
                                    break;
                                case '0':
                                    break;
                                default:
                                    printf("La opcion no es correcta\n");
                                    break;

                        }

                        }while(opcionC!='0');
                    } else {
                        resul = 0;
                        loggear("Inicio Sesion Fallido\n");
                    }




                    break;
                case '0':
                    fin = 1;
                    printf("FIN DE LA CONEXIÓN");
                    break;
            }
        } while (opcion != '0');

    } while (fin == 0);
    loggear("Programa Finalizado\n\n");
    printf("Programa Finalizado\n");
    closesocket(comm_socket);
    WSACleanup();

    return 0;
}
