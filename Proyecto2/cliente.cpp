#include "cliente.h"

cliente::cliente() {
    nombre = "";
    cedula = "";
    paisResidencia = "";
}

cliente::cliente(string nombre, string cedula, string paisResidencia) {
    this->nombre = nombre;
    this->cedula = cedula;
    this->paisResidencia = paisResidencia;
}

cliente::~cliente() {}

string cliente::getNombre() const { return nombre; }
string cliente::getCedula() const { return cedula; }
string cliente::getPaisResidencia() const { return paisResidencia; }

void cliente::setNombre(string nombre) { this->nombre = nombre; }
void cliente::setCedula(string cedula) { this->cedula = cedula; }
void cliente::setPaisResidencia(string paisResidencia) { this->paisResidencia = paisResidencia; }

string cliente::toString() const {
    stringstream ss;
    ss << "Nombre: " << nombre << endl;
    ss << "Cedula: " << cedula << endl;
    ss << "Pais de Residencia: " << paisResidencia << endl;
    return ss.str();
}