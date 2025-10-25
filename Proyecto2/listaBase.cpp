#include "listaBase.h"

template <class T>
listaBase<T>::listaBase() {
	primero = nullptr;
	cantidad = 0;
}

template <class T>
listaBase<T>::~listaBase() {
	while (!estaVacia()) {
		eliminarInicio();
	}
	cantidad = 0;
}

template <class T>
bool listaBase<T>::agregarInicio(T* elemento) {
	nodoBase<T>* actual = new nodoBase<T>(elemento);
	if (actual == nullptr) {
		return false;
	}
	actual->setSiguiente(primero);
	primero = actual;
	cantidad++;
	return true;
}

template <class T>
bool listaBase<T>::agregarFinal(T* elemento) {
	nodoBase<T>* actual = new nodoBase<T>(elemento);
	if (actual == nullptr) {
		return false;
	}
	if (estaVacia()) {
		primero = actual;
	} else {
		nodoBase<T>* temp = primero;
		while (temp->getSiguiente() != nullptr) {
			temp = temp->getSiguiente();
		}
		temp->setSiguiente(actual);
	}
	cantidad++;
	return true;
}

template <class T>
bool listaBase<T>::eliminarInicio() {
	if (estaVacia()) {
		return false;
	}
	actual = primero;
	primero = primero->getSiguiente();
	delete actual;
	cantidad--;
	return true;
}

template <class T>
bool listaBase<T>::eliminarFinal() {
	if (estaVacia()) {
		return false;
	}
	if (primero->getSiguiente() == nullptr) {
		delete primero;
		primero = nullptr;
	} else {
		nodoBase<T>* temp = primero;
		while (temp->getSiguiente()->getSiguiente() != nullptr) {
			temp = temp->getSiguiente();
		}
		delete temp->getSiguiente();
		temp->setSiguiente(nullptr);
	}
	cantidad--;
	return true;
}

template <class T>
bool listaBase<T>::estaVacia() const {
	return primero == nullptr;
}

template <class T>
string listaBase<T>::toStringLista() {
	stringstream s;
	s << "Imprimiendo listaBase: \n";
	nodoBase<T>* actual = primero;
	int i = 1;
	while(actual != nullptr) {
		s << i << ". " << actual->getElemento()->toString() << "\n";
		actual = actual->getSiguiente();
		i++;
	}
	return s.str();
}

template <class T>
nodoBase<T>* listaBase<T>::retornarPrimero() {
	return primero;
}
template <class T>
nodoBase<T>* listaBase<T>::retornarUltimo() {
	nodoBase<T>* actual = primero;
	if (estaVacia()) {
		return nullptr;
	}
	while (actual->getSiguiente() != nullptr) {
		actual = actual->getSiguiente();
	}
	return actual;
}
