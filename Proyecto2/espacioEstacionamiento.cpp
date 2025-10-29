#include "espacioEstacionamiento.h"

espacioEstacionamiento::espacioEstacionamiento() {
    codigo = "";
    ocupado = false;
    placaVehiculo = "";
}

espacioEstacionamiento::espacioEstacionamiento(string codigo, bool ocupado) {
    this->codigo = codigo;
    this->ocupado = ocupado;
    this->placaVehiculo = "";
}

espacioEstacionamiento::~espacioEstacionamiento() {}

string espacioEstacionamiento::getCodigo() const {
    return codigo;
}

void espacioEstacionamiento::setCodigo(string codigo) {
    this->codigo = codigo;
}

bool espacioEstacionamiento::estaOcupado() const {
    return ocupado;
}

void espacioEstacionamiento::ocupar() {
    ocupado = true;
}

void espacioEstacionamiento::desocupar() {
    ocupado = false;
    placaVehiculo = "";
}

void espacioEstacionamiento::liberarEspacio() {
    ocupado = false;
    placaVehiculo = "";
}

string espacioEstacionamiento::getVehiculo() const {
    return placaVehiculo;
}

string espacioEstacionamiento::getPlacaVehiculo() const {
    return placaVehiculo;
}

void espacioEstacionamiento::setPlacaVehiculo(string placa) {
    this->placaVehiculo = placa;
}

string espacioEstacionamiento::toString() {
    stringstream s;
    s << "Codigo: " << codigo;
    s << " - Estado: " << (ocupado ? "Ocupado" : "Disponible");
    if (ocupado && placaVehiculo != "") {
        s << " - Placa: " << placaVehiculo;
    }
    return s.str();
}