#pragma once
#include <string>
#include <iostream>
#include "lista.h"
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
    lista planteles;
    lista clientes;
    lista colaboradores;
    lista vehiculos;

public:
    sucursal();
    sucursal(int id, const string& nom, const string& prov);
    ~sucursal();

    int getIdSucursal() const;
    string getNombre() const;
    string getProvincia() const;

    void agregarPlantel(plantel* p);
    void agregarCliente(cliente* c);
    void agregarColaborador(colaborador* c);
    void agregarVehiculo(vehiculo* v);

    lista* getPlanteles();
    lista* getClientes();
    lista* getColaboradores();
    lista* getVehiculos();

    void mostrarResumen() const;
    string toString() const;
};