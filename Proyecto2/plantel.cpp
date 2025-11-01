#include "plantel.h"

plantel::plantel() {
    letra = 'A';
    capacidad = 0;
    tipo = 1;
    filas = 0;
    columnas = 0;
    espacios = nullptr;
    espaciosOcupados = 0;
}

plantel::plantel(char letra, int capacidad, int tipo, int filas, int columnas) {
    this->letra = letra;
    this->capacidad = capacidad;
    this->tipo = tipo;
    this->filas = filas;
    this->columnas = columnas;
    this->espaciosOcupados = 0;

    espacios = new matriz(filas, columnas);

    // Inicializar todos los espacios
    int contador = 0;
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if (contador < capacidad) {
                stringstream ss;
                ss << letra;
                if (contador < 10) ss << "0";
                ss << contador;

                espacioEstacionamiento* espacio = new espacioEstacionamiento(ss.str(), false);
                espacios->setValor(i, j, espacio);
                contador++;
            }
            else {
                espacios->setValor(i, j, nullptr);
            }
        }
    }
}

plantel::~plantel() {
    if (espacios != nullptr) {
        for (int i = 0; i < filas; i++) {
            for (int j = 0; j < columnas; j++) {
                espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
                if (espacio != nullptr) {
                    delete espacio;
                }
            }
        }
        delete espacios;
    }
}

char plantel::getLetra() const { return letra; }
int plantel::getCapacidad() const { return capacidad; }
int plantel::getTipo() const { return tipo; }
int plantel::getFilas() const { return filas; }
int plantel::getColumnas() const { return columnas; }
int plantel::getEspaciosOcupados() const { return espaciosOcupados; }
int plantel::getEspaciosDisponibles() const { return capacidad - espaciosOcupados; }

void plantel::setLetra(char letra) { this->letra = letra; }
void plantel::setCapacidad(int capacidad) { this->capacidad = capacidad; }
void plantel::setTipo(int tipo) { this->tipo = tipo; }

string plantel::obtenerTipoTexto() const {
    switch (tipo) {
    case 1: return "Techado y asfaltado";
    case 2: return "Techado y lastreado";
    case 3: return "Asfaltado";
    case 4: return "Lastreado";
    default: return "Desconocido";
    }
}

bool plantel::asignarVehiculo(int fila, int columna, vehiculo* v) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return false;
    }

    espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(fila, columna);

    if (espacio == nullptr || espacio->estaOcupado()) {
        return false;
    }

    espacio->ocupar();
    espacio->setPlacaVehiculo(v->getPlaca());
    espaciosOcupados++;

    stringstream ubicacion;
    ubicacion << letra << "-" << fila << "-" << columna;
    v->setUbicacionPlantel(ubicacion.str());

    return true;
}

bool plantel::liberarEspacio(int fila, int columna) {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return false;
    }

    espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(fila, columna);

    if (espacio == nullptr || !espacio->estaOcupado()) {
        return false;
    }

    espacio->desocupar();
    espacio->setPlacaVehiculo("");
    espaciosOcupados--;
    return true;
}

espacioEstacionamiento* plantel::obtenerEspacio(int fila, int columna) const {
    if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas) {
        return nullptr;
    }
    return (espacioEstacionamiento*)espacios->getValor(fila, columna);
}

espacioEstacionamiento* plantel::buscarEspacioPorCodigo(const string codigo) const {
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && espacio->getCodigo() == codigo) {
                return espacio;
            }
        }
    }
    return nullptr;
}

string plantel::obtenerPlacaEnEspacio(const string codigo) const {
    espacioEstacionamiento* espacio = buscarEspacioPorCodigo(codigo);

    if (espacio != nullptr) {
        if (espacio->estaOcupado()) {
            return "Placa del vehiculo: " + espacio->getPlacaVehiculo();
        }
        else {
            return "El espacio esta vacio";
        }
    }

    return "Espacio no encontrado";
}

int plantel::contarVecinosOcupados(int f, int c) const {
    int count = 0;

    // Verificar los 8 vecinos (arriba, abajo, izquierda, derecha y diagonales)
    for (int i = f - 1; i <= f + 1; i++) {
        for (int j = c - 1; j <= c + 1; j++) {
            if (i == f && j == c) continue; // Saltar la posición actual
            if (i >= 0 && i < filas && j >= 0 && j < columnas) {
                espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
                if (espacio != nullptr && espacio->estaOcupado()) {
                    count++;
                }
            }
        }
    }
    return count;
}

listaBase<string>* plantel::recomendarEspacios() const {
    listaBase<string>* recomendaciones = new listaBase<string>();

    // Estructura auxiliar para trabajar con espacios
    struct EspacioScore {
        string codigo;
        int fila;
        int columna;
        int vecinos;
    };

    // Lista para almacenar espacios libres con su score
    listaBase<EspacioScore>* espaciosLibres = new listaBase<EspacioScore>();

    // Buscar todos los espacios libres y contar vecinos
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr && !espacio->estaOcupado()) {
                EspacioScore* score = new EspacioScore();
                score->codigo = espacio->getCodigo();
                score->fila = i;
                score->columna = j;
                score->vecinos = contarVecinosOcupados(i, j);
                espaciosLibres->agregarFinal(score);
            }
        }
    }

    // Ordenar por menor cantidad de vecinos (bubble sort)
    if (!espaciosLibres->estaVacia()) {
        nodoBase<EspacioScore>* actual = espaciosLibres->retornarPrimero();

        while (actual != nullptr) {
            nodoBase<EspacioScore>* siguiente = actual->getSiguiente();

            while (siguiente != nullptr) {
                if (siguiente->getElemento()->vecinos < actual->getElemento()->vecinos) {
                    // Intercambiar elementos
                    EspacioScore temp = *(actual->getElemento());
                    *(actual->getElemento()) = *(siguiente->getElemento());
                    *(siguiente->getElemento()) = temp;
                }
                siguiente = siguiente->getSiguiente();
            }
            actual = actual->getSiguiente();
        }
    }

    // Retornar los 3 mejores (o menos si no hay suficientes)
    int contador = 0;
    int limite = 3;
    nodoBase<EspacioScore>* actual = espaciosLibres->retornarPrimero();

    while (actual != nullptr && contador < limite) {
        string* codigoStr = new string(actual->getElemento()->codigo);
        recomendaciones->agregarFinal(codigoStr);
        contador++;
        actual = actual->getSiguiente();
    }

    delete espaciosLibres;
    return recomendaciones;
}

string plantel::mostrarVistaGrafica() const {
    stringstream s;
    s << "\n====== PLANTEL " << letra << " ======\n";
    s << "Tipo: " << obtenerTipoTexto() << "\n";
    s << "Capacidad: " << capacidad << " espacios\n";
    s << "Ocupados: " << espaciosOcupados << " | Disponibles: " << getEspaciosDisponibles() << "\n\n";

    // Encabezado de columnas
    s << "     ";
    for (int j = 0; j < columnas; j++) {
        s << "Col" << j << "  ";
    }
    s << "\n";

    for (int i = 0; i < filas; i++) {
        s << "F" << i << "   ";
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio == nullptr) {
                s << "[---] ";
            }
            else if (espacio->estaOcupado()) {
                s << "[XXX] ";
            }
            else {
                s << "[ O ] ";
            }
        }
        s << "\n";
    }

    s << "\nLeyenda: [ O ] = Disponible | [XXX] = Ocupado | [---] = No existe\n";
    return s.str();
}

string plantel::mostrarDetalle() const {
    stringstream s;
    s << "\n====== DETALLE PLANTEL " << letra << " ======\n\n";

    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            espacioEstacionamiento* espacio = (espacioEstacionamiento*)espacios->getValor(i, j);
            if (espacio != nullptr) {
                s << espacio->toString();
                if (espacio->estaOcupado()) {
                    s << " - Placa: " << espacio->getPlacaVehiculo();
                }
                s << "\n";
            }
        }
    }
    return s.str();
}

string plantel::toString() const {
    stringstream s;
    s << "Plantel " << letra << " - ";
    s << "Tipo: " << obtenerTipoTexto() << " - ";
    s << "Capacidad: " << capacidad << " - ";
    s << "Ocupacion: " << espaciosOcupados << "/" << capacidad;
    return s.str();
}

double plantel::getPorcentajeOcupacion() const {
    if (capacidad == 0) return 0.0;
    return (static_cast<double>(espaciosOcupados) / capacidad) * 100.0;
}

bool plantel::estaLleno() const {
    return espaciosOcupados >= capacidad;
}