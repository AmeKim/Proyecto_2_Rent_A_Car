#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "listaBase.h"
#include "sucursal.h"

using namespace std;

class SistemaRentACar {
private:
    listaBase<sucursal>* sucursales;

public:
    SistemaRentACar();
    ~SistemaRentACar();

    bool agregarSucursal(sucursal* suc);
    bool eliminarSucursal(int idSucursal);
    sucursal* buscarSucursal(int idSucursal);

    string mostrarSucursales() const;
    int contarSucursales() const;

    // Reportes globales
    string reporteClientesPorContratos();
    string reporteHistorialCliente(const string& idCliente);

    // Traslado de vehículos entre sucursales
    bool trasladarVehiculo(const string& placa, int idSucursalOrigen, int idSucursalDestino);
};