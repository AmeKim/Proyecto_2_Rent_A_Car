#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "listaBase.h"
#include "cliente.h"
#include "personaFisica.h"
#include "personaJuridica.h"

using namespace std;

class carteraClientes : public listaBase<cliente> {
public:
    carteraClientes();
    ~carteraClientes();

    bool agregarClienteFisico(personaFisica* fis);
    bool agregarClienteJuridico(personaJuridica* jur);
    bool eliminarCliente(string id);
    bool estaVacio();

    personaFisica* buscarporCedula(string id);
    personaJuridica* buscarporCedulaJuridica(string id);
    cliente* buscarClientePorCedula(string id);

    string mostrarClientesFisicos();
    string mostrarClientesJuridicos();
    string mostrarTodosLosClientes();
};