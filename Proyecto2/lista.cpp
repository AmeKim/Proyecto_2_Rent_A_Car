#include "lista.h"
#include "cliente.h"
#include <iostream>

using namespace std;

lista::lista() {
    cabeza = nullptr;
    cantidad = 0;
}

lista::~lista() {
    vaciar();
}

void lista::vaciar() {
    nodo* actual = cabeza;
    while (actual != nullptr) {
        nodo* siguiente = actual->getSiguiente();
        if (actual->getDato() != nullptr) {
            delete actual->getDato();
        }
        delete actual;
        actual = siguiente;
    }
    cabeza = nullptr;
    cantidad = 0;
}

void lista::insertarInicio(cliente* dato) {
    nodo* nuevo = new nodo(dato, cabeza);
    cabeza = nuevo;
    cantidad++;
}

void lista::insertarFinal(cliente* dato) {
    nodo* nuevo = new nodo(dato, nullptr);

    if (cabeza == nullptr) {
        cabeza = nuevo;
    }
    else {
        nodo* actual = cabeza;
        while (actual->getSiguiente() != nullptr) {
            actual = actual->getSiguiente();
        }
        actual->setSiguiente(nuevo);
    }
    cantidad++;
}

bool lista::eliminarPorPosicion(int pos) {
    if (pos < 0 || pos >= cantidad || cabeza == nullptr) {
        return false;
    }

    nodo* eliminar;

    if (pos == 0) {
        eliminar = cabeza;
        cabeza = cabeza->getSiguiente();
    }
    else {
        nodo* anterior = cabeza;
        for (int i = 0; i < pos - 1; i++) {
            anterior = anterior->getSiguiente();
        }
        eliminar = anterior->getSiguiente();
        anterior->setSiguiente(eliminar->getSiguiente());
    }

    if (eliminar->getDato() != nullptr) {
        delete eliminar->getDato();
    }
    delete eliminar;
    cantidad--;
    return true;
}

cliente* lista::obtener(int pos) const {
    if (pos < 0 || pos >= cantidad || cabeza == nullptr) {
        return nullptr;
    }

    nodo* actual = cabeza;
    for (int i = 0; i < pos; i++) {
        actual = actual->getSiguiente();
    }
    return actual->getDato();
}

cliente* lista::buscarPorId(string id) const {
    nodo* actual = cabeza;

    while (actual != nullptr) {
        if (actual->getDato()->getId() == id) {
            return actual->getDato();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool lista::eliminarPorId(string id) {
    if (cabeza == nullptr) {
        return false;
    }

    if (cabeza->getDato()->getId() == id) {
        nodo* eliminar = cabeza;
        cabeza = cabeza->getSiguiente();
        if (eliminar->getDato() != nullptr) {
            delete eliminar->getDato();
        }
        delete eliminar;
        cantidad--;
        return true;
    }

    nodo* anterior = cabeza;
    nodo* actual = cabeza->getSiguiente();

    while (actual != nullptr) {
        if (actual->getDato()->getId() == id) {
            anterior->setSiguiente(actual->getSiguiente());
            if (actual->getDato() != nullptr) {
                delete actual->getDato();
            }
            delete actual;
            cantidad--;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}

int lista::getCantidad() const {
    return cantidad;
}

bool lista::estaVacia() const {
    return cabeza == nullptr;
}

nodo* lista::getCabeza() const {
    return cabeza;
}

void lista::mostrar() const {
    nodo* actual = cabeza;
    int pos = 0;

    while (actual != nullptr) {
        cout << "[" << pos << "] " << actual->getDato()->toString() << endl;
        actual = actual->getSiguiente();
        pos++;
    }
}