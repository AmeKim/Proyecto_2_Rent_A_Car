#pragma once
#include <iostream>
#include "cliente.h"

using namespace std;

class nodo{
private:
    cliente* dato;
    nodo* siguiente;

public:
    nodo(cliente* d = nullptr, nodo* sig = nullptr);
    virtual ~nodo();

    cliente* getDato() const;
    nodo* getSiguiente() const;
    void setDato(cliente* d);
    void setSiguiente(nodo* sig);
};

