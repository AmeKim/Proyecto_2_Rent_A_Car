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

using namespace std;
class Interfaz {
public:
	static int menuPrincipal();
	static int submenuSucursal();
	static int submenuColaborador();
	static int submenuVehiculosYPlanteles();
	static int submenuSolicitudesYContratos();
	static int submenuClientes();

	//--------------------Metodos para Sucursales--------------------------

	static void agregarSucursal();
	static void mostrarSucursales();
	static void eliminarSucursal();

	//--------------------Metodos para Colaboradores-----------------------
	static void agregarColaborador();
	static void mostrarColaboradorEspecifico();
	static void eliminarColaborador();
	static string reportesPorColaborador();


	//------------------Metodos para Carros y Planteles---------------------
	static void agregarPlantel();
	static void visualizarPlantel();
	static void agregarVehiculo();
	static void eliminarVehiculo();
	static void reasignarVehiculo();
	static void cambiarEstadoVehiculo();
	static void visualizarEstadoVehiculo();
	static void generarReportePorcentajeOcupacion();
	static void trasladoVehiculosASucursal();

	//--------------Metodos para Solicitudes y Contratos--------------------
	static void crearSolicitudAlquiler();
	static void mostrarSolicitudesPorSucursal();
	static void mostrarSolicitudEspecifica();
	static void aprobarRechazarSolicitud();
	static void recibirVehiculoAlquilado();
	static void generarReporteContratos();

	//----------------------Metodos para Clientes----------------------------
	static void agregarCliente();
	static void mostrarCliente();
	static void eliminarCliente();
	static void historialAlquileresCliente();
	static void reporteCantidadContratosPorCliente();
};