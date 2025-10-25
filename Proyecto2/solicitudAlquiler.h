#pragma once
#include <string>
#include <iostream>
#include "cliente.h"
#include "colaborador.h"
#include "vehiculo.h"

using namespace std;

class solicitudAlquiler {
private:
    string codigo;
    cliente* cli;
    colaborador* col;
    vehiculo* veh;
    int dias;
    string fechaInicio;
    string fechaEntrega;
    double precioDia;
    double precioTotal;
    string estado;

public:
    solicitudAlquiler();
    solicitudAlquiler(const string cod, cliente* cliente, colaborador* colaborador,
    vehiculo* vehiculo, int dias, const string fInicio, const string fEntrega, double pDia);

    string getCodigo() const;
    string getEstado() const;
    double getPrecioTotal() const;
    int getDias() const;
    string getFechaInicio() const;
    string getFechaEntrega() const;
    double getPrecioDia() const;
    cliente* getCliente() const;
    colaborador* getColaborador() const;
    vehiculo* getVehiculo() const;

    void aprobar();
    void rechazar();
    void anular();

    void mostrarInfo() const;
    string toString() const;
};