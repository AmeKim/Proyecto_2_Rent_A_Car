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
    // M�todos generales
    static void imprimirMensaje(string m);
    static void imprimirTitulo(string t);

    // Men�s principales
    static int menuPrincipal();
    static int submenuSucursal();
    static int submenuColaborador();
    static int submenuVehiculosYPlanteles();
    static int submenuSolicitudesYContratos();
    static int submenuClientes();

    // M�todos para Sucursales
    static sucursal* capturarDatosSucursal();
    static int solicitarIDSucursal();

    // M�todos para Colaboradores
    static colaborador* capturarDatosColaborador();
    static string solicitarIDColaborador();

    // M�todos para Veh�culos y Planteles
    static vehiculo* capturarDatosVehiculo();
    static plantel* capturarDatosPlantel();

    // M�todos para Clientes
    static cliente* capturarDatosCliente();
    static personaFisica* capturarDatosPersonaFisica();
    static personaJuridica* capturarDatosPersonaJuridica();

    // M�todos para Solicitudes
    static solicitudAlquiler* capturarDatosSolicitud();
};