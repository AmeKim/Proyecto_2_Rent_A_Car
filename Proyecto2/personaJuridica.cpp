#include "personaJuridica.h"

personaJuridica::personaJuridica() : cliente() {
    actividadEconomica = "";
    porcDescuento = 0.0;
}

personaJuridica::personaJuridica(string cedula, string nombre, string paisResidencia,
    string actividadEconomica, float porcDescuento)
    : cliente(nombre, cedula, paisResidencia) {
    this->actividadEconomica = actividadEconomica;
    this->porcDescuento = porcDescuento;
}

personaJuridica::~personaJuridica() {}

void personaJuridica::setActividadEconomica(string actividad) {
    actividadEconomica = actividad;
}

string personaJuridica::getActividadEconomica() const {
    return actividadEconomica;
}

void personaJuridica::setPorcDescuento(float descuento) {
    porcDescuento = descuento;
}

float personaJuridica::getPorcDescuento() const {
    return porcDescuento;
}

string personaJuridica::toString() const {
    stringstream s;
    s << "===== Cliente Persona Juridica =====\n";
    s << cliente::toString();
    s << "Actividad Economica: " << actividadEconomica << endl;
    s << "Porcentaje de Descuento: " << porcDescuento << "%" << endl;
    return s.str();
}