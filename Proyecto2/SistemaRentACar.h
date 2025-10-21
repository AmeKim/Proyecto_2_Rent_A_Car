#pragma once
#include <string>
#include "lista.h"
#include "sucursal.h"
using namespace std;

class SistemaRentACar {
private:
    lista sucursales;

public:
    SistemaRentACar();
    ~SistemaRentACar();

    void registrarSucursal(sucursal* s);
    void mostrarSucursales();
    sucursal* buscarSucursalPorId(int id);
};