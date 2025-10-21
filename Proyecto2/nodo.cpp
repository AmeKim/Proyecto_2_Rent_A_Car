#include "nodo.h"

nodo::nodo(void* d, nodo* sig) {
    dato = d;
    siguiente = sig;
}

nodo::~nodo() {}

void* nodo::getDato() { return dato; }
void nodo::setDato(void* d) { dato = d; }
nodo* nodo::getSiguiente() { return siguiente; }
void nodo::setSiguiente(nodo* s) { siguiente = s; }
