#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "listaBase.h"
#include "sucursal.h"

using namespace std;

class SistemaRentACar : public listaBase<sucursal> {
public:
    SistemaRentACar();
    ~SistemaRentACar();

    void agregarSucursal(sucursal* suc);
    bool eliminarSucursal(int id);
    sucursal* buscarSucursal(int id);

    string mostrarSucursales() const;
    string reporteOcupacionPlanteles();

    // Traslado de vehículos entre sucursales
    bool trasladarVehiculos(int idSucursalOrigen, int idSucursalDestino,
        int cantidadVehiculos);
};