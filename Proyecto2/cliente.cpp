#include "cliente.h"

cliente::cliente() {
    nombre = "";
    cedula = "";
    paisResidencia = "";
}

cliente::cliente(string nom, string ced, string pais) {
    nombre = nom;
    cedula = ced;
    paisResidencia = pais;
}

cliente::~cliente() {}

string cliente::getNombre() const {
    return nombre;
}

string cliente::getCedula() const {
    return cedula;
}

string cliente::getPaisResidencia() const {
    return paisResidencia;
}

void cliente::setNombre(string nom) {
    nombre = nom;
}

void cliente::setCedula(string ced) {
    cedula = ced;
}

void cliente::setPaisResidencia(string pais) {
    paisResidencia = pais;
}

string cliente::toString() const {
    stringstream ss;
    ss << "Nombre: " << nombre << endl;
    ss << "Cédula: " << cedula << endl;
    ss << "País: " << paisResidencia << endl;
    return ss.str();
}