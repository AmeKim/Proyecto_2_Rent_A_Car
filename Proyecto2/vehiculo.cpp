#include "vehiculo.h"

vehiculo::vehiculo() {
    placa = "";
    modelo = "";
    marca = "";
    tipoLicencia = "";
    precio = 0.0;
    estado = "Revision";  // Estado inicial según el proyecto
    categoria = ' ';
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
void vehiculo::setUbicacionPlantel(string ubicacionPlantel) {
    this->ubicacionPlantel = ubicacionPlantel;
}

bool vehiculo::cambiarEstado(string nuevoEstado, string fecha, colaborador* responsable) {
    // Validar transiciones según la tabla del proyecto
    if (estado == "Disponible") {
        if (nuevoEstado != "Alquilado" && nuevoEstado != "Revision" && nuevoEstado != "Lavado") {
            return false;
        }
    }
    else if (estado == "Alquilado") {
        if (nuevoEstado != "Devuelto") {
            return false;
        }
    }
    else if (estado == "Devuelto") {
        if (nuevoEstado != "Revision" && nuevoEstado != "Lavado") {
            return false;
        }
    }
    else if (estado == "Revision") {
        if (nuevoEstado != "Lavado") {
            return false;
        }
    }
    else if (estado == "Lavado") {
        if (nuevoEstado != "Disponible" && nuevoEstado != "Revision") {
            return false;
        }
    }

    // Registrar en bitácora
    registroBitacora* registro = new registroBitacora(estado, nuevoEstado, fecha, responsable);
    bitacora->agregarFinal(registro);

    estado = nuevoEstado;
    return true;
}

string vehiculo::mostrarBitacora() const {
    if (bitacora->estaVacia()) {
        return "No hay registros en la bitacora.\n";
    }
    return bitacora->toStringLista();
}

string vehiculo::toString() const {
    stringstream s;
    s << "===== Vehiculo =====\n";
    s << "Placa: " << placa << endl;
    s << "Modelo: " << modelo << endl;
    s << "Marca: " << marca << endl;
    s << "Tipo de Licencia: " << tipoLicencia << endl;
    s << "Precio: " << precio << endl;
    s << "Estado: " << estado << endl;
    s << "Categoria: " << categoria << endl;
    s << "Ubicacion en Plantel: " << ubicacionPlantel << endl;
    return s.str();
}