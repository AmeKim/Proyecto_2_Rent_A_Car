#pragma once
#include <iostream>
#include <string>
using namespace std;
class espacioEstacionamiento{
	private:
	string codigo;
	bool ocupado;
public:
	espacioEstacionamiento();
	espacioEstacionamiento(string codigo, bool ocupado);
	~espacioEstacionamiento();
	string getCodigo() const;
	void setCodigo(string codigo);
	bool estaOcupado() const;
	void ocupar();
	void desocupar();
	string toString();
};

