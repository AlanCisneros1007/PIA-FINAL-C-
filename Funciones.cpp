#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstdio>

using namespace std;

int i;
string correo;
ofstream archivo;
Personas registros[50];


void Lectura(char narch[60]) {
	ifstream archivo;
	int clavemaquina = 0;
	char nm[30] = ""; char np[30] = ""; char nc[11] = ""; char ce[40] = "";
	bool yaExiste = false;
	string correo;
	i = 0;
	archivo.open(narch, ios::in);

	if (archivo.fail()) {
		cout << "El archivo no se pudo abrir o no existe. ";
	}
	else {
		while (!archivo.eof()) {
			
			while (registros[i].clavemaquina != 0) {
				i++;
			};
				
			if (registros[i].clavemaquina == 0 && i < 50) {
				yaExiste = false;
				clavemaquina = 0;
				archivo >> clavemaquina;
				if (clavemaquina != 0) {
					archivo >> nm;
					archivo >> np;
					archivo >> nc;
					archivo >> ce;
				}

				for (int i = 0; i < 50; i++) {
					if (clavemaquina != 0 && registros[i].clavemaquina == clavemaquina) {
						yaExiste = true;
						cout << "El usuario con clave de maquina [" << clavemaquina << "] ya existe, no fue registrado. " << endl;
					}
				}

				if (validarCorreo(ce) == 0) {
					cout << "Correo equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarCadena(nm) == 0) {
					cout << "Nombre de la maquina equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarCadena(np) == 0) {
					cout << "Nombre de proveedor equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarCorreo(ce) && validarCadena(nm) && validarCadena(np) == 1 && yaExiste == false && clavemaquina != 0) {
					registros[i].clavemaquina = clavemaquina;
					strcpy_s(registros[i].nombremaquina, nm);
					strcpy_s(registros[i].nombreproveedor, np);
					strcpy_s(registros[i].numerocelular, nc);
					strcpy_s(registros[i].correoelectronico, ce);
					cout << "Maquina [" << clavemaquina << "] registrada en posicion [" << i << "]" << endl;
					i++;
				}

			}
		}

		if (i > 50) {
			cout << "Se ha excedido el numero maximo de registros, por favor borre o reinicie la aplicacion.\n ";
		}
	}

	archivo.close();
}

int pedirOpcion() {
	int op;
	bool letra = false;
	cout << "Ingresa una opcion: ";
	do {
		letra = false;
		cin >> op;

		if (std::cin.fail())
		{
			std::cin.clear();
			letra = true;
		}
		std::cin.ignore(std::numeric_limits<int>::max(), '\n');

		if ((op < 1 || op>6) && letra == true) {
			std::cout << "ERROR: Introduce la opcion a realizar: ";
		}

		if ((op < 1 || op>6) && letra == false) {
			std::cout << "ERROR: Introduce la opcion a realizar: ";
		}

	} while (letra == true || op < 1 || op>6);

	return op;

}

bool validarCadena(char cadena[]) {
	bool valCadena = true;
	for (int i = 0; i < strlen(cadena); i++) {
		if (isdigit(cadena[i]) != 0) valCadena = false;
	}
	return valCadena;
}

bool validarCorreo(char correo[40]) {
	bool validar = false;
	bool validarCorreo = false;
	bool validarArroba = false;
	bool validarMayus = false;
	bool validarRestoCadena = false;
	string str(correo);
	char proov[40] = "";
	int x = 0;

	size_t founda = str.find("@");
	size_t foundc = str.find(".com");

	if (founda && foundc != std::string::npos) {
		for (int i = founda + 1; i < foundc; i++) {
			proov[x] = correo[i];
			x++;
		}
	}

	if ((foundc != std::string::npos)) {
		if (strcmp(proov, "gmail") == 0 || strcmp(proov, "hotmail") == 0) {
			validarCorreo = true;
		}
		else {
			cout << "Proveedor equivocado. " << endl;
		}
	}

	for (int i = 0; i < strlen(correo); i++) {
		if (isupper(correo[i])) {
			validarMayus = true;
			cout << "SE ENCONTRARON MAYUSCULAS EN EL CORREO. " << endl;
		}
	}

	if (founda != std::string::npos) {
		if (founda > 2 && founda < 15)
			validarArroba = true;
		else
			cout << "El correo no cumple la cantidad de caracteres aceptados. Min 2 , Max 20";
	}

	for (int i = foundc + 4; i < strlen(correo); i++) {
		if (correo[i] != 0) {
			validarRestoCadena = true;
		}

	}

	if (validarArroba && validarCorreo == true && validarMayus == false && validarRestoCadena == false) validar = true;
	return validar;

};

void localizarPorProveedor(char nombreProovedor[30]) {
	bool encontrado = false;
	for (int x = 0; x < 50; x++) {
		if (strcmp(registros[x].nombreproveedor, nombreProovedor) == 0) {
			cout << "Lugar" << x << endl;
			cout << "Clave de la maquina: " << registros[x].clavemaquina << endl;
			cout << "Nombre de la maquina: " << registros[x].nombremaquina << "\n";
			cout << "Nombre de proveedor: " << registros[x].nombreproveedor << "\n";
			cout << "Numero de celular: " << registros[x].numerocelular << "\n";
			cout << "E-mail: " << registros[x].correoelectronico << "\n";
			cout << "\n";
			encontrado = true;
		}
	}

	if (encontrado == false) {
		cout << "No se encontro el nombre del proveedor. Verifique si es correcto.";
	}

}

void localizar(int clave) {
	bool encontrado = false;
	for (int i = 0; i < 50; i++) {
		if (registros[i].clavemaquina == clave) {
			cout << "Clave de la maquina: " << registros[i].clavemaquina << '\n';
			cout << "Nombre de la maquina: " << registros[i].nombremaquina << '\n';
			cout << "Nombre proveedor: " << registros[i].nombreproveedor << '\n';
			cout << "Numero de celular: " << registros[i].numerocelular << '\n';
			cout << "E-Mail: " << registros[i].correoelectronico << '\n';
			encontrado = true;
		}
	}

	if (encontrado == false) {
		cout << "No se pudo localizar la máquina con esta clave. ";
	}
}

void Baja(int clave) {
	char vacio[10] = "";
	bool encontrado = false;

	for (int i = 0; i < 50; i++) {

		if (registros[i].clavemaquina == clave && clave != 0) {
			
			cout << registros[i].clavemaquina<<endl;
			cout << registros[i].nombremaquina<<endl;
			cout << registros[i].nombreproveedor<<endl;
			cout << registros[i].numerocelular<<endl;
			cout << registros[i].correoelectronico<<endl;

			registros[i].clavemaquina = 0;
			strcpy_s(registros[i].nombremaquina, vacio);
			strcpy_s(registros[i].nombreproveedor, vacio);
			strcpy_s(registros[i].numerocelular, vacio);
			strcpy_s(registros[i].correoelectronico, vacio);
			cout << "Registro dado de baja con exito. " << endl;

			encontrado = true;
		}
	}

	if (encontrado == false) {
		cout << "Lo sentimos, el ID ingresado no existe en la base de datos. " << endl;
	}
}

void OrdenamientoClave() {

	int i, j, aux;
	char aux2[30] = "", aux3[30] = "", aux4[11] = "", aux5[40] = "";

	for (i = 0; i < 50; i++) {
		for (j = 0; j < 50; j++) {
			if (registros[j].clavemaquina > registros[j + 1].clavemaquina) {
				aux = registros[j].clavemaquina;
				strcpy_s(aux2, registros[j].nombremaquina);
				strcpy_s(aux3, registros[j].nombreproveedor);
				strcpy_s(aux4, registros[j].numerocelular);
				strcpy_s(aux5, registros[j].correoelectronico);
				registros[j].clavemaquina = registros[j + 1].clavemaquina;
				strcpy_s(registros[j].nombremaquina, registros[j + 1].nombremaquina);
				strcpy_s(registros[j].nombreproveedor, registros[j + 1].nombreproveedor);
				strcpy_s(registros[j].numerocelular, registros[j + 1].numerocelular);
				strcpy_s(registros[j].correoelectronico, registros[j + 1].correoelectronico);
				registros[j + 1].clavemaquina = aux;
				strcpy_s(registros[j + 1].nombremaquina, aux2);
				strcpy_s(registros[j + 1].nombreproveedor, aux3);
				strcpy_s(registros[j + 1].numerocelular, aux4);
				strcpy_s(registros[j + 1].correoelectronico, aux5);
			}
		}

	};
}

void OrdenamientoNombre() {

	int i, j, aux;
	char aux2[30] = "", aux3[30] = "", aux4[11] = "", aux5[40] = "";

	for (i = 0; i < 50; i++) {
		for (j = 0; j < 50; j++) {
			if (strcmp(registros[j].nombreproveedor, registros[j + 1].nombreproveedor) > 0) {
				aux = registros[j].clavemaquina;
				strcpy_s(aux2, registros[j].nombremaquina);
				strcpy_s(aux3, registros[j].nombreproveedor);
				strcpy_s(aux4, registros[j].numerocelular);
				strcpy_s(aux5, registros[j].correoelectronico);
				registros[j].clavemaquina = registros[j + 1].clavemaquina;
				strcpy_s(registros[j].nombremaquina, registros[j + 1].nombremaquina);
				strcpy_s(registros[j].nombreproveedor, registros[j + 1].nombreproveedor);
				strcpy_s(registros[j].numerocelular, registros[j + 1].numerocelular);
				strcpy_s(registros[j].correoelectronico, registros[j + 1].correoelectronico);
				registros[j + 1].clavemaquina = aux;
				strcpy_s(registros[j + 1].nombremaquina, aux2);
				strcpy_s(registros[j + 1].nombreproveedor, aux3);
				strcpy_s(registros[j + 1].numerocelular, aux4);
				strcpy_s(registros[j + 1].correoelectronico, aux5);
			}
		}

	};
}

void imprimirRegistros() {
	for (int i = 0; i < 50; i++) {
		if (registros[i].clavemaquina != 0) {
			cout << "Posicion [" << i << "]" << endl;
			cout << "Clave de la maquina: " << registros[i].clavemaquina << '\n';
			cout << "Nombre de la maquina: " << registros[i].nombremaquina << '\n';
			cout << "Nombre proveedor: " << registros[i].nombreproveedor << '\n';
			cout << "Numero de celular: " << registros[i].numerocelular << '\n';
			cout << "E-Mail: " << registros[i].correoelectronico << '\n' << endl;
		}
	}


};

void archivoClaveProov() {
	archivo.open("clave-proveedor.txt", ios::out);

	if (archivo.fail()) {
		cout << "No se puede abrir el archivo. " << endl;
	}

	for (int i = 0; i < 50; i++) {
		if (registros[i].clavemaquina != 0) {
			archivo << "Clave de la maquina: " << registros[i].clavemaquina << '\n';
			archivo << "Nombre proveedor: " << registros[i].nombreproveedor << '\n';
			archivo << "Nombre de la maquina: " << registros[i].nombremaquina << '\n';
			archivo << "Numero de celular: " << registros[i].numerocelular << '\n';
			archivo << "E-Mail: " << registros[i].correoelectronico << '\n' << endl;
		}
	}

	archivo.close();
	cout << "Archivo ordenado por clave-maquina ha sido creado con exito ......";
}

void archivoNombreProveedor() {
	archivo.open("nombre-proveedor.txt", ios::out);

	if (archivo.fail()) {
		cout << "No se puede abrir el archivo. " << endl;
	}

	for (int i = 0; i < 50; i++) {
		if (registros[i].clavemaquina != 0) {
			archivo << "Nombre proveedor: " << registros[i].nombreproveedor << '\n';
			archivo << "Clave de la maquina: " << registros[i].clavemaquina << '\n';
			archivo << "Nombre de la maquina: " << registros[i].nombremaquina << '\n';
			archivo << "Numero de celular: " << registros[i].numerocelular << '\n';
			archivo << "E-Mail: " << registros[i].correoelectronico << '\n' << endl;
		}
	}

	archivo.close();
	cout << "Archivo ordenado por nombre-proveedor ha sido creado con exito ......";
}

void registrarMaquinas(int noUsu) {
	int clavemaquina = 0, i = 0;
	bool yaExiste = false, registrado = false;
	char nm[30] = ""; char np[30] = ""; char nc[11] = ""; char ce[40] = "",nombretxt[40] = "";
	cout << "Ingrese el nombre del .txt a generar: ";
	cin.getline(nombretxt, 40, '\n');

	//remove("alan.txt");
	archivo.open(nombretxt, ios::out);

	if (archivo.fail()) {
		cout << "No se puede abrir el archivo. " << endl;
	}

	do {
		cout << "Ingrese clave de maquina [1xxx]: ";
		cin >> clavemaquina; cin.ignore();
		cout << "Ingrese nombre de maquina: ";
		cin.getline(nm, 30, '\n');
		cout << "Ingrese nombre del proveedor: ";
		cin.getline(np, 30, '\n');
		cout << "Ingrese el numero de celular [10 digitos]: ";
		cin.getline(nc, 30, '\n');
		cout << "Ingrese el correo electronico: ";
		cin.getline(ce, 30, '\n');

		for (int x = 0; x < 50; x++) {
			if (clavemaquina == registros[x].clavemaquina) yaExiste = true;
		}

		if (validarCorreo(ce) == 0) {
			cout << "Correo equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}

		if (validarCadena(nm) == 0) {
			cout << "Nombre de la maquina equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}

		if (validarCadena(np) == 0) {
			cout << "Nombre de proveedor equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}

		if (validarCorreo(ce) && validarCadena(nm) && validarCadena(np) == 1 && yaExiste == false && clavemaquina != 0) {
			archivo << "Nombre proveedor: " << np << '\n';
			archivo << "Clave de la maquina: " << clavemaquina << '\n';
			archivo << "Nombre de la maquina: " << nm << '\n';
			archivo << "Numero de celular: " << nc << '\n';
			archivo << "E-Mail: " << ce << '\n' << endl;
			cout << "Maquina [" << clavemaquina << "] registrada en posicion [" << i << "]" << endl;
			registrado = true;
			i++;
		}		

	} while (registrado == false && i<noUsu);
	
	archivo.close();
	cout << "Archivo creado con exito ......";

};