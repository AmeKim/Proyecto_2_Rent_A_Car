#include "personaFisica.h"
#include <iostream>

personaFisica::personaFisica() : cliente() {
    tipoLicencia = "";
}

personaFisica::personaFisica(const string& id, const string& nombre,const string& pais, const string& tipoLic): cliente(id, nombre, pais) {
    tipoLicencia = tipoLic;
}

string personaFisica::getTipoLicencia() const {
    return tipoLicencia;
}

void personaFisica::setTipoLicencia(const string& tipo) {
    tipoLicencia = tipo;
}

string personaFisica::toString() const {
    return "Persona F�sica - ID: " + getCedula() +
        " | Nombre: " + getNombre() +
        " | Pa�s: " + getPaisResidencia() +
        " | Licencia: " + tipoLicencia;
}

void personaFisica::mostrarInfo() const {
    cout << "Cliente Persona F�sica" << endl;
    cout << "ID: " << getCedula() << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "Pa�s: " << getPaisResidencia() << endl;
    cout << "Tipo de Licencia: " << tipoLicencia << endl;
    cout << "-------------------------------" << endl;
}
