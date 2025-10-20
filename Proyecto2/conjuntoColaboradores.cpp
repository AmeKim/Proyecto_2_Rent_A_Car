#include "conjuntoColaboradores.h"

conjuntoColaboradores::conjuntoColaboradores(int capacidad){
	this->capacidad = capacidad;
	this->cantidad = 0;
	this->colaboradores = new colaborador*[capacidad];
}

conjuntoColaboradores::~conjuntoColaboradores(){
	for (int i = 0; i < cantidad; i++) {
		delete colaboradores[i];
	}
	delete[] colaboradores;
}

void conjuntoColaboradores::agregarColaborador(const colaborador* colab){
	if (cantidad < capacidad) {
		colaboradores[cantidad] = new colaborador(*colab);
		cantidad++;
	}
}

bool conjuntoColaboradores::eliminarColaborador(const string cedula){
	for(int i = 0; i < cantidad; i++) {
		if (colaboradores[i]->getCedula() == cedula) {
			delete colaboradores[i];
			for (int j = i; j < cantidad - 1; j++) {
				colaboradores[j] = colaboradores[j + 1];
			}
			cantidad--;
			return true;
		}
	}
	return false;
}

colaborador* conjuntoColaboradores::buscarColaborador(const string cedula){
	for(int i = 0; i < cantidad; i++) {
		if (colaboradores[i]->getCedula() == cedula) {
			return colaboradores[i];
		}
	}
}

void conjuntoColaboradores::mostrarColaboradores(){
	for(int i = 0; i < cantidad; i++) {
		cout << colaboradores[i]->toString() << endl;
	}
}
