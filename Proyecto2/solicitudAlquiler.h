#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "cliente.h"
#include "colaborador.h"
#include "vehiculo.h"
#include "personaJuridica.h"

using namespace std;

class solicitudAlquiler {
protected:
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
    solicitudAlquiler(const string& cod, cliente* cliente, colaborador* colaborador,
        vehiculo* vehiculo, int dias, const string& fInicio,
        const string& fEntrega, double pDia);
    virtual ~solicitudAlquiler();

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

    virtual string toString() const;
};