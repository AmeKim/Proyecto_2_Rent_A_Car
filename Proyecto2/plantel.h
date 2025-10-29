#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "matriz.h"
#include "espacioEstacionamiento.h"

using namespace std;

class plantel {
private:
    string nombre;
    int tipo;  // 1: Techado y asfaltado, 2: Techado y lastreado, 3: Asfaltado, 4: Lastreado
    int capacidadMax;
    int filas;
    int columnas;
    matriz* espacios;

public:
    plantel();
    plantel(string nombre, int tipo, int filas, int columnas);
    ~plantel();

    string getNombre() const;
    void setNombre(string nombre);
    int getTipo() const;
    void setTipo(int tipo);
    int getCapacidadMax() const;
    matriz* getEspacios() const;
    int getFilas() const;
    int getColumnas() const;

    bool ocuparEspacio(int fila, int col, string placaVehiculo);
    bool desocuparEspacio(int fila, int col);
    espacioEstacionamiento* obtenerEspacio(int fila, int col) const;

    int contarEspaciosLibres() const;
    double calcularPorcentajeOcupacion() const;

    // NUEVOS MÉTODOS REQUERIDOS
    vector<string> recomendarEspacios() const;
    bool asignarEspacioManual(string codigoEspacio, string placaVehiculo);
    bool liberarEspacio(string codigoEspacio);
    string getVehiculo(string codigoEspacio) const;

    string obtenerCodigoEspacio(int fila, int col) const;
    string mostrarGrafico() const;
    string toString() const;
};