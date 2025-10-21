#pragma once
#include <iostream>
using namespace std;

class nodo {
private:
    void* dato;        // Apunta a cualquier tipo de objeto
    nodo* siguiente;   // Puntero al siguiente nodo

public:
    nodo(void* dato, nodo* sig = nullptr);
    ~nodo();

    void* getDato();
    void setDato(void* d);
    nodo* getSiguiente();
    void setSiguiente(nodo* s);
};
