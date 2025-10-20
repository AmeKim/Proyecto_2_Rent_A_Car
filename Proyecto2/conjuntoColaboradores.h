#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "colaborador.h"

using namespace std;
class conjuntoColaboradores{
	private:
		int capacidad;
		int cantidad;
		colaborador** colaboradores;
	public:
		conjuntoColaboradores(int capacidad);
		~conjuntoColaboradores();
		void agregarColaborador(const colaborador* colab);
		bool eliminarColaborador(const string cedula);
		colaborador* buscarColaborador(const string cedula);
		void mostrarColaboradores();
};

