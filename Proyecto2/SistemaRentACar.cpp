#include "SistemaRentACar.h"
#include <iostream>

SistemaRentACar::SistemaRentACar() {}
SistemaRentACar::~SistemaRentACar() {}

void SistemaRentACar::registrarSucursal(sucursal* s) {
    sucursales.agregar((void*)s);
}

sucursal* SistemaRentACar::buscarSucursalPorId(int id) {
    sucursales.reiniciar();
    void* dato;
    while ((dato = sucursales.siguiente()) != nullptr) {
        sucursal* s = (sucursal*)dato;
        if (s->getIdSucursal() == id) return s;
    }
    return nullptr;
}

void SistemaRentACar::mostrarSucursales() {
    sucursales.reiniciar();
    void* dato;
    while ((dato = sucursales.siguiente()) != nullptr) {
        ((sucursal*)dato)->mostrarResumen();
    }
}
