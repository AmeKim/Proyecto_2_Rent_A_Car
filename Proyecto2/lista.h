#pragma once
#include <iostream>
#include "nodo.h"
#include "cliente.h"

using namespace std;

class lista{
private:
    nodo* cabeza;
    int cantidad;

public:
    lista();
    virtual ~lista();

    void vaciar();
    void insertarInicio(cliente* dato);
    void insertarFinal(cliente* dato);
    bool eliminarPorPosicion(int pos);
    cliente* obtener(int pos) const;
    cliente* buscarPorId(string id) const;
    bool eliminarPorId(string id);
    int getCantidad() const;
    bool estaVacia() const;
    nodo* getCabeza() const;
    void mostrar() const;
};