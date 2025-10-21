#pragma once
#include <iostream>
#include <string>
#include "nodo.h"
#include "cliente.h"
#include "espacioEstacionamiento.h"

using namespace std;

class lista {
private:
    nodo* primero;
    nodo* actual;
    int cantidad;

public:
    lista();
    ~lista();

    void agregar(void* elemento);
    bool eliminar(void* elemento);
    void* buscar(void* elemento);

    void reiniciar();
    void* siguiente();

    bool estaVacia() const;
    int getCantidad() const;

    string toString(string(*toStringFn)(void*));
};