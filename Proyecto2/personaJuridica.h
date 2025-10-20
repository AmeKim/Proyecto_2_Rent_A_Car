#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "cliente.h"

using namespace std;

class personaJuridica : public cliente{
	string actividadEconomica;
	float porcDescuento;
public:
	personaJuridica();
	personaJuridica(string, string, string, string , float);
	~personaJuridica();
	void setActividadEconomica(string);
	string getActividadEconomica() const;
	void setPorcDescuento(float descuento);
	float getPorcDescuento() const;
	string toString();
};

