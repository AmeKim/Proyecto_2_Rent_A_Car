#include "plantel.h"

plantel::plantel() {
	nombre = "";
	tipo = ' ';
	capacidadMax = 0;
	espacios = nullptr;
}

plantel::plantel(string nombre, string ubicacion, int capacidad) {
	this->nombre = nombre;
	this->tipo = ' ';
	this->capacidadMax = capacidad;
	this->espacios = nullptr;
}

plantel:: ~plantel() {

}
string plantel::getNombre() const{
	return nombre;
}
void plantel::setNombre(string nombre) {
	this->nombre = nombre;
}

espacioEstacionamiento* plantel::getEspacios() const {
	return espacios;
}

void plantel::setEspacios(espacioEstacionamiento* espacios) {
	this->espacios = espacios;
}

int plantel::getCapacidadMax() const {
	return capacidadMax;
}

void plantel::setCapacidadMax(int capacidad) {
	this->capacidadMax = capacidad;
}