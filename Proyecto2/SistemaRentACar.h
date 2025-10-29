#pragma once
#include <string>
#include <sstream>
#include "listaBase.h"
#include "sucursal.h"
using namespace std;

class SistemaRentACar {
private:
    listaBase<sucursal>* sucursales;
    int contadorCodigoSolicitud;
    int contadorCodigoContrato;

public:
    SistemaRentACar();
    ~SistemaRentACar();

    // Sucursales
    void registrarSucursal(sucursal* s);
    bool eliminarSucursal(int id);
    sucursal* buscarSucursalPorId(int id);
    string mostrarSucursales();

    bool buscarIDEntreSucursales(int id);
    bool estaVacio();

    // Generadores de códigos únicos
    string generarCodigoSolicitud();
    string generarCodigoContrato();

    // Reportes globales
    string reporteClientesPorContratos();
    string reporteAlquileresPorColaborador(string cedulaColaborador);
};