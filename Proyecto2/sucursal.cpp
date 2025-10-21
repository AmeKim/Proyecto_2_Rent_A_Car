#include "sucursal.h"

sucursal::sucursal() {
    idSucursal = 0;
    nombre = "";
    provincia = "";
}

sucursal::sucursal(int id, const string& nom, const string& prov) {
    idSucursal = id;
    nombre = nom;
    provincia = prov;
}

int sucursal::getIdSucursal() const { return idSucursal; }
string sucursal::getNombre() const { return nombre; }
string sucursal::getProvincia() const { return provincia; }

void sucursal::agregarPlantel(plantel* p) { planteles.agregar((void*)p); }
void sucursal::agregarCliente(cliente* c) { clientes.agregar((void*)c); }
void sucursal::agregarColaborador(colaborador* c) { colaboradores.agregar((void*)c); }
void sucursal::agregarVehiculo(vehiculo* v) { vehiculos.agregar((void*)v); }

void sucursal::mostrarResumen() const {
    cout << "Sucursal #" << idSucursal << " - " << nombre << " (" << provincia << ")" << endl;
}

string sucursal::toString() const {
    return "Sucursal #" + to_string(idSucursal) + " - " + nombre + " (" + provincia + ")";
}
