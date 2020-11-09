#include "Funciones.h"
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <cstdio>
#include <ctype.h>

using namespace std;

int i;
string correo;
ofstream archivo;
Personas registros[50];


void Lectura(char narch[60]) {
	ifstream archivo;
	int clavemaquina = 0, fail = 0;
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

				if (validarCorreo(ce,1) == 0 ) {
					cout << "Correo equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarCadena(nm) == 0 ) {
					cout << "Nombre de la maquina equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarCadena(np) == 0 ) {
					cout << "Nombre de proveedor equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarTelefono(nc) == 0 ) {
					cout << "Telefono equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (clavemaquina!= 0 && validarRangoClave(clavemaquina) == 0) {
					cout << "Clave no está en el rango requerido [XXXX] en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
				}

				if (validarRangoClave(clavemaquina) && validarCorreo(ce,0) && validarCadena(nm) && validarCadena(np) == 1 && yaExiste == false && clavemaquina != 0 && validarTelefono(nc)==1 ) {
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

int pedirOpcion(int minimo, int maximo, char mensaje[40]) {
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

		if ((op < minimo || op>maximo) && letra == true) {
			std::cout << mensaje;
		}

		if ((op < minimo || op>maximo) && letra == false) {
			std::cout << mensaje;
		}

	} while (letra == true || op < minimo || op>maximo);

	return op;

}

bool validarCadena(char cadena[]) {
	bool valCadena = true;
	for (int i = 0; i < strlen(cadena); i++) {
		if (isdigit(cadena[i]) != 0) valCadena = false;
	}
	return valCadena;
}

bool validarCorreo(char correo[40], bool mensajes) {
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
			if(mensajes==1)
			cout << "Proveedor equivocado. " << endl;
		}
	}

	for (int i = 0; i < strlen(correo); i++) {
		if (isupper(correo[i])) {
			validarMayus = true;
			if (mensajes == 1)
			cout << "Se encontraron mayusculas en el correo. " << endl;
		}
	}

	if (founda != std::string::npos) {
		if (founda > 2 && founda < 15) {
			validarArroba = true;
		}
		else {
			if (mensajes == 1)
			cout << "El correo no cumple la cantidad de caracteres aceptados. Min 2 , Max 20. " << endl;
		}
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
	cout << "Aqui estan los registros encontrados del proveedor " << nombreProovedor<<". \n" << endl;
	for (int x = 0; x < 50; x++) {
		if (strcmp(registros[x].nombreproveedor, nombreProovedor) == 0) {
			cout << "----------------------------------------------------------\n";
			cout << "\tClave de la maquina: " << registros[x].clavemaquina << endl;
			cout << "\tNombre de la maquina: " << registros[x].nombremaquina << "\n";
			cout << "\tNombre de proveedor: " << registros[x].nombreproveedor << "\n";
			cout << "\tNumero de celular: " << registros[x].numerocelular << "\n";
			cout << "\tE-mail: " << registros[x].correoelectronico << "\n";
			cout << "----------------------------------------------------------\n";
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
		if (registros[i].clavemaquina == clave && clave!=0) {
			cout << "----------------------------------------------------------\n";
			cout << "\tClave de la maquina: " << registros[i].clavemaquina << '\n';
			cout << "\tNombre de la maquina: " << registros[i].nombremaquina << '\n';
			cout << "\tNombre proveedor: " << registros[i].nombreproveedor << '\n';
			cout << "\tNumero de celular: " << registros[i].numerocelular << '\n';
			cout << "\tE-Mail: " << registros[i].correoelectronico << '\n';
			cout << "----------------------------------------------------------\n";
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
			cout << "----------------------------------------------------------\n";
			cout <<"\tClave de maquina: "<< registros[i].clavemaquina<<endl;
			cout << "\tNombre de maquina: " << registros[i].nombremaquina<<endl;
			cout << "\tNombre de proveedor: " << registros[i].nombreproveedor<<endl;
			cout << "\tNumero celular: " << registros[i].numerocelular<<endl;
			cout << "\tCorreo electronico: " << registros[i].correoelectronico<<endl;
			cout << "----------------------------------------------------------\n";

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
		for (j = 0; j < 49; j++) {
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
			cout << "----------------------------------------------------------\n";
			std::cout << "\tClave de la maquina: " << registros[i].clavemaquina << '\n';
			std::cout << "\tNombre de la maquina: " << registros[i].nombremaquina << '\n';
			std::cout << "\tNombre proveedor: " << registros[i].nombreproveedor << '\n';
			std::cout << "\tNumero de celular: " << registros[i].numerocelular << '\n';
			std::cout << "\tE-Mail: " << registros[i].correoelectronico << '\n';
			cout << "----------------------------------------------------------\n";
			cout<< endl<<endl;
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
	cin.getline(nombretxt, 40, '\n'); cout << '\n';

	//remove("alan.txt");
	archivo.open(nombretxt, ios::out);

	if (archivo.fail()) {
		cout << "No se puede abrir el archivo. " << endl;
	}

	while (i < noUsu){
		cout << "Ingrese clave de maquina [1xxx]: ";
		cin >> clavemaquina; cin.ignore(); cout << "\n";
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

		if (validarCorreo(ce,1) == 0) {
			cout << "Correo equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl<<endl;
		}

		if (validarCadena(nm) == 0) {
			cout << "Nombre de la maquina equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}

		if (validarCadena(np) == 0) {
			cout << "Nombre de proveedor equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}

		if (validarTelefono(nc) == 0) {
			cout << "Telefono equivocado en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}

		if (clavemaquina != 0 && validarRangoClave(clavemaquina) == 0) {
			cout << "Clave no está en el rango requerido [XXXX] en la maquina con clave [" << clavemaquina << "]. Corriga para poder registrarla. " << endl;
		}
		cout << "\n";
		if (validarCorreo(ce,0) && validarRangoClave(clavemaquina) && validarCadena(nm) && validarCadena(np) == 1 && yaExiste == false && clavemaquina != 0 && validarTelefono(nc)==1) {
			archivo << clavemaquina << " ";
			archivo << nm << " ";
			archivo << np << " ";
			archivo << nc << " ";
			archivo << ce << '\n' << endl;
			cout << "Maquina [" << clavemaquina << "] registrada en posicion [" << i << "]" << endl<<endl;
			registrado = true;
			i++;
		}		

	}
	
	archivo.close();
	cout << "Archivo creado con exito ......";

};

bool validarTelefono(char telefono[11]){
	bool valido = true;

	for (int i = 0; i < strlen(telefono); i++) {
		if (isdigit(telefono[i])) {
		}
		else {
			valido = false;
		}
	}

	if (strlen(telefono) < 10) {
		valido = false;
	}

	return valido;
};

bool validarRangoClave(int clave) {
	bool claveValida = false;
	if (clave > 999 && clave < 10000)
		claveValida = true;

	return claveValida;
}
