#include "listaEstacionamiento.h"

listaEstacionamiento::listaEstacionamiento() : listaBase<espacioEstacionamiento>() {
	actual = nullptr;
	primero = nullptr;
}
listaEstacionamiento::~listaEstacionamiento() {
}
int listaEstacionamiento::contarEspaciosLibres() {
	int contador = 0;
	actual = primero;
	while (actual != nullptr) {
		if (!actual->getElemento()->estaOcupado()) {
			contador++;
		}
		actual = actual->getSiguiente();
	}
	return contador;
}

string listaEstacionamiento::toStringLista() {
	stringstream s;
	actual = primero;
	while (actual != nullptr) {
		s << actual->getElemento()->toString() << endl;
		actual = actual->getSiguiente();
	}
	return s.str();
}
