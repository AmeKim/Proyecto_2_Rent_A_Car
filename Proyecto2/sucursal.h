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

    // Listas genéricas (usando punteros void*)
    lista planteles;
    lista clientes;
    lista colaboradores;
    lista vehiculos;

public:
    sucursal();
    sucursal(int id, const string& nombre, const string& provincia);

    int getIdSucursal() const;
    string getNombre() const;
    string getProvincia() const;

    void agregarPlantel(plantel* p);
    void agregarCliente(cliente* c);
    void agregarColaborador(colaborador* c);
    void agregarVehiculo(vehiculo* v);

    void mostrarResumen() const;
    string toString() const;
};
