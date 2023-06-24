#include <stdio.h>
#include <winsock2.h>
#include <iostream>
#define SERVER_IP "127.0.0.1"
#define SERVER_PORT 6000
using namespace std;


char menu(){
	char opcion;
	cout<<"1. Registrarse"<<endl;
	cout<<"2. Iniciar Sesion"<<endl;
	cout<<"0. Salir"<<endl;
	cout<<"Elige una opcion: ";
	cin>>opcion;
	return opcion;
}
char menuAdministrador(){
	char opcion;
	cout<<"MENU ADMINISRADOR"<<endl;
	cout<<"1. Crear articulo "<<endl;
	cout<<"2. Borrar articulo "<<endl;
	cout<<"3. Modificar articulo"<<endl;
	cout<<"4. Visualizar ventas"<<endl;
	cout<<"5. Listar ventas por cliente"<<endl;
	cout<<"0. Salir"<<endl;
	cout<<"Elige una opci�n: ";
	cin>>opcion;
	return opcion;
}
char menuCliente(){
	char opcion;
	cout<<"MENU CLIENTE"<<endl;
	cout<<"1.Comprar Articulos "<<endl;
	cout<<"2.Devolver articulo"<<endl;
	cout<<"3.Ver compras"<<endl;
	cout<<"0. Salir"<<endl;
	cout<<"Elige una opci�n: ";
	cin>>opcion;
	return opcion;
}

int main(int argc, char *argv[]) {

	WSADATA wsaData;
	SOCKET s;
	struct sockaddr_in server;
	char sendBuff[512], recvBuff[512];

	/*
	 * En sendBuff guardaremos lo que el cliente le env�a al servidor
	 * En recvBuff guardaremos lo que el servidor le env�a al cliente
	 * */
	printf("\nInitialising Winsock...\n");
	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("Failed. Error Code : %d", WSAGetLastError());
		return -1;
	}

	printf("Initialised.\n");

	//SOCKET creation
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		printf("Could not create socket : %d", WSAGetLastError());
		WSACleanup();
		return -1;
	}

	printf("Socket created.\n");

	server.sin_addr.s_addr = inet_addr(SERVER_IP); //INADDR_ANY;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//CONNECT to remote server
	if (connect(s, (struct sockaddr*) &server, sizeof(server)) == SOCKET_ERROR) {
		printf("Connection error: %d", WSAGetLastError());
		closesocket(s);
		WSACleanup();
		return -1;
	}

	printf("Connection stablished with: %s (%d)\n", inet_ntoa(server.sin_addr),
			ntohs(server.sin_port));

	/*EMPIEZA EL PROGRAMA DEL CLIENTE*/
	char opcion,opcionA,opcionC;
	char nom[20],con[20],dni[20],tlf[20],art[20],cantidad[20];
	int resul,id,precio,stock;

	do{
		opcion = menu();
		sprintf(sendBuff,"%c",opcion);
		send(s, sendBuff, sizeof(sendBuff), 0);



		switch(opcion){
		case '1':
			cout<<"====REGISTARSE===="<<endl;
			cout<<"DNI: ";cin>>dni;
			cout<<"Nombre:";cin>>nom;
			cout<<"Contrasenia:";cin>>con;
			cout<<"Telefono:";cin>>tlf;
			sprintf(sendBuff,"%s",dni);
			send(s, sendBuff, sizeof(sendBuff), 0);
			sprintf(sendBuff,"%s",nom);
			send(s, sendBuff, sizeof(sendBuff), 0);
			sprintf(sendBuff,"%s",con);
			send(s, sendBuff, sizeof(sendBuff), 0); //Env�o la contrase�a al servidor
			sprintf(sendBuff,"%s",tlf);
			send(s, sendBuff, sizeof(sendBuff), 0);

			// Guardar datos del cliente en la base de datos

			break;
		case '2':
			cout<<"NOMBRE: ";cin>>nom;
			cout<<"CONTRASENYA: ";cin>>con;
			sprintf(sendBuff,"%s",nom);
			send(s, sendBuff, sizeof(sendBuff), 0); //Env�o el nombre al servidor
			sprintf(sendBuff,"%s",con);
			send(s, sendBuff, sizeof(sendBuff), 0); //Env�o la contrase�a al servidor

			recv(s, recvBuff, sizeof(recvBuff), 0); //Recibe el resultado del Inicio de Sesi�n
			sscanf(recvBuff,"%d",&resul);
			cout<<"RESULTADO: "<<resul<<endl;
			if(resul==1){
				do{
					opcionA = menuAdministrador();
					switch(opcionA){
						case '1':
							cout<<"Introduce un id: ";cin>>id;
							cout<<"Introduce un nombre: ";cin>>art;
							cout<<"Introduce un precio: ";cin>>precio;
							cout<<"Introduce el stock: ";cin>>stock;
							sprintf(sendBuff,"%d",id);
							send(s, sendBuff, sizeof(sendBuff), 0);
							sprintf(sendBuff,"%s",art);
							send(s, sendBuff, sizeof(sendBuff), 0);
							sprintf(sendBuff,"%d",precio);
							send(s, sendBuff, sizeof(sendBuff), 0);
							sprintf(sendBuff,"%d",stock);
							send(s, sendBuff, sizeof(sendBuff), 0);


							break;
						case '2': break;
						case '0': break;
						default: cout<<"La opcion no es correcta"<<endl;
					}
				}while(opcionA!='0');
			}else if(resul ==2){
				do{
					opcionC = menuCliente();
					switch(opcionC){
						case '1':
						cout<<"Ingrese el nombre o ID del artículo: ";cin>>art;
						cout<<"Ingrese la cantidad: ";cin>>cantidad;
						sprintf(sendBuff, "%s", art);
						send(s, sendBuff, sizeof(sendBuff), 0);
						sprintf(sendBuff, "%d", cantidad);
						send(s, sendBuff, sizeof(sendBuff), 0);

						recv(s, recvBuff, sizeof(recvBuff), 0);
						sscanf(recvBuff, "%d", &resul);

						if (resul == 1) {
							cout<<"Compra realizada con éxito"<<endl;
						} else {
							cout<<"No se pudo realizar la compra"<<endl;
						}

						break;

						case '2':
					    cout<<"Ingrese el nombre o ID del artículo: ";cin>>art;
					    cout<<"Ingrese la cantidad a devolver: ";cin>>cantidad;

					    sprintf(sendBuff, "%s", art);
					    send(s, sendBuff, sizeof(sendBuff), 0);
					    sprintf(sendBuff, "%d", cantidad);
					    send(s, sendBuff, sizeof(sendBuff), 0);

					    recv(s, recvBuff, sizeof(recvBuff), 0);
					    sscanf(recvBuff, "%d", &resul);

					    if (resul == 1) {
					        cout << "Devolución realizada con éxito" << endl;
					    } else {
					        cout << "No se pudo realizar la devolución" << endl;
					    }

					    break;

						case '3':
						    sprintf(sendBuff, "VER_COMPRAS");
						    send(s, sendBuff, sizeof(sendBuff), 0);

						    recv(s, recvBuff, sizeof(recvBuff), 0);
						    cout << "Lista de compras:" << endl;
						    cout << recvBuff << endl;

						break;

						case '0': break;
						default: cout<<"La opcion no es correcta"<<endl;
					}
				}while(opcionC!='0');
			}else{
				cout<<"El Inicio de Sesion no ha sido correcto"<<endl;
			}
			break;
		case '0': cout<<"AGUR"<<endl;break;
		default: cout<<"La opcion seleccionada no es correcta"<<endl;
		}

	}while(opcion!='0');

	/*ACABA EL PROGRAMA DEL CLIENTE*/
	// CLOSING the socket and cleaning Winsock...
	closesocket(s);
	WSACleanup();

	return 0;
}
