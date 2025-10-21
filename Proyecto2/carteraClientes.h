#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "lista.h"
#include "cliente.h"
#include "personaFisica.h"
#include "personaJuridica.h"
using namespace std;
class carteraClientes{
	private:
		lista* clientes;
		
public:
	carteraClientes();
	~carteraClientes();

	void agregarCliente(cliente* nuevoCliente);
	void eliminarCliente(const string& dni);
	cliente* buscarCliente(const string& dni) const;

	int getCantidadClientes() const;
	int getCantidadPersonasFisicas() const;
	int getCantidadPersonasJuridicas() const;

	void mostrarClientesFisicos() const;
	void mostrarClientesJuridicos() const;
	void mostrarClienteEspecifico(const string& dni) const;
	void mostrarClientes() const;
};

