#pragma once
#include <iostream>
#include "espacioEstacionamiento.h"

using namespace std;

class matriz {
private:
    int filas;
    int columnas;
    void*** Matriz; // matriz de punteros genéricos

public:
    matriz(int f, int c);
    ~matriz();

    void* getValor(int f, int c);
    void setValor(int f, int c, void* valor);
    int getFilas() const;
    int getColumnas() const;
    void mostrar(string(*mostrarFn)(void*)); // imprime usando función externa
};