#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class vehiculo{
	private:
	string placa;
	string modelo;
	string marca;
	string tipoLicencia;
	int precio;
	string estado;
	char categoria;
	string ubicacionPlantel;
public:
	vehiculo();
	vehiculo(string placa, string modelo, string marca, string tipoLicencia, int precio, string estado, char categoria, string ubicacionPlantel);
	~vehiculo();
	string getPlaca() const;
	void setPlaca(string placa);
	string getModelo() const;
	void setModelo(string modelo);
	string getMarca() const;
	void setMarca(string marca);
	string getTipoLicencia() const;
	void setTipoLicencia(string tipoLicencia);
	int getPrecio() const;
	void setPrecio(int precio);
	string getEstado() const;
	void setEstado(string estado);
	char getCategoria() const;
	void setCategoria(char categoria);
	string getUbicacionPlantel() const;
	void setUbicacionPlantel(string ubicacionPlantel);
	string toString();
};

