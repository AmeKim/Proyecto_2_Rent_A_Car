#include "lista.h"
#include "cliente.h"
#include <iostream>

using namespace std;

lista::lista() {
	primero = nullptr;
	actual = nullptr;
}

lista::~lista() {
    vaciar();
}

void lista::vaciar() {
    actual = primero;
    while (actual != nullptr) {
        nodo* siguiente = actual->getSiguiente();
        if (actual->getDato() != nullptr) {
            delete actual->getDato();
        }
        delete actual;
        actual = siguiente;
    }
    primero = nullptr;
    actual = nullptr;
}

void lista::insertarInicio(espacioEstacionamiento* dato) {
    nodo* nuevo = new nodo(dato, primero);
    primero = nuevo;
}

void lista::insertarFinal(espacioEstacionamiento* dato) {
    nodo* nuevo = new nodo(dato, nullptr);

    if (primero == nullptr) {
        primero = nuevo;
    }
    else {
        actual = primero;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
}

espacioEstacionamiento* lista::buscarPorId(string id) const {
    actual= primero;
    while (actual != nullptr) {
        if (actual->getDato()->getCodigo() == id) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool lista::eliminarPorId(string id) {
    actual = primero;
    nodo* anterior = nullptr;
    while (actual != nullptr) {
        if (actual->getDato()->getCodigo() == id) {
            if (anterior == nullptr) {
                primero = actual->getSiguiente();
            }
            else {
                anterior->setSiguiente(actual->getSiguiente());
            }
            delete actual->getDato();
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}

bool lista::estaVacia() const {
    return primero == nullptr;
}

nodo* lista::getActual() const {
    return actual;
}
void lista::mostrar() const {
    actual = primero;
    while (actual != nullptr) {
        cout << actual->getDato()->toString() << endl;
        actual = actual->getSiguiente();
    }
}