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
    int idSucursal;
    string nombre;
    string provincia;

    listaBase<plantel>* planteles;
    carteraClientes* clientes;
    conjuntoColaboradores* colaboradores;
    inventarioVehiculos* vehiculos;
    listaBase<solicitudAlquiler>* solicitudes;
    listaBase<contratoAlquiler>* contratos;

	int compararFechas(const string& fecha1, const string& fecha2) const;

public:
    sucursal();
    sucursal(int id, const string& nombre, const string& provincia);
    ~sucursal();

    // Getters
    int getIdSucursal() const;
    string getNombre() const;
    string getProvincia() const;

    // Setters
    void setIdSucursal(int id);
    void setNombre(const string& nombre);
    void setProvincia(const string& provincia);

    // Gestión de planteles
    bool agregarPlantel(plantel* p);
    plantel* buscarPlantel(char letra);
    string mostrarPlanteles() const;
    plantel* encontrarPlantelConMasEspacios();
    string reportePorcentajeOcupacion() const;

    // Gestión de clientes
    carteraClientes* getClientes();

    // Gestión de colaboradores
    conjuntoColaboradores* getColaboradores();

    // Gestión de vehículos
    inventarioVehiculos* getVehiculos();
    bool agregarVehiculoASucursal(vehiculo* v, char letraPlantel, int fila, int columna);
    bool eliminarVehiculoDeSucursal(const string& placa);
    bool reubicarVehiculo(const string& placa, char nuevoPlantel, int fila, int columna);

    // Gestión de solicitudes
    bool agregarSolicitud(solicitudAlquiler* sol);
    solicitudAlquiler* buscarSolicitud(const string& codigo);
    string mostrarSolicitudes() const;
    bool aprobarSolicitud(const string& codigo);
    bool rechazarSolicitud(const string& codigo);

    // NUEVO: Getter público para solicitudes
    listaBase<solicitudAlquiler>* getSolicitudes() { return solicitudes; }

    // Gestión de contratos
    bool agregarContrato(contratoAlquiler* contrato);
    contratoAlquiler* buscarContrato(const string& codigo);
    string mostrarContratos() const;
    string mostrarContratosOrdenados() const;

    // NUEVO: Getter público para contratos
    listaBase<contratoAlquiler>* getContratos() { return contratos; }

    // Reportes
    string reporteContratosVehiculo(const string& placa) const;
    string reporteAlquileresColaborador(const string& idColaborador) const;


    string toString() const;
};