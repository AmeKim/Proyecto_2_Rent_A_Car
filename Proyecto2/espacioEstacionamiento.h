#pragma once
#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class espacioEstacionamiento {
private:
    string codigo;
    bool ocupado;
    string placaVehiculo; // NUEVO ATRIBUTO

public:
    espacioEstacionamiento();
    espacioEstacionamiento(string codigo, bool ocupado);
    ~espacioEstacionamiento();

    string getCodigo() const;
    void setCodigo(string codigo);

    bool estaOcupado() const;
    void ocupar();
    void desocupar();

    void liberarEspacio();
    string getVehiculo() const;
    string getPlacaVehiculo() const;
    void setPlacaVehiculo(string placa);

    string toString();
};