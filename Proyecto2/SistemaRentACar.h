#pragma once
#include <string>
#include "listaBase.h"
#include "sucursal.h"
using namespace std;

class SistemaRentACar {
private:
    listaBase<sucursal*> sucursales;

public:
    SistemaRentACar();
    ~SistemaRentACar();

    void registrarSucursal(sucursal* s);
    string mostrarSucursales();
    sucursal* buscarSucursalPorId(int id);
};