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
    cliente* cliente;
    colaborador* colaborador;
    vehiculo* vehiculo;
    int dias;
    string fechaInicio;
    string fechaEntrega;
    double precioDia;
    double precioTotal;
    string estado; // "Pendiente", "Aprobada", "Rechazada", "Anulada"

public:
    solicitudAlquiler();
    solicitudAlquiler(const string& cod, cliente* cli, colaborador* col, vehiculo* veh,int dias, const string& fInicio, const string& fEntrega, double pDia);

    string getCodigo() const;
    string getEstado() const;
    double getPrecioTotal() const;
    int getDias() const;

    void aprobar();
    void rechazar();
    void anular();

    void mostrarInfo() const;
    string toString() const;
};
