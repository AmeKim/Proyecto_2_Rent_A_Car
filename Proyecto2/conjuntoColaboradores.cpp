#include "conjuntoColaboradores.h"

conjuntoColaboradores:: conjuntoColaboradores() : listaBase<colaborador>() {
	primero = nullptr;
	actual = nullptr;
}

conjuntoColaboradores::~conjuntoColaboradores() {
}
void conjuntoColaboradores::agregarColaborador(colaborador* col) {
	agregarFinal(col);
}

void conjuntoColaboradores::eliminarColaborador(string id) {
	actual = primero;
	nodoBase<colaborador>* prev = nullptr;
	while (actual != nullptr) {
		if (actual->getElemento()->getCedula() == id) {
			if (prev == nullptr) {
				primero = actual->getSiguiente();
			} else {
				prev->setSiguiente(actual->getSiguiente());
			}
			delete actual;
			return;
		}
		prev = actual;
		actual = actual->getSiguiente();
	}
}

colaborador* conjuntoColaboradores::buscarColaborador(string id) {
	actual = primero;
	while (actual != nullptr) {
		if (actual->getElemento()->getCedula() == id) {
			return actual->getElemento();
		}
		actual = actual->getSiguiente();
	}
	return nullptr;
}

string conjuntoColaboradores::toString() {
	stringstream ss;
	actual = primero;
	while (actual != nullptr) {
		ss << actual->getElemento()->toString() << endl;
		actual = actual->getSiguiente();
	}
	return ss.str();
}