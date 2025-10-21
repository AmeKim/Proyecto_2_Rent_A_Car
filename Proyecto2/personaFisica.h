#pragma once
#include <string>
#include <iostream>
#include "cliente.h"

using namespace std;

class personaFisica : public cliente {
private:
    string tipoLicencia;  // Tipo de licencia de conducir (ej: B1, B2, etc.)

public:
    personaFisica();
    personaFisica(const string& id, const string& nombre,const string& pais, const string& tipoLicencia);

    string getTipoLicencia() const;
    void setTipoLicencia(const string& tipo);

    string toString() const;
    void mostrarInfo() const override;
};
