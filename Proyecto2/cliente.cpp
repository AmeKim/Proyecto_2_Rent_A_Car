#include "cliente.h"

cliente::cliente(){
    this->cedula = "";
    this->nombre = "";
    this->paisResidencia = "";
}

cliente::cliente(string nombre, string cedula, string paisResidencia){
	this->cedula = cedula;
	this->nombre = nombre;
	this->paisResidencia = paisResidencia;
}

cliente::~cliente(){
}

string cliente::getNombre() const { return nombre;}

string cliente::getCedula() const {return cedula;}

string cliente::getPaisResidencia() const{ return paisResidencia;}

void cliente::setNombre(string nombre){ nombre = nombre;}

void cliente::setCedula(string cedula) {cedula = cedula;}

void cliente::setPaisResidencia(string paisResidencia) { paisResidencia = paisResidencia; }

string cliente::toString(){
	stringstream s;
	s << "Nombre: " << nombre << endl;
	s << "Cedula: " << cedula << endl;
	s << "Pais de Residencia : " << paisResidencia << endl;
	return s.str();	
   
}
