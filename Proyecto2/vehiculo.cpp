#include "vehiculo.h"

vehiculo::vehiculo(){
	placa = "";
	modelo = "";
	marca = "";
	tipoLicencia = "";
	precio = 0;
	estado = "";
	categoria = ' ';
	ubicacionPlantel = "";
}

vehiculo::vehiculo(string placa, string modelo, string marca, string tipoLicencia, int precio, string estado, char categoria, string ubicacionPlantel){
	this->placa = placa;
	this->modelo = modelo;
	this->marca = marca;
	this->tipoLicencia = tipoLicencia;
	this->precio = precio;
	this->estado = estado;
	this->categoria = categoria;
	this->ubicacionPlantel = ubicacionPlantel;
}

vehiculo::~vehiculo(){
}

string vehiculo::getPlaca() const{
	return placa;
}

void vehiculo::setPlaca(string placa)
{
	this->placa = placa;
}

string vehiculo::getModelo() const
{
	return modelo;
}

void vehiculo::setModelo(string modelo)
{
	this->modelo = modelo;	
}

string vehiculo::getMarca() const{
	return marca;
}

void vehiculo::setMarca(string marca){
	this->marca = marca;
}

string vehiculo::getTipoLicencia() const{
	return tipoLicencia;
}

void vehiculo::setTipoLicencia(string tipoLicencia){
	this->tipoLicencia = tipoLicencia;
}

int vehiculo::getPrecio() const{
	return precio;
}

void vehiculo::setPrecio(int precio){
	this->precio = precio;
}

string vehiculo::getEstado() const{
	return string();
}

void vehiculo::setEstado(string estado){
	this->estado = estado;
}

char vehiculo::getCategoria() const{
	return categoria;
}

void vehiculo::setCategoria(char categoria){
	this->categoria = categoria;
}

string vehiculo::getUbicacionPlantel() const{
	return ubicacionPlantel;
}

void vehiculo::setUbicacionPlantel(string ubicacionPlantel){
	this->ubicacionPlantel = ubicacionPlantel;
}

string vehiculo::toString(){
	stringstream s;
	s << "Placa: " << placa << endl;
	s << "Modelo: " << modelo << endl;
	s << "Marca: " << marca << endl;
	s << "Tipo de Licencia: " << tipoLicencia << endl;
	s << "Precio: " << precio << endl;
	s << "Estado: " << estado << endl;
	s << "Categoria: " << categoria << endl;
	s << "Ubicacion en Plantel: " << ubicacionPlantel << endl;
	return s.str();	
}