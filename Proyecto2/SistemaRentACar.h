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

    // Gestión de sucursales
    bool agregarSucursal(sucursal* suc);
    bool eliminarSucursal(int idSucursal);
    sucursal* buscarSucursal(int idSucursal);
    string mostrarSucursales() const;
    int contarSucursales() const;

    // Reportes globales
    string reporteHistorialCliente(const string& idCliente);
    string reporteClientesPorContratos();

    // Traslado de vehículos (opcional)
    bool trasladarVehiculo(const string& placa, int idSucursalOrigen, int idSucursalDestino);

    // Acceso a la lista de sucursales
    listaBase<sucursal>* getSucursales() { return sucursales; }
};