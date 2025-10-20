#include "colaborador.h"

colaborador::colaborador(){
	this->nombre = "";
	this->cedula = "";
	this->fechaIngreso = "";
}

colaborador::colaborador(string nombre, string cedula, string fechaIngreso) {
	this->nombre = nombre;
	this->cedula = cedula;
	this->fechaIngreso = fechaIngreso;
}

colaborador::~colaborador() {
}

string colaborador::getNombre() const {
	return nombre;
}

string colaborador::getCedula() const {	return cedula;
}

string colaborador::getFechaIngreso() const {
	return fechaIngreso;
}

void colaborador::setNombre(string nombre) {
	this->nombre = nombre;
}

void colaborador::setCedula(string cedula) {
	this->cedula = cedula;
}

void colaborador::setFechaIngreso(string fechaIngreso) {
	this->fechaIngreso = fechaIngreso;
}

string colaborador::toString(){
	stringstream ss;
	ss << "Nombre: " << nombre << endl;
	ss << "Cedula: " << cedula << endl;
	ss << "Fecha de Ingreso: " << fechaIngreso << endl;
	return ss.str();
}
