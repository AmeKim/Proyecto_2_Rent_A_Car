#pragma once
#include <iostream>
#include <sstream>
#include "interfaz.h"
#include "SistemaRentACar.h"
#include "sucursal.h"
#include "plantel.h"
#include "vehiculo.h"
#include "cliente.h"
#include "personaFisica.h"
#include "personaJuridica.h"
#include "colaborador.h"
#include "solicitudAlquiler.h"
#include "contratoAlquiler.h"
#include "utiles.h"

using namespace std;

class controller {
private:
    SistemaRentACar* sistema;

    // Métodos privados para gestionar cada módulo
    void gestionarSucursales();
    void gestionarColaboradores();
    void gestionarVehiculos();
    void gestionarSolicitudes();
    void gestionarClientes();

    // Métodos auxiliares
    int seleccionarSucursal();
    sucursal* obtenerSucursal();
    void cargarDatosQuemados(); // Para pruebas rápidas

public:
    controller();
    virtual ~controller();
    int iniciarSistema();
};