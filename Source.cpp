#include <iostream>
#include <fstream>
#include "Funciones.h"
#include <locale.h>
using namespace std;



int opcion;
char narch[60];
int main() {
	int cv,opcion1, opcion2, opcion3, opcion4;
	ofstream archivo;
	char buscarPorProveedor[30] = "";
	setlocale(LC_ALL, "spanish");

	cout << "'\n------------------------------------------------------------\n";
	cout << "PRIMERA PARTE DE PROYECTO FINAL C++\n";
	cout << "\nMENU. ";

	do {
		cout << "\n\n1. ALTA DE REGISTROS.\n2. BAJA DE REGISTROS.\n3. LOCALIZA REGISTRO.\n4. REPORTES.\n5. ARCHIVOS.\n6. SALIR" << endl;
		/*	cout << "\n\nOpcion: ";
			cin >> opcion;
			cin.ignore();*/
		opcion = pedirOpcion();
		switch (opcion) {
		case 1:

				cout << "Ingrese el nombre del archivo con los registros: ";
				cin.getline(narch, 60, '\n');
				Lectura(narch);
				break;
			
		case 2:
			cout << "BAJA DE REGISTROS" << "\n";
			cout << "Ingrese la clave de la maquina que dara de baja: ";
			cin >> cv;
			cin.ignore();
			Baja(cv);
			break;
		case 3:
			cout << "\nLocaliza Registro.\n";
			cout << "1. Buscar por clave maquina.\n2. Buscar por Nombre-Proveedor.\n3. Salir.\n";	
			opcion2 = pedirOpcion();
			switch (opcion2) {
			case 1:
				cout << "Ingresa la clave de la maquina: ";
				cin >> cv;
				cout << "\n";
				localizar(cv);
				break;

			case 2:
				cout << "Ingrese el nombre del proveedor: ";
				cin.getline(buscarPorProveedor, 30, '\n');
				cout << "\n";
				localizarPorProveedor(buscarPorProveedor);
				break;

			case 3:
				cout << "Saliendo ......";
				break;
			default: 
				cout << "Verifique su opcion e intentelo de nuevo"; break;
			
			}

			break;
		case 4:
			cout << "\nREPORTES.\n";
			cout << "1. Reporte ordenado por clave maquina.\n2. Reporte ordenado por Nombre-Proveedor.\n3. Salir.\nIngresa la opcion deseada: ";

			opcion3 = pedirOpcion();
			switch (opcion3) {
			case 1:
				OrdenamientoClave();
				imprimirRegistros();
				break;

			case 2:
				OrdenamientoNombre();
				imprimirRegistros();
				break;

			case 3:
				cout << "Saliendo ......";
				break;
			default: cout << "Verifique su opcion e intentelo de nuevo"; break;

			}

			break;
		case 5:
			int noUsu;
			cout << "\nARCHIVOS.\n";
			cout << "1. Crear archivo de entrada al sistema.\n2. Crear archivo con la informacion ordenada por nombre-proveedor.\n3. Crear archivo con la informacion ordenada por clave-proveedor.\nIngresa la opcion deseada: ";

			opcion4 = pedirOpcion();
			switch (opcion4) {
			case 1:
				cout << "Bienvenido, va a registrar usuarios en un TXT para poder usarlos en el sistema.\n¿Cuantos usuarios quiere guardar?. ";
				cin >> noUsu;
				cin.ignore();
				registrarMaquinas(noUsu);
			
				cout << "FALTA DE REALIZAR ESTA PARTE" << endl;
				break;

			case 2:
				OrdenamientoNombre();
				archivoNombreProveedor();
				break;

			case 3:
				OrdenamientoClave();
				archivoClaveProov();
				break;
			default: cout << "Verifique su opcion e intentelo de nuevo"; break;
				// 
			}

			break;
		case 6:
			cout << "\n\nNos vemos pronto." << endl;
			imprimirRegistros();
			exit(0);
			break;
		default:
			cout << "\nEscoja una opcion correcta! ";
		}



	} while (opcion != 6);


	system("pause");
	return 0;
}