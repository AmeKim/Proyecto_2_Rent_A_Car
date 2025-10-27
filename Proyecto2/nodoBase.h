#pragma once
#pragma once
#include <iostream>
using namespace std;

template <class T>
class nodoBase {
private:
    T* dato;
    nodoBase<T>* siguiente;

public:
    nodoBase(T* elemento) {
        this->dato = elemento;
        siguiente = nullptr;
    }

    nodoBase<T>* getSiguiente() {
        return siguiente;
    }

    T* getElemento() {
        return dato;
    }

    void setSiguiente(nodoBase<T>* siguiente) {
        this->siguiente = siguiente;
    }
};