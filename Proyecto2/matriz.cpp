#include "matriz.h"
#include "espacioEstacionamiento.h"
#include <iostream>
using namespace std;

matriz::matriz(int f, int c) {
    filas = f;
    columnas = c;
    datos = nullptr;

    if (filas > 0 && columnas > 0) {
        datos = new espacioEstacionamiento * *[filas];
        for (int i = 0; i < filas; i++) {
            datos[i] = new espacioEstacionamiento * [columnas];
            for (int j = 0; j < columnas; j++) {
                datos[i][j] = nullptr;
            }
        }
    }
}

matriz::~matriz() {
    liberarMemoria();
}

void matriz::liberarMemoria() {
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

bool matriz::setElemento(int f, int c, espacioEstacionamiento* elemento) {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) {
        return false;
    }

    if (datos[f][c] != nullptr) {
        delete datos[f][c];
    }

    datos[f][c] = elemento;
    return true;
}

espacioEstacionamiento* matriz::getElemento(int f, int c) const {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) {
        return nullptr;
    }
    return datos[f][c];
}

bool matriz::eliminarElemento(int f, int c) {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) {
        return false;
    }

    if (datos[f][c] != nullptr) {
        delete datos[f][c];
        datos[f][c] = nullptr;
    }
    return true;
}

int matriz::getFilas() const {
    return filas;
}

int matriz::getColumnas() const {
    return columnas;
}

void matriz::vaciar() {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (datos[i][j] != nullptr) {
                delete datos[i][j];
                datos[i][j] = nullptr;
            }
        }
    }
}

bool matriz::estaVacio(int f, int c) const {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) {
        return true;
    }
    return datos[f][c] == nullptr;
}

int matriz::contarElementos() const {
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

espacioEstacionamiento* matriz::buscarPorCodigo(string codigo) const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (datos[i][j] != nullptr && datos[i][j]->getCodigo() == codigo) {
                return datos[i][j];
            }
        }
    }
    return nullptr;
}

bool matriz::obtenerPosicionPorCodigo(string codigo, int& fila, int& columna) const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (datos[i][j] != nullptr && datos[i][j]->getCodigo() == codigo) {
                fila = i;
                columna = j;
                return true;
            }
        }
    }
    return false;
}

int matriz::contarVecinos(int f, int c) const {
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
                if (datos[i][j] != nullptr && datos[i][j]->estaOcupado()) {
                    contador++;
                }
            }
        }
    }
    return contador;
}

int matriz::contarDisponibles() const {
    int contador = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (datos[i][j] != nullptr && !datos[i][j]->estaOcupado()) {
                contador++;
            }
        }
    }
    return contador;
}

void matriz::mostrar() const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (datos[i][j] != nullptr) {
                cout << datos[i][j]->getCodigo() << " ";
            }
            else {
                cout << "--- ";
            }
        }
        cout << endl;
    }
}

void matriz::mostrarEstados() const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (datos[i][j] != nullptr) {
                if (datos[i][j]->estaOcupado()) {
                    cout << "[X] ";
                }
                else {
                    cout << "[ ] ";
                }
            }
            else {
                cout << "--- ";
            }
        }
        cout << endl;
    }
}

void matriz::redimensionar(int nuevasFilas, int nuevasColumnas) {
    liberarMemoria();
    filas = nuevasFilas;
    columnas = nuevasColumnas;

    if (filas > 0 && columnas > 0) {
        datos = new espacioEstacionamiento * *[filas];
        for (int i = 0; i < filas; i++) {
            datos[i] = new espacioEstacionamiento * [columnas];
            for (int j = 0; j < columnas; j++) {
                datos[i][j] = nullptr;
            }
        }
    }
}