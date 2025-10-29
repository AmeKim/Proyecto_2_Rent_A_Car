#pragma once
#include <iostream>
#include <string>
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
    int id;
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
    sucursal(int id, string nombre, string provincia);
    ~sucursal();

    int getId() const;
    string getNombre() const;
    string getProvincia() const;

    void setId(int id);
    void setNombre(string nombre);
    void setProvincia(string provincia);

    // Gestión de planteles
    void agregarPlantel(plantel* p);
    plantel* buscarPlantel(string nombre);
    string mostrarPlanteles() const;
    string reporteOcupacionPlanteles();

    // Gestión de clientes
    carteraClientes* getClientes();
    void agregarClienteFisico(personaFisica* pf);
    void agregarClienteJuridico(personaJuridica* pj);
    bool eliminarCliente(string id);
    string mostrarClientes();

    // Gestión de colaboradores
    conjuntoColaboradores* getColaboradores();
    void agregarColaborador(colaborador* col);
    bool eliminarColaborador(string id);
    string mostrarColaboradores();

    // Gestión de vehículos
    inventarioVehiculos* getVehiculos();
    void agregarVehiculo(vehiculo* v);
    bool eliminarVehiculo(string placa);
    string mostrarVehiculos();
    vehiculo* buscarVehiculo(string placa);

    // Gestión de solicitudes y contratos
    void agregarSolicitud(solicitudAlquiler* sol);
    void agregarContrato(contratoAlquiler* con);
    solicitudAlquiler* buscarSolicitud(string codigo);
    contratoAlquiler* buscarContrato(string codigo);
    string mostrarSolicitudes();
    string mostrarContratos();
    string mostrarContratosOrdenados();

    // Reportes
    string historialCliente(string idCliente);
    string reporteClientesPorContratos();
    string reporteContratosVehiculo(string placa);
    string reporteAlquileresPorColaborador(string idColaborador);

    // Traslado de vehículos
    listaBase<vehiculo>* obtenerVehiculosDisponiblesParaTraslado();
    bool removerVehiculo(vehiculo* v);
    bool agregarVehiculoDeTraslado(vehiculo* v, string nombrePlantel, string espacioEstacionamiento);

    string toString() const;
};