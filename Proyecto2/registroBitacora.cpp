#include "registroBitacora.h"

registroBitacora::registroBitacora() : responsable(nullptr) {
    estadoAnterior = "";
    estadoNuevo = "";
    fechaCambio = "";
}

registroBitacora::registroBitacora(const string& anterior, const string& nuevo,
    const string& fecha, colaborador* colab)
    : estadoAnterior(anterior), estadoNuevo(nuevo),
    fechaCambio(fecha), responsable(colab) {
}

string registroBitacora::getEstadoAnterior() const { return estadoAnterior; }
string registroBitacora::getEstadoNuevo() const { return estadoNuevo; }
string registroBitacora::getFechaCambio() const { return fechaCambio; }
colaborador* registroBitacora::getResponsable() const { return responsable; }

string registroBitacora::toString() const {
    stringstream s;
    s << "Estado Anterior: " << estadoAnterior << " -> Nuevo: " << estadoNuevo << endl;
    s << "Fecha: " << fechaCambio << endl;
    s << "Responsable: " << (responsable ? responsable->getNombre() : "N/A") << endl;
    return s.str();
}