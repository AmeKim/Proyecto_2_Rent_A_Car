#include "carteraClientes.h"

carteraClientes::carteraClientes(){
	clientes = new lista();
}

carteraClientes::~carteraClientes(){

}

void carteraClientes::agregarCliente(cliente* nuevoCliente){
}

void carteraClientes::eliminarCliente(const string& dni){
}

cliente* carteraClientes::buscarCliente(const string& dni) const{
	return;
}

int carteraClientes::getCantidadClientes() const{
	return 0;
}

int carteraClientes::getCantidadPersonasFisicas() const{
	return 0;
}

int carteraClientes::getCantidadPersonasJuridicas() const{
	return 0;
}

void carteraClientes::mostrarClientesFisicos() const{
}

void carteraClientes::mostrarClientesJuridicos() const{
}

void carteraClientes::mostrarClienteEspecifico(const string& dni) const{
}

void carteraClientes::mostrarClientes() const{
}
