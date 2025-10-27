#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "cliente.h"

using namespace std;

class personaJuridica : public cliente {
private:
    string actividadEconomica;
    float porcDescuento;

public:
    personaJuridica();
    personaJuridica(string cedula, string nombre, string paisResidencia,
        string actividadEconomica, float porcDescuento);
    ~personaJuridica();

    void setActividadEconomica(string actividad);
    string getActividadEconomica() const;
    void setPorcDescuento(float descuento);
    float getPorcDescuento() const;

    string toString() const override;
};