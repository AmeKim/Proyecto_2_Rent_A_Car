#pragma once
#include <string>
#include <iostream>
#include "listaBase.h"
#include "plantel.h"
#include "cliente.h"
#include "colaborador.h"
#include "vehiculo.h"

using namespace std;

class sucursal {
private:
    int idSucursal;
    string nombre;
    string provincia;
	listaBase<plantel*> planteles;
	listaBase<cliente*> clientes;
	listaBase<colaborador*> colaboradores;
    listaBase<vehiculo*> vehiculos;

public:
    sucursal();
    sucursal(int id, const string& nom, const string& prov);
    ~sucursal();

    int getIdSucursal() const;
    string getNombre() const;
    string getProvincia() const;

    bool agregarPlantel(plantel* p);
    bool agregarCliente(cliente* c);
    bool agregarColaborador(colaborador* c);
    bool agregarVehiculo(vehiculo* v);

    void mostrarResumen() const;
    string toString() const;
};