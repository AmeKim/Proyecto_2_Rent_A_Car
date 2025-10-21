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
    return "Persona Física - ID: " + getCedula() +
        " | Nombre: " + getNombre() +
        " | País: " + getPaisResidencia() +
        " | Licencia: " + tipoLicencia;
}

void personaFisica::mostrarInfo() const {
    cout << "Cliente Persona Física" << endl;
    cout << "ID: " << getCedula() << endl;
    cout << "Nombre: " << getNombre() << endl;
    cout << "País: " << getPaisResidencia() << endl;
    cout << "Tipo de Licencia: " << tipoLicencia << endl;
    cout << "-------------------------------" << endl;
}
