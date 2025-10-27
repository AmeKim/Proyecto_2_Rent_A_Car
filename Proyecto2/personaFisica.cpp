#include "personaFisica.h"

personaFisica::personaFisica() : cliente() {
    tipoLicencia = "";
}

personaFisica::personaFisica(const string& cedula, const string& nombre,
    const string& pais, const string& tipoLic)
    : cliente(nombre, cedula, pais) {
    tipoLicencia = tipoLic;
}

personaFisica::~personaFisica() {}

string personaFisica::getTipoLicencia() const {
    return tipoLicencia;
}

void personaFisica::setTipoLicencia(const string& tipo) {
    tipoLicencia = tipo;
}

string personaFisica::toString() const {
    stringstream ss;
    ss << "===== Cliente Persona Fisica =====\n";
    ss << cliente::toString();
    ss << "Tipo de Licencia: " << tipoLicencia << endl;
    return ss.str();
}