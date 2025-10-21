#pragma once
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class cliente {
private:
    string nombre;
    string cedula;
    string paisResidencia;

public:
    cliente();
    cliente(string nombre, string cedula, string paisResidencia);
    virtual ~cliente();

    string getNombre() const;
    string getCedula() const;
    string getPaisResidencia() const;

    void setNombre(string nombre);
    void setCedula(string cedula);
    void setPaisResidencia(string paisResidencia);

    virtual void mostrarInfo() const;
    virtual string toString() const;
};