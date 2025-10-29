#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "matriz.h"
#include "espacioEstacionamiento.h"
#include "vehiculo.h"

using namespace std;

class plantel {
private:
    char letra;
    int capacidad;
    int tipo; // 1: Techado y asfaltado, 2: Techado y lastreado, 3: Asfaltado, 4: Lastreado
    int filas;
    int columnas;
    matriz* espacios;
    int espaciosOcupados;

    string obtenerTipoTexto() const;
    int contarVecinosOcupados(int f, int c) const;

public:
    plantel();
    plantel(char letra, int capacidad, int tipo, int filas, int columnas);
    ~plantel();

    char getLetra() const;
    int getCapacidad() const;
    int getTipo() const;
    int getFilas() const;
    int getColumnas() const;
    int getEspaciosOcupados() const;
    int getEspaciosDisponibles() const;

    void setLetra(char letra);
    void setCapacidad(int capacidad);
    void setTipo(int tipo);

    // Gestión de espacios
    bool asignarVehiculo(int fila, int columna, vehiculo* v);
    bool liberarEspacio(int fila, int columna);
    espacioEstacionamiento* obtenerEspacio(int fila, int columna) const;
    espacioEstacionamiento* buscarEspacioPorCodigo(const string& codigo) const;
    string obtenerPlacaEnEspacio(const string& codigo) const;

    // Recomendación de espacios
    vector<string> recomendarEspacios() const;

    // Visualización
    string mostrarVistaGrafica() const;
    string mostrarDetalle() const;
    string toString() const;

    // Utilidades
    double getPorcentajeOcupacion() const;
    bool estaLleno() const;
};