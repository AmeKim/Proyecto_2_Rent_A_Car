#pragma once
#include <iostream>
#include "nodo.h"
#include "cliente.h"
#include "espacioEstacionamiento.h"

using namespace std;

class lista{
private:
    nodo* primero;
    nodo* actual;

public:
    lista();
    virtual ~lista();

    void vaciar();
    void insertarInicio(espacioEstacionamiento* dato);
    void insertarFinal(espacioEstacionamiento* dato);
    espacioEstacionamiento* buscarPorId(string id) const;
    bool eliminarPorId(string id);
    bool estaVacia() const;
    nodo* getActual() const;
    void mostrar() const;
};