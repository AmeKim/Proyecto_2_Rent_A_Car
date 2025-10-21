#pragma once
#include <iostream>
#include <string>

using namespace std;

class matriz {
private:
    void*** Matriz;
    int filas;
    int columnas;

public:
    matriz(int f, int c);
    ~matriz();

    void* getValor(int f, int c);
    void setValor(int f, int c, void* valor);

    int getFilas() const;
    int getColumnas() const;

    void mostrar(string(*mostrarFn)(void*));
};