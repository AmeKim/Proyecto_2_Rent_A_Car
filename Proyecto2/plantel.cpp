#include "plantel.h"

plantel::plantel() {
    nombre = "";
    tipo = 0;
    capacidadMax = 0;
    filas = 0;
    columnas = 0;
    espacios = nullptr;
}

plantel::plantel(string nombre, int tipo, int filas, int columnas) {
    this->nombre = nombre;
    this->tipo = tipo;
    this->filas = filas;
    this->columnas = columnas;
    this->capacidadMax = filas * columnas;

    // Crear matriz de espacios
    espacios = new matriz(filas, columnas);

    // Inicializar cada espacio
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            string codigo = obtenerCodigoEspacio(i, j);
            espacioEstacionamiento* espacio = new espacioEstacionamiento(codigo, false);
            espacios->setValor(i, j, espacio);
        }
    }
}

plantel::~plantel() {
    if (espacios != nullptr) {
        // Liberar cada espacio
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
                delete espacio;
            }
        }
        delete espacios;
    }
}

string plantel::getNombre() const { return nombre; }
void plantel::setNombre(string nombre) { this->nombre = nombre; }

int plantel::getTipo() const { return tipo; }
void plantel::setTipo(int tipo) { this->tipo = tipo; }

int plantel::getCapacidadMax() const { return capacidadMax; }

matriz* plantel::getEspacios() const { return espacios; }

int plantel::getFilas() const { return filas; }
int plantel::getColumnas() const { return columnas; }

bool plantel::ocuparEspacio(int fila, int col, string placaVehiculo) {
    if (fila < 0 || fila >= filas || col < 0 || col >= columnas) {
        return false;
    }

    espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(fila, col);
    if (espacio == nullptr || espacio->estaOcupado()) {
        return false;
    }

    espacio->ocupar();
    return true;
}

bool plantel::desocuparEspacio(int fila, int col) {
    if (fila < 0 || fila >= filas || col < 0 || col >= columnas) {
        return false;
    }

    espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(fila, col);
    if (espacio == nullptr || !espacio->estaOcupado()) {
        return false;
    }

    espacio->desocupar();
    return true;
}

espacioEstacionamiento* plantel::obtenerEspacio(int fila, int col) const {
    if (fila < 0 || fila >= filas || col < 0 || col >= columnas) {
        return nullptr;
    }
    return (espacioEstacionamiento*)espacios->getValor(fila, col);
}

int plantel::contarEspaciosLibres() const {
    int contador = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && !espacio->estaOcupado()) {
                contador++;
            }
        }
    }
    return contador;
}

double plantel::calcularPorcentajeOcupacion() const {
    int ocupados = capacidadMax - contarEspaciosLibres();
    return (double)ocupados / capacidadMax * 100.0;
}

string plantel::obtenerCodigoEspacio(int fila, int col) const {
    stringstream ss;
    ss << nombre;

    // Formato: A00, A01, etc.
    if (fila < 10) ss << "0";
    ss << fila;

    if (col < 10) ss << "0";
    ss << col;

    return ss.str();
}

string plantel::mostrarGrafico() const {
    stringstream s;
    s << "\n===== Plantel " << nombre << " =====\n";
    s << "Tipo: ";
    switch (tipo) {
    case 1: s << "Techado y asfaltado\n"; break;
    case 2: s << "Techado y lastreado\n"; break;
    case 3: s << "Asfaltado\n"; break;
    case 4: s << "Lastreado\n"; break;
    default: s << "Desconocido\n";
    }
    s << "Capacidad: " << capacidadMax << " espacios\n";
    s << "Distribucion:\n\n";

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr) {
                if (espacio->estaOcupado()) {
                    s << "[X] ";  // Ocupado
                }
                else {
                    s << "[ ] ";  // Libre
                }
            }
        }
        s << "\n";
    }

    s << "\nEspacios libres: " << contarEspaciosLibres() << "/" << capacidadMax;
    s << " (" << calcularPorcentajeOcupacion() << "% ocupacion)\n";

    return s.str();
}

string plantel::toString() const {
    stringstream s;
    s << "Plantel " << nombre << " - Tipo: " << tipo;
    s << " - Capacidad: " << capacidadMax;
    s << " (" << filas << "x" << columnas << ")";
    return s.str();
}