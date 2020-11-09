#pragma once

void Lectura(char narch[60]);
void Baja(int clave);
bool validarCorreo(char correo[40],bool mensajes);
bool validarCadena(char cadena[]);
void localizarPorProveedor(char nombreProovedor[30]);
void localizar(int clave);
void OrdenamientoClave();
void OrdenamientoNombre();
void archivoClaveProov();
void archivoNombreProveedor();
void imprimirRegistros();
void registrarMaquinas(int noUsu);
bool validarTelefono(char telefono[11]);
bool validarRangoClave(int clave);
int pedirOpcion(int minimo, int maximo, char mensaje[40]);

struct Personas {
	unsigned int clavemaquina = 0;
	char nombremaquina[30] = "";
	char nombreproveedor[30] = "";
	char numerocelular[11] = "";
	char correoelectronico[40] = "";
};

