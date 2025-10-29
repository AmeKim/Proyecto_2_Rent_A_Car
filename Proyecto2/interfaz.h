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

	static void imprimirMensaje(string m);
	static void imprimirTitulo(string t);

	static int menuPrincipal();
	static int submenuSucursal();
	static int submenuColaborador();
	static int submenuVehiculosYPlanteles();
	static int submenuSolicitudesYContratos();
	static int submenuClientes();

	//--------------------Metodos para Sucursales--------------------------

	static sucursal* capturarDatosSucursal();
	static int solicitarIDSucursal();


	//--------------------Metodos para Colaboradores-----------------------
	static colaborador* capturarDatosColaborador();
	static string solicitarIDColaborador();


	//------------------Metodos para Carros y Planteles---------------------
	static void capturarDatosPlantel();
	static vehiculo* CapturarDatosVehiculo();


	//--------------Metodos para Solicitudes y Contratos--------------------


	//----------------------Metodos para Clientes----------------------------

};