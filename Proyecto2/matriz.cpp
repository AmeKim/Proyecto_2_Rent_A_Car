#include "matriz.h"

matriz::matriz(int f, int c) {
    filas = f;
    columnas = c;
    Matriz = new void** [filas];
    for (int i = 0; i < filas; i++) {
        Matriz[i] = new void* [columnas];
        for (int j = 0; j < columnas; j++) {
            Matriz[i][j] = nullptr;
        }
    }
}

matriz::~matriz() {
    for (int i = 0; i < filas; i++) {
        delete[] Matriz[i];
    }
    delete[] Matriz;
}

void* matriz::getValor(int f, int c) { return Matriz[f][c]; }

void matriz::setValor(int f, int c, void* valor) {
    if (f >= 0 && f < filas && c >= 0 && c < columnas)
        Matriz[f][c] = valor;
}

int matriz::getFilas() const { return filas; }
int matriz::getColumnas() const { return columnas; }

void matriz::mostrar(string(*mostrarFn)(void*)) {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (Matriz[i][j] != nullptr)
                cout << mostrarFn(Matriz[i][j]) << "\t";
            else
                cout << "[ ]\t";
        }
        cout << endl;
    }
}
