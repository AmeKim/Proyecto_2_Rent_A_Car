#include "nodoBase.h"

template <class T>
nodoBase<T>::nodoBase(T* elemento) {
	this-> dato = elemento;
	siguiente = nullptr;
}

template <class T>
nodoBase<T>* nodoBase<T>::getSiguiente() {
	return siguiente;
}

template <class T>
T* nodoBase<T>::getElemento() {
	return dato;
}

template <class T>
void nodoBase<T>::setSiguiente(nodoBase<T>* siguiente) {
	this->siguiente = siguiente;
}
