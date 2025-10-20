#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class colaborador{
private:
	string nombre;
	string cedula;
	string fechaIngreso;
public:
	colaborador();
	colaborador(string nombre, string cedula, string fechaIngreso);
	~colaborador();
	string getNombre() const;
	string getCedula() const;
	string getFechaIngreso() const;
	void setNombre(string nombre);
	void setCedula(string cedula);
	void setFechaIngreso(string fechaIngreso);
	string toString();

};

