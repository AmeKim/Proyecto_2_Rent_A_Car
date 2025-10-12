#pragma once
#include <iostream>
#include "EspacioEstacionamiento.h"

using namespace std;

class matriz{
private:
	espacioEstacionamiento*** datos;
	int filas;
	int columnas;
	void liberarMemoria();
public:
    matriz(int f = 0, int c = 0);
    virtual ~matriz();

    bool setElemento(int f, int c, espacioEstacionamiento* elemento);
    espacioEstacionamiento* getElemento(int f, int c) const;
    bool eliminarElemento(int f, int c);

    int getFilas() const;
    int getColumnas() const;

    void vaciar();
    bool estaVacio(int f, int c) const;
    int contarElementos() const;

    espacioEstacionamiento* buscarPorCodigo(string codigo) const;
    bool obtenerPosicionPorCodigo(string codigo, int& fila, int& columna) const;

    int contarVecinos(int f, int c) const;
    int contarDisponibles() const;

    void mostrar() const;
    void mostrarEstados() const;
    void redimensionar(int nuevasFilas, int nuevasColumnas);
};

