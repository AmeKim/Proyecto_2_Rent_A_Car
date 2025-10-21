#include "lista.h"

lista::lista() {
    primero = nullptr;
    actual = nullptr;
    cantidad = 0;
}

lista::~lista() {
    nodo* aux;
    while (primero != nullptr) {
        aux = primero;
        primero = primero->getSiguiente();
        delete aux;
    }
}

void lista::agregar(void* elemento) {
    nodo* nuevo = new nodo(elemento);
    if (primero == nullptr) {
        primero = nuevo;
    }
    else {
        nodo* aux = primero;
        while (aux->getSiguiente() != nullptr) {
            aux = aux->getSiguiente();
        }
        aux->setSiguiente(nuevo);
    }
    cantidad++;
}

bool lista::eliminar(void* elemento) {
    if (primero == nullptr) return false;
    nodo* aux = primero;
    nodo* ant = nullptr;

    while (aux != nullptr) {
        if (aux->getDato() == elemento) {
            if (ant == nullptr) {
                primero = aux->getSiguiente();
            }
            else {
                ant->setSiguiente(aux->getSiguiente());
            }
            delete aux;
            cantidad--;
            return true;
        }
        ant = aux;
        aux = aux->getSiguiente();
    }
    return false;
}

void* lista::buscar(void* elemento) {
    nodo* aux = primero;
    while (aux != nullptr) {
        if (aux->getDato() == elemento) return aux->getDato();
        aux = aux->getSiguiente();
    }
    return nullptr;
}

void lista::reiniciar() { actual = primero; }

void* lista::siguiente() {
    if (actual == nullptr) return nullptr;
    void* dato = actual->getDato();
    actual = actual->getSiguiente();
    return dato;
}

bool lista::estaVacia() const { return primero == nullptr; }
int lista::getCantidad() const { return cantidad; }

string lista::toString(string(*toStringFn)(void*)) {
    string texto = "";
    nodo* aux = primero;
    while (aux != nullptr) {
        texto += toStringFn(aux->getDato()) + "\n";
        aux = aux->getSiguiente();
    }
    return texto;
}