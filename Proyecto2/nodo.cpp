#include "nodo.h"

nodo::nodo(cliente* d, nodo* sig) {
    dato = d;
    siguiente = sig;
}

nodo::~nodo() {
    siguiente = nullptr;
}

cliente* nodo::getDato() const {
    return dato;
}

nodo* nodo::getSiguiente() const {
    return siguiente;
}

void nodo::setDato(cliente* d) {
    dato = d;
}

void nodo::setSiguiente(nodo* sig) {
    siguiente = sig;
}