#include "inventarioVehiculos.h"

inventarioVehiculos::inventarioVehiculos() {
	primero = nullptr;
	actual = nullptr;
}

inventarioVehiculos::~inventarioVehiculos() {
	while (!estaVacia()) {
		eliminarInicio();
	}
}
void inventarioVehiculos::agregarVehiculo(vehiculo* v) {
	if(v == nullptr) {
		return;
	}
	agregarFinal(v);
}
void inventarioVehiculos::eliminarVehiculo(vehiculo* v) {
	if (estaVacia() || v == nullptr) {
		return;
	}
	if(primero->getElemento() == v) {
		eliminarInicio();
		return;
	}
	nodoBase<vehiculo>* actual = primero;
	while (actual->getSiguiente() != nullptr) {
		if (actual->getSiguiente()->getElemento() == v) {
			nodoBase<vehiculo>* temp = actual->getSiguiente();
			actual->setSiguiente(temp->getSiguiente());
			delete temp->getElemento();
			delete temp;
			return;
		}
		actual = actual->getSiguiente();
	}
}

string inventarioVehiculos::mostrarVehiculos() const {
	nodoBase<vehiculo>* actual = primero;
	stringstream s;
	int i = 1;
	while (actual != nullptr) {
		s << i << ". " << actual->getElemento()->toString() << endl;
		actual = actual->getSiguiente();
		i++;
	}
	if (i == 1) {
		s << "No hay vehiculos registrados.\n";
	}
	return s.str();
}

string inventarioVehiculos::mostrarTotalDeEstados() {
	stringstream s;
	int disponibles = 0;
	int enMantenimiento = 0;
	int alquilados = 0;
	int devueltos = 0;
	int lavados = 0;
	nodoBase<vehiculo>* actual = primero;
	while (actual != nullptr) {
		string estado = actual->getElemento()->getEstado();
		if (estado == "disponible") {
			disponibles++;
		} else if (estado == "en mantenimiento") {
			enMantenimiento++;
		} else if (estado == "alquilado") {
			alquilados++;
		} else if (estado == "devuelto") {
			devueltos++;
		} else if (estado == "lavado") {
			lavados++;
		}
		actual = actual->getSiguiente();
	}
	s << "Total de Vehiculos por Estado:\n";
	s<< "Disponibles: " << disponibles << endl;
	s<< "En Mantenimiento: " << enMantenimiento << endl;
	s<< "Alquilados: " << alquilados << endl;
	s<< "Devueltos: " << devueltos << endl;
	s<< "Lavados: " << lavados << endl;
	return s.str();
}