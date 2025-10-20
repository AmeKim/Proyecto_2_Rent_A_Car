#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "vehiculo.h"

using namespace std;

class inventarioVehiculos {
private:
    vehiculo*** datos;
    int filas;
    int columnas;
    void liberarMemoria();
public:
    inventarioVehiculos(int f = 0, int c = 0);
    virtual ~inventarioVehiculos();

    bool setElemento(int f, int c, vehiculo* elemento);
    vehiculo* getElemento(int f, int c) const;
    bool eliminarElemento(int f, int c);

    void vaciar();
    bool estaVacio(int f, int c) const;
    int contarElementos() const;

    vehiculo* buscarPorCodigo(string codigo) const;
    bool obtenerPosicionPorCodigo(string codigo, int& fila, int& columna) const;

    int contarVecinos(int f, int c) const;
    int contarDisponibles() const;

    void mostrar() const;
    void mostrarEstados() const;
    void redimensionar(int nuevasFilas, int nuevasColumnas);
};
