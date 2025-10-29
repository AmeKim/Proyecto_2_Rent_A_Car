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
    espacio->setPlacaVehiculo(placaVehiculo);
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
    espacio->setPlacaVehiculo("");
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

// IMPLEMENTACIÓN DE NUEVOS MÉTODOS

vector<string> plantel::recomendarEspacios() const {
    vector<string> recomendaciones;

    // Contar vehículos alrededor de cada espacio disponible
    struct EspacioScore {
        string codigo;
        int fila;
        int col;
        int vecinosOcupados;
    };

    vector<EspacioScore> espaciosDisponibles;

    // Analizar cada espacio
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && !espacio->estaOcupado()) {
                // Contar vecinos ocupados (arriba, abajo, izquierda, derecha)
                int vecinos = 0;

                // Arriba
                if (i > 0) {
                    espacioEstacionamiento* arriba = (espacioEstacionamiento*)espacios->getValor(i - 1, j);
                    if (arriba && arriba->estaOcupado()) vecinos++;
                }
                // Abajo
                if (i < filas - 1) {
                    espacioEstacionamiento* abajo = (espacioEstacionamiento*)espacios->getValor(i + 1, j);
                    if (abajo && abajo->estaOcupado()) vecinos++;
                }
                // Izquierda
                if (j > 0) {
                    espacioEstacionamiento* izq = (espacioEstacionamiento*)espacios->getValor(i, j - 1);
                    if (izq && izq->estaOcupado()) vecinos++;
                }
                // Derecha
                if (j < columnas - 1) {
                    espacioEstacionamiento* der = (espacioEstacionamiento*)espacios->getValor(i, j + 1);
                    if (der && der->estaOcupado()) vecinos++;
                }

                EspacioScore score;
                score.codigo = espacio->getCodigo();
                score.fila = i;
                score.col = j;
                score.vecinosOcupados = vecinos;
                espaciosDisponibles.push_back(score);
            }
        }
    }

    // Ordenar por menor cantidad de vecinos ocupados
    for (size_t i = 0; i < espaciosDisponibles.size(); i++) {
        for (size_t j = i + 1; j < espaciosDisponibles.size(); j++) {
            if (espaciosDisponibles[j].vecinosOcupados < espaciosDisponibles[i].vecinosOcupados) {
                EspacioScore temp = espaciosDisponibles[i];
                espaciosDisponibles[i] = espaciosDisponibles[j];
                espaciosDisponibles[j] = temp;
            }
        }
    }

    // Retornar los 3 mejores (o menos si no hay suficientes)
    int maxRecomendaciones = 3;
    for (size_t i = 0; i < espaciosDisponibles.size() && i < maxRecomendaciones; i++) {
        recomendaciones.push_back(espaciosDisponibles[i].codigo);
    }

    return recomendaciones;
}

bool plantel::asignarEspacioManual(string codigoEspacio, string placaVehiculo) {
    // Buscar el espacio por código
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && espacio->getCodigo() == codigoEspacio) {
                if (espacio->estaOcupado()) {
                    return false; // Ya está ocupado
                }
                espacio->ocupar();
                espacio->setPlacaVehiculo(placaVehiculo);
                return true;
            }
        }
    }
    return false; // No se encontró el espacio
}

bool plantel::liberarEspacio(string codigoEspacio) {
    // Buscar el espacio por código
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && espacio->getCodigo() == codigoEspacio) {
                if (!espacio->estaOcupado()) {
                    return false; // Ya está libre
                }
                espacio->desocupar();
                espacio->setPlacaVehiculo("");
                return true;
            }
        }
    }
    return false; // No se encontró el espacio
}

string plantel::getVehiculo(string codigoEspacio) const {
    // Buscar el espacio por código y retornar la placa del vehículo
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && espacio->getCodigo() == codigoEspacio) {
                return espacio->getPlacaVehiculo();
            }
        }
    }
    return ""; // No se encontró el espacio
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