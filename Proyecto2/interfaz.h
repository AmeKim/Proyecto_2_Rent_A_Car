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

// Estructura auxiliar para capturar datos de solicitud
struct DatosSolicitud {
    string codigo;
    string idCliente;
    string idColaborador;
    string placaVehiculo;
    int dias;
    string fechaInicio;
    string fechaEntrega;
    double precioDia;
};

class Interfaz {
public:
    // ==================== METODOS GENERALES ====================
    static void imprimirMensaje(string m);
    static void imprimirTitulo(string t);
    static void mostrarSeparador();
    static void mostrarMensajeExito(string mensaje);
    static void mostrarMensajeError(string mensaje);
    static void mostrarMensajeAdvertencia(string mensaje);

    // ==================== MENUS PRINCIPALES ====================
    static int menuPrincipal();
    static int submenuSucursal();
    static int submenuColaborador();
    static int submenuVehiculosYPlanteles();
    static int submenuSolicitudesYContratos();
    static int submenuClientes();

    // ==================== METODOS PARA SUCURSALES ====================
    static sucursal* capturarDatosSucursal();
    static int solicitarIDSucursal();
    static int solicitarIDSucursalDestino();

    // ==================== METODOS PARA COLABORADORES ====================
    static colaborador* capturarDatosColaborador();
    static string solicitarIDColaborador();

    // ==================== METODOS PARA VEHICULOS Y PLANTELES ====================
    static vehiculo* capturarDatosVehiculo();
    static string solicitarPlacaVehiculo();
    static plantel* capturarDatosPlantel();
    static char solicitarLetraPlantel();
    static string solicitarCodigoEspacio();

    // ==================== METODOS PARA CLIENTES ====================
    static cliente* capturarDatosCliente();
    static personaFisica* capturarDatosPersonaFisica();
    static personaJuridica* capturarDatosPersonaJuridica();
    static string solicitarIDCliente();

    // ==================== METODOS PARA SOLICITUDES ====================
    static DatosSolicitud capturarDatosSolicitud();
    static string solicitarCodigoSolicitud();
    static int solicitarDiasAlquiler();
    static int solicitarDiasUtilizados();
    static string solicitarFecha(string tipoFecha);
    static int menuAprobarRechazar();

    // ==================== METODOS PARA CAMBIO DE ESTADO ====================
    static string menuCambioEstado(string estadoActual);
    static void mostrarTablaEstados();

    // ==================== METODOS PARA VISUALIZACION ====================
    static void mostrarEncabezadoPlantel(char letra, int tipo, int capacidad);

    // ==================== METODOS PARA CONFIRMACION ====================
    static bool confirmarAccion(string mensaje);
    static int seleccionarOpcionDeLista(int cantidadOpciones);

    // ==================== METODOS PARA REPORTES ====================
    static void mostrarEncabezadoReporte(string tituloReporte);
    static void mostrarPieReporte();

    // ==================== METODOS PARA TRASLADO (OPCIONAL) ====================
    static int solicitarCantidadVehiculosTraslado();
};