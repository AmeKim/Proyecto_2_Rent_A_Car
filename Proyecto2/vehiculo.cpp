#include "vehiculo.h"

vehiculo::vehiculo() {
    placa = "";
    modelo = "";
    marca = "";
    tipoLicencia = "";
    precio = 0.0;
    estado = "Disponible";
    categoria = 'A';
    ubicacionPlantel = "";
    bitacora = new listaBase<registroBitacora>();
}

vehiculo::vehiculo(string placa, string modelo, string marca, string tipoLicencia,
    double precio, string estado, char categoria, string ubicacionPlantel) {
    this->placa = placa;
    this->modelo = modelo;
    this->marca = marca;
    this->tipoLicencia = tipoLicencia;
    this->precio = precio;
    this->estado = estado;
    this->categoria = categoria;
    this->ubicacionPlantel = ubicacionPlantel;
    bitacora = new listaBase<registroBitacora>();
}

vehiculo::~vehiculo() {
    delete bitacora;
}

string vehiculo::getPlaca() const { return placa; }
void vehiculo::setPlaca(string placa) { this->placa = placa; }

string vehiculo::getModelo() const { return modelo; }
void vehiculo::setModelo(string modelo) { this->modelo = modelo; }

string vehiculo::getMarca() const { return marca; }
void vehiculo::setMarca(string marca) { this->marca = marca; }

string vehiculo::getTipoLicencia() const { return tipoLicencia; }
void vehiculo::setTipoLicencia(string tipoLicencia) { this->tipoLicencia = tipoLicencia; }

double vehiculo::getPrecio() const { return precio; }
void vehiculo::setPrecio(double precio) { this->precio = precio; }

string vehiculo::getEstado() const { return estado; }
void vehiculo::setEstado(string estado) { this->estado = estado; }

char vehiculo::getCategoria() const { return categoria; }
void vehiculo::setCategoria(char categoria) { this->categoria = categoria; }

string vehiculo::getUbicacionPlantel() const { return ubicacionPlantel; }
void vehiculo::setUbicacionPlantel(string ubicacionPlantel) { this->ubicacionPlantel = ubicacionPlantel; }

bool vehiculo::cambiarEstado(string nuevoEstado, string fecha, colaborador* responsable) {
    // Validar transiciones válidas según la tabla del documento
    bool transicionValida = false;

    if (estado == "Disponible") {
        if (nuevoEstado == "Alquilado" || nuevoEstado == "Revision" || nuevoEstado == "Lavado") {
            transicionValida = true;
        }
    }
    else if (estado == "Alquilado") {
        if (nuevoEstado == "Devuelto") {
            transicionValida = true;
        }
    }
    else if (estado == "Devuelto") {
        if (nuevoEstado == "Revision" || nuevoEstado == "Lavado") {
            transicionValida = true;
        }
    }
    else if (estado == "Revision") {
        if (nuevoEstado == "Lavado") {
            transicionValida = true;
        }
    }
    else if (estado == "Lavado") {
        if (nuevoEstado == "Disponible" || nuevoEstado == "Revision") {
            transicionValida = true;
        }
    }

    if (!transicionValida) {
        return false;
    }

    // Registrar en bitácora
    registroBitacora* registro = new registroBitacora(estado, nuevoEstado, fecha, responsable);
    bitacora->agregarFinal(registro);

    // Cambiar el estado
    estado = nuevoEstado;

    return true;
}

string vehiculo::mostrarBitacora() const {
    stringstream s;
    s << "\n===== BITACORA DE ESTADOS - VEHICULO " << placa << " =====\n\n";

    if (bitacora->estaVacia()) {
        s << "No hay registros en la bitacora.\n";
        return s.str();
    }

    s << bitacora->toStringLista();
    return s.str();
}

string vehiculo::toString() const {
    stringstream s;
    s << "Placa: " << placa << " | ";
    s << "Marca: " << marca << " | ";
    s << "Modelo: " << modelo << " | ";
    s << "Categoria: " << categoria << " | ";
    s << "Estado: " << estado << " | ";
    s << "Precio/dia: $" << precio << " | ";
    s << "Plantel: " << ubicacionPlantel;
    return s.str();
}