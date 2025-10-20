#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "espacioEstacionamiento.h"

using namespace std;

class plantel{
private:
    string nombre;
    char tipo;
    int capacidadMax;
    espacioEstacionamiento* espacios;
public:
    plantel();
    plantel(string nombre, string ubicacion, int capacidad);
    ~plantel();
    string getNombre() const;
    void setNombre(string nombre);
    espacioEstacionamiento* getEspacios() const;
    void setEspacios(espacioEstacionamiento* espacios);
	int getCapacidadMax() const;
	void setCapacidadMax(int capacidad);

};

