#pragma once
#include <iostream>
#include <sstream>
#include "listaBase.h"
#include "espacioEstacionamiento.h"
#include "utiles.h"

using namespace std;

class listaEstacionamiento : public listaBase<espacioEstacionamiento> {
private:
	nodoBase<espacioEstacionamiento>* actual;
	nodoBase<espacioEstacionamiento>* primero;
public:
	listaEstacionamiento();
	~listaEstacionamiento();
	int contarEspaciosLibres();

	string toStringLista();

	
};