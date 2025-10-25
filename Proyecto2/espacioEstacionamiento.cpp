#include "espacioEstacionamiento.h"

espacioEstacionamiento::espacioEstacionamiento(){
	codigo = "";
	ocupado = false;
}

espacioEstacionamiento::espacioEstacionamiento(string codigo, bool ocupado){
	this->codigo = codigo;
	this->ocupado = ocupado;
}

espacioEstacionamiento::~espacioEstacionamiento(){
}

string espacioEstacionamiento::getCodigo() const{
    return codigo;
}

void espacioEstacionamiento::setCodigo(string codigo){
    this->codigo = codigo;
}

bool espacioEstacionamiento::estaOcupado() const    {
    return ocupado;
}

void espacioEstacionamiento::ocupar(){
    ocupado = true;
}

void espacioEstacionamiento::desocupar(){
    ocupado = false;
}

string espacioEstacionamiento::toString(){
    stringstream s;
    s << "Codigo: " << codigo << endl;
	s << "Ocupado: " << (ocupado ? "Si" : "No") << endl;
	return s.str();
}

