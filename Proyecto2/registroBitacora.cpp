#include "registroBitacora.h"
#include <iostream>

registroBitacora::registroBitacora() : responsable(nullptr) {}

registroBitacora::registroBitacora(const string& anterior, const string& nuevo,const string& fecha, colaborador* colab): estadoAnterior(anterior), estadoNuevo(nuevo), fechaCambio(fecha), responsable(colab) {
}

string registroBitacora::getEstadoAnterior() const { return estadoAnterior; }
string registroBitacora::getEstadoNuevo() const { return estadoNuevo; }
string registroBitacora::getFechaCambio() const { return fechaCambio; }
colaborador* registroBitacora::getResponsable() const { return responsable; }

void registroBitacora::mostrarRegistro() const {
    cout << "Cambio de " << estadoAnterior << " a " << estadoNuevo
        << " por " << (responsable ? responsable->getNombre() : "N/A")
        << " el " << fechaCambio << "\n";
}