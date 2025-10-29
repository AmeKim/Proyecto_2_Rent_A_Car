#pragma once
#include <iostream>
#include<sstream>
#include "interfaz.h"
#include "espacioEstacionamiento.h"
#include "SistemaRentACar.h"
#include "listaEstacionamiento.h"
#include "conjuntoColaboradores.h"
#include "carteraClientes.h"
#include "inventarioVehiculos.h"
#include "sucursal.h"
#include "utiles.h"

using namespace std;

class controller {
private:
	SistemaRentACar* sucursales;
	conjuntoColaboradores* colaboradores;
	carteraClientes* clientes;
	inventarioVehiculos* vehiculos;

	//metodos privados para gestionar cada modulo
	void gestionarSucursales();
	void gestionarColaboradores();
	void gestionarVehiculos();
	void gestionarSolicitudes();
	void gestionarClientes();

	int seleccionarSucursal();
public:
	controller();
	virtual ~controller();
	int iniciarSistema();

};