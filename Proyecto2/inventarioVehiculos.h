#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "vehiculo.h"
#include "listaBase.h"

using namespace std;

class inventarioVehiculos : public listaBase<vehiculo> {
private:
	nodoBase<vehiculo>* primero;
    nodoBase<vehiculo>* actual;
public:
    inventarioVehiculos();
    ~inventarioVehiculos();
    void agregarVehiculo(vehiculo* v);
    void eliminarVehiculo(vehiculo* v);
    string mostrarVehiculos() const;
    string mostrarTotalDeEstados();
};
