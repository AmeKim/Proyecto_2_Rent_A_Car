#include "nodo.h"

nodo::nodo(void* d, nodo* sig) : dato(d), siguiente(sig) {}

nodo::~nodo() {
    // No eliminamos dato aquí porque no sabemos su tipo real
}

void* nodo::getDato() const {
    return dato;
}

nodo* nodo::getSiguiente() const {
    return siguiente;
}

void nodo::setDato(void* d) {
    dato = d;
}

void nodo::setSiguiente(nodo* sig) {
    siguiente = sig;
}