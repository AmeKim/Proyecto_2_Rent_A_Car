#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "listaBase.h"
#include "plantel.h"
#include "carteraClientes.h"
#include "conjuntoColaboradores.h"
#include "inventarioVehiculos.h"
#include "solicitudAlquiler.h"
#include "contratoAlquiler.h"

using namespace std;

class sucursal {
private:
    int idSucursal;
    string nombre;
    string provincia;
    listaBase<plantel>* planteles;
    carteraClientes* clientes;
    conjuntoColaboradores* colaboradores;
    inventarioVehiculos* vehiculos;
    listaBase<solicitudAlquiler>* solicitudes;
    listaBase<contratoAlquiler>* contratos;

public:
    sucursal();
    sucursal(int id, const string& nom, const string& prov);
    ~sucursal();

    int getIdSucursal() const;
    string getNombre() const;
    string getProvincia() const;

    // Planteles
    bool agregarPlantel(plantel* p);
    plantel* buscarPlantel(string nombre);
    string mostrarPlanteles() const;

    // Clientes
    carteraClientes* getCarteraClientes();

    // Colaboradores
    conjuntoColaboradores* getConjuntoColaboradores();

    // Vehiculos
    inventarioVehiculos* getInventarioVehiculos();
    vehiculo* buscarVehiculoPorPlaca(string placa);

    // Solicitudes y contratos
    bool agregarSolicitud(solicitudAlquiler* sol);
    bool agregarContrato(contratoAlquiler* con);
    solicitudAlquiler* buscarSolicitudPorCodigo(string codigo);
    contratoAlquiler* buscarContratoPorCodigo(string codigo);
    string mostrarSolicitudes() const;
    string mostrarContratos() const;

    // Recomendación de espacios
    string recomendarEspacioEstacionamiento();

    void mostrarResumen() const;
    string toString() const;
};