#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "vehiculo.h"
#include "listaBase.h"

using namespace std;

class inventarioVehiculos : public listaBase<vehiculo> {
public:
    inventarioVehiculos();
    ~inventarioVehiculos();

    void agregarVehiculo(vehiculo* v);
    bool eliminarVehiculoPorPlaca(string placa);
    vehiculo* buscarVehiculoPorPlaca(string placa);

    string mostrarVehiculos() const;
    string mostrarVehiculosDisponibles() const;
    string mostrarTotalDeEstados();

    nodoBase<vehiculo>* getPrimero() { return primero; }
};
