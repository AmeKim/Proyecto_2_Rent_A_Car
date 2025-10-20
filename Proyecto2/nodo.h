#pragma once
#include <iostream>
using namespace std;

class nodo {
private:
    void* dato;
    nodo* siguiente;
public:
    nodo(void* d = nullptr, nodo* sig = nullptr);
    virtual ~nodo();
    void* getDato() const;
    nodo* getSiguiente() const;
    void setDato(void* d);
    void setSiguiente(nodo* sig);
};

