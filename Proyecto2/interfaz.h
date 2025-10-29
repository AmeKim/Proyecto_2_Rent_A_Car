#pragma once
#include <iostream>
#include <sstream>
#include <string>
#include "utiles.h"
#include "sucursal.h"
#include "colaborador.h"
#include "vehiculo.h"
#include "plantel.h"
#include "solicitudAlquiler.h"
#include "cliente.h"
#include "personaFisica.h"
#include "personaJuridica.h"

using namespace std;

class Interfaz {
public:
    // Métodos generales
    static void imprimirMensaje(string m);
    static void imprimirTitulo(string t);

    // Menús principales
    static int menuPrincipal();
    static int submenuSucursal();
    static int submenuColaborador();
    static int submenuVehiculosYPlanteles();
    static int submenuSolicitudesYContratos();
    static int submenuClientes();

    // Métodos para Sucursales
    static sucursal* capturarDatosSucursal();
    static int solicitarIDSucursal();

    // Métodos para Colaboradores
    static colaborador* capturarDatosColaborador();
    static string solicitarIDColaborador();

    // Métodos para Vehículos y Planteles
    static vehiculo* capturarDatosVehiculo();
    static plantel* capturarDatosPlantel();

    // Métodos para Clientes
    static cliente* capturarDatosCliente();
    static personaFisica* capturarDatosPersonaFisica();
    static personaJuridica* capturarDatosPersonaJuridica();

    // Métodos para Solicitudes
    static solicitudAlquiler* capturarDatosSolicitud();
};