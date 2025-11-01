#pragma once
#include "nodoBase.h"
#include <sstream>
#include <string>

template <class T>
class listaBase {
protected:
    nodoBase<T>* primero;
    nodoBase<T>* actual;
    int cantidad;

public:
    listaBase() {
        primero = nullptr;
        actual = nullptr;
        cantidad = 0;
    }

    virtual ~listaBase() {
        while (!estaVacia()) {
            eliminarInicio();
        }
        cantidad = 0;
    }

    bool agregarInicio(T* elemento) {
        nodoBase<T>* nuevo = new nodoBase<T>(elemento);
        if (nuevo == nullptr) {
            return false;
        }
        nuevo->setSiguiente(primero);
        primero = nuevo;
        cantidad++;
        return true;
    }

    bool agregarFinal(T* elemento) {
        nodoBase<T>* nuevo = new nodoBase<T>(elemento);
        if (nuevo == nullptr) {
            return false;
        }
        if (estaVacia()) {
            primero = nuevo;
        }
        else {
            nodoBase<T>* temp = primero;
            while (temp->getSiguiente() != nullptr) {
                temp = temp->getSiguiente();
            }
            temp->setSiguiente(nuevo);
        }
        cantidad++;
        return true;
    }

    bool eliminarInicio() {
        if (estaVacia()) {
            return false;
        }
        nodoBase<T>* temp = primero;
        primero = primero->getSiguiente();
        delete temp->getElemento();
        delete temp;
        cantidad--;
        return true;
    }

    bool eliminarFinal() {
        if (estaVacia()) {
            return false;
        }
        if (primero->getSiguiente() == nullptr) {
            delete primero->getElemento();
            delete primero;
            primero = nullptr;
        }
        else {
            nodoBase<T>* temp = primero;
            while (temp->getSiguiente()->getSiguiente() != nullptr) {
                temp = temp->getSiguiente();
            }
            delete temp->getSiguiente()->getElemento();
            delete temp->getSiguiente();
            temp->setSiguiente(nullptr);
        }
        cantidad--;
        return true;
    }

    // NUEVO: Eliminar un elemento específico sin liberar memoria
    bool eliminarElementoSinBorrar(T* elemento) {
        if (estaVacia() || elemento == nullptr) {
            return false;
        }

        nodoBase<T>* actual = primero;
        nodoBase<T>* anterior = nullptr;

        while (actual != nullptr) {
            if (actual->getElemento() == elemento) {
                if (anterior == nullptr) {
                    // Es el primer nodo
                    primero = actual->getSiguiente();
                }
                else {
                    anterior->setSiguiente(actual->getSiguiente());
                }
                // NO eliminamos el elemento, solo el nodo
                delete actual;
                cantidad--;
                return true;
            }
            anterior = actual;
            actual = actual->getSiguiente();
        }
        return false;
    }

    bool estaVacia() const {
        return primero == nullptr;
    }

    int getCantidad() const {
        return cantidad;
    }

    string toStringLista() {
        stringstream s;
        s << "Imprimiendo lista:\n";
        nodoBase<T>* temp = primero;
        int i = 1;
        while (temp != nullptr) {
            s << i << ". " << temp->getElemento()->toString() << "\n";
            temp = temp->getSiguiente();
            i++;
        }
        return s.str();
    }

    nodoBase<T>* retornarPrimero() {
        return primero;
    }

    nodoBase<T>* retornarUltimo() {
        nodoBase<T>* temp = primero;
        if (estaVacia()) {
            return nullptr;
        }
        while (temp->getSiguiente() != nullptr) {
            temp = temp->getSiguiente();
        }
        return temp;
    }

    // Para iterar manualmente
    void reiniciar() {
        actual = primero;
    }

    T* siguiente() {
        if (actual == nullptr) {
            return nullptr;
        }
        T* elemento = actual->getElemento();
        actual = actual->getSiguiente();
        return elemento;
    }
};