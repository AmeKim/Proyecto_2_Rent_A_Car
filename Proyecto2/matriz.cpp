#include "matriz.h"

matriz::matriz(int f, int c) {
    filas = f;
    columnas = c;

    // Crear matriz dinámica de punteros void
    Matriz = new void** [filas];
    for (int i = 0; i < filas; i++) {
        Matriz[i] = new void* [columnas];
        for (int j = 0; j < columnas; j++) {
            Matriz[i][j] = nullptr;
        }
    }
}

matriz::~matriz() {
    // Nota: No eliminamos los objetos apuntados, solo la estructura
    // Los objetos deben ser eliminados por quien los creó
    for (int i = 0; i < filas; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;
}

void* matriz::getValor(int f, int c) {
    if (f < 0 || f >= filas || c < 0 || c >= columnas) {
        return nullptr;
    }
    return Matriz[f][c];
}

void matriz::setValor(int f, int c, void* valor) {
    if (f >= 0 && f < filas && c >= 0 && c < columnas) {
        Matriz[f][c] = valor;
    }
}

int matriz::getFilas() const {
    return filas;
}

int matriz::getColumnas() const {
    return columnas;
}

void matriz::mostrar(string(*mostrarFn)(void*)) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (Matriz[i][j] != nullptr && mostrarFn != nullptr) {
                cout << mostrarFn(Matriz[i][j]) << " ";
            }
            else {
                cout << "[NULL] ";
            }
        }
        cout << endl;
    }
}

string matriz::mostrarMatrizTexto(string(*mostrarFn)(void*)) {
    stringstream s;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (Matriz[i][j] != nullptr && mostrarFn != nullptr) {
                s << mostrarFn(Matriz[i][j]) << " ";
            }
            else {
                s << "[---] ";
            }
        }
        s << "\n";
    }
    return s.str();
}