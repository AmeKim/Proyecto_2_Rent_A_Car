#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "listaBase.h"
#include "registroBitacora.h"

using namespace std;

class vehiculo {
private:
    string placa;
    string modelo;
    string marca;
    string tipoLicencia;
    double precio;
    string estado;
    char categoria;
    string ubicacionPlantel;
    listaBase<registroBitacora>* bitacora;

public:
    vehiculo();
    vehiculo(string placa, string modelo, string marca, string tipoLicencia,
        double precio, string estado, char categoria, string ubicacionPlantel);
    ~vehiculo();

    string getPlaca() const;
    void setPlaca(string placa);
    string getModelo() const;
    void setModelo(string modelo);
    string getMarca() const;
    void setMarca(string marca);
    string getTipoLicencia() const;
    void setTipoLicencia(string tipoLicencia);
    double getPrecio() const;
    void setPrecio(double precio);
    string getEstado() const;
    void setEstado(string estado);
    char getCategoria() const;
    void setCategoria(char categoria);
    string getUbicacionPlantel() const;
    void setUbicacionPlantel(string ubicacionPlantel);

    bool cambiarEstado(string nuevoEstado, string fecha, colaborador* responsable);
    string mostrarBitacora() const;

    string toString() const;
};