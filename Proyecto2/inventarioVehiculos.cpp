#include "inventarioVehiculos.h"

inventarioVehiculos::inventarioVehiculos(int f, int c ) {
	filas = f;
	columnas = c;
	datos = nullptr;
	if (filas > 0 && columnas > 0) {
		datos = new vehiculo** [filas];
		for (int i = 0; i < filas; i++) {
			datos[i] = new vehiculo * [columnas];
			for (int j = 0; j < columnas; j++) {
				datos[i][j] = nullptr;
			}
		}
	}
}

inventarioVehiculos::~inventarioVehiculos() {
	liberarMemoria();
}

void inventarioVehiculos::liberarMemoria() {
	if (datos != nullptr) {
		for (int i = 0; i < filas; i++) {
			if (datos[i] != nullptr) {
				for (int j = 0; j < columnas; j++) {
					if (datos[i][j] != nullptr) {
						delete datos[i][j];
						datos[i][j] = nullptr;
					}
				}
				delete[] datos[i];
				datos[i] = nullptr;
			}
		}
		delete[] datos;
		datos = nullptr;
	}
}

bool inventarioVehiculos::setElemento(int f, int c, vehiculo* elemento) {
	if (f < 0 || f >= filas || c < 0 || c >= columnas) {
		return false;
	}
	if (datos[f][c] != nullptr) {
		delete datos[f][c];
	}
	datos[f][c] = elemento;
	return true;
}

vehiculo* inventarioVehiculos::getElemento(int f, int c) const {
	if (f < 0 || f >= filas || c < 0 || c >= columnas) {
		return nullptr;
	}
	return datos[f][c];
}

bool inventarioVehiculos::eliminarElemento(int f, int c) {
	if (f < 0 || f >= filas || c < 0 || c >= columnas) {
		return false;
	}
	if (datos[f][c] != nullptr) {
		delete datos[f][c];
		datos[f][c] = nullptr;
	}
	return true;
}

void inventarioVehiculos::vaciar() {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr) {
				delete datos[i][j];
				datos[i][j] = nullptr;
			}
		}
	}
}

bool inventarioVehiculos::estaVacio(int f, int c) const {
	for(int i = 0; i < filas; i++) {
		for(int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr) {
				return false;
			}
		}
	}
	return true;
}

int inventarioVehiculos::contarElementos() const {
	int contador = 0;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr) {
				contador++;
			}
		}
	}
	return contador;
}

vehiculo* inventarioVehiculos::buscarPorCodigo(string codigo) const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr && datos[i][j]->getPlaca() == codigo) {
				return datos[i][j];
			}
		}
	}
	return nullptr;
}

bool inventarioVehiculos::obtenerPosicionPorCodigo(string codigo, int& fila, int& columna) const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr && datos[i][j]->getPlaca() == codigo) {
				fila = i;
				columna = j;
				return true;
			}
		}
	}
	return false;
}

int inventarioVehiculos::contarVecinos(int f, int c) const {
	if (f < 0 || f >= filas || c < 0 || c >= columnas) {
		return -1;
	}
	int contador = 0;
	for (int i = f - 1; i <= f + 1; i++) {
		for (int j = c - 1; j <= c + 1; j++) {
			if (i == f && j == c) {
				continue;
			}
			if (i >= 0 && i < filas && j >= 0 && j < columnas) {
				if (datos[i][j] != nullptr) {
					contador++;
				}
			}
		}
	}
	return contador;
}

int inventarioVehiculos::contarDisponibles() const {
	int contador = 0;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr && datos[i][j]->getEstado() == "disponible") {
				contador++;
			}
		}
	}
	return contador;
}

void inventarioVehiculos::mostrar() const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr) {
				cout << datos[i][j]->toString() << endl;
			}
			else {
				cout << "[Vacío]" << endl;
			}
		}
	}
}

void inventarioVehiculos::mostrarEstados() const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (datos[i][j] != nullptr) {
				cout << "Vehículo en posición (" << i << ", " << j << "): " << datos[i][j]->getEstado() << endl;
			}
			else {
				cout << "Posición (" << i << ", " << j << "): [Vacío]" << endl;
			}
		}
	}
}

void inventarioVehiculos::redimensionar(int nuevasFilas, int nuevasColumnas) {
	vehiculo*** nuevosDatos = nullptr;
	if (nuevasFilas > 0 && nuevasColumnas > 0) {
		nuevosDatos = new vehiculo** [nuevasFilas];
		for (int i = 0; i < nuevasFilas; i++) {
			nuevosDatos[i] = new vehiculo * [nuevasColumnas];
			for (int j = 0; j < nuevasColumnas; j++) {
				nuevosDatos[i][j] = nullptr;
			}
		}
		int minFilas = (nuevasFilas < filas) ? nuevasFilas : filas;
		int minColumnas = (nuevasColumnas < columnas) ? nuevasColumnas : columnas;
		for (int i = 0; i < minFilas; i++) {
			for (int j = 0; j < minColumnas; j++) {
				nuevosDatos[i][j] = datos[i][j];
			}
		}
	}
	liberarMemoria();
	datos = nuevosDatos;
	filas = nuevasFilas;
	columnas = nuevasColumnas;
}



