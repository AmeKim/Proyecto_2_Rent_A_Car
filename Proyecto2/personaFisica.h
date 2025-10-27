#pragma once
#include <string>
#include <iostream>
#include <sstream>
#include "cliente.h"

using namespace std;

class personaFisica : public cliente {
private:
    string tipoLicencia;

public:
    personaFisica();
    personaFisica(const string& cedula, const string& nombre, const string& pais, const string& tipoLicencia);
    ~personaFisica();

    string getTipoLicencia() const;
    void setTipoLicencia(const string& tipo);

    string toString() const override;
};