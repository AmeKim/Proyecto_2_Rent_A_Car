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

sucursal::~sucursal() {}

int sucursal::getIdSucursal() const {
    return idSucursal;
}

string sucursal::getNombre() const {
    return nombre;
}

string sucursal::getProvincia() const {
    return provincia;
}

void sucursal::agregarPlantel(plantel* p) {
    planteles.agregar((void*)p);
}

void sucursal::agregarColaborador(colaborador* c) {
    colaboradores.agregar((void*)c);
}

void sucursal::agregarVehiculo(vehiculo* v) {
    vehiculos.agregar((void*)v);
}

lista* sucursal::getPlanteles() {
    return &planteles;
}

lista* sucursal::getClientes() {
    return &clientes;
}

lista* sucursal::getColaboradores() {
    return &colaboradores;
}

lista* sucursal::getVehiculos() {
    return &vehiculos;
}

void sucursal::mostrarResumen() const {
    cout << "========================================" << endl;
    cout << "Sucursal #" << idSucursal << " - " << nombre << endl;
    cout << "Provincia: " << provincia << endl;
    cout << "========================================" << endl;
}

string sucursal::toString() const {
    return "Sucursal #" + to_string(idSucursal) + " - " + nombre + " (" + provincia + ")";
}