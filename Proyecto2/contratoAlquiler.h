#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "solicitudAlquiler.h"

using namespace std;

class contratoAlquiler : public solicitudAlquiler {
private:
    string estadoContrato;
    int diasRealesUso;

public:
    contratoAlquiler();
    contratoAlquiler(const solicitudAlquiler& solicitudAprobada);

    string getEstadoContrato() const;
    int getDiasRealesUso() const;

    void finalizarContrato(int diasUtilizados);
    double calcularMontoFinal() const;

    string toString() const override;
};