#include "personaFisica.h"

personaFisica::personaFisica() : cliente() {
    tipoLicencia = "";
}

personaFisica::personaFisica(const string& id, const string& nombre,
    const string& pais, const string& tipoLic)
    : cliente(nombre, id, pais) {
    tipoLicencia = tipoLic;
}

string personaFisica::getTipoLicencia() const {
    return tipoLicencia;
}

void personaFisica::setTipoLicencia(const string& tipo) {
    tipoLicencia = tipo;
}

string personaFisica::toString() const {
    stringstream ss;
    ss << cliente::toString();
    ss << "Tipo de Licencia: " << tipoLicencia << endl;
    return ss.str();
}