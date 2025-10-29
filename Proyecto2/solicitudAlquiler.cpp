#include "solicitudAlquiler.h"

solicitudAlquiler::solicitudAlquiler() {
    codigo = "";
    cli = nullptr;
    col = nullptr;
    veh = nullptr;
    dias = 0;
    fechaInicio = "";
    fechaEntrega = "";
    precioDia = 0.0;
    precioTotal = 0.0;
    estado = "Pendiente";
}

solicitudAlquiler::solicitudAlquiler(const string& cod, cliente* cliente, colaborador* colaborador,
    vehiculo* vehiculo, int dias, const string& fInicio,
    const string& fEntrega, double pDia) {
    this->codigo = cod;
    this->cli = cliente;
    this->col = colaborador;
    this->veh = vehiculo;
    this->dias = dias;
    this->fechaInicio = fInicio;
    this->fechaEntrega = fEntrega;
    this->precioDia = pDia;
    this->estado = "Pendiente";

    // Calcular precio total considerando descuento para personas jurídicas
    precioTotal = precioDia * dias;

    personaJuridica* pj = dynamic_cast<personaJuridica*>(cliente);
    if (pj != nullptr) {
        double descuento = pj->getPorcDescuento() / 100.0;
        precioTotal = precioTotal * (1.0 - descuento);
    }
}

solicitudAlquiler::~solicitudAlquiler() {}

string solicitudAlquiler::getCodigo() const { return codigo; }
string solicitudAlquiler::getEstado() const { return estado; }
double solicitudAlquiler::getPrecioTotal() const { return precioTotal; }
int solicitudAlquiler::getDias() const { return dias; }
string solicitudAlquiler::getFechaInicio() const { return fechaInicio; }
string solicitudAlquiler::getFechaEntrega() const { return fechaEntrega; }
double solicitudAlquiler::getPrecioDia() const { return precioDia; }
cliente* solicitudAlquiler::getCliente() const { return cli; }
colaborador* solicitudAlquiler::getColaborador() const { return col; }
vehiculo* solicitudAlquiler::getVehiculo() const { return veh; }

void solicitudAlquiler::aprobar() {
    estado = "Aprobada";
}

void solicitudAlquiler::rechazar() {
    estado = "Rechazada";
}

void solicitudAlquiler::anular() {
    estado = "Anulada";
}

string solicitudAlquiler::toString() const {
    stringstream s;
    s << "===== SOLICITUD DE ALQUILER =====\n";
    s << "Codigo: " << codigo << "\n";
    s << "Estado: " << estado << "\n";

    if (cli != nullptr) {
        s << "Cliente: " << cli->getNombre() << " (ID: " << cli->getCedula() << ")\n";
    }

    if (veh != nullptr) {
        s << "Vehiculo: " << veh->getPlaca() << " - " << veh->getMarca() << " " << veh->getModelo() << "\n";
    }

    if (col != nullptr) {
        s << "Colaborador: " << col->getNombre() << " (ID: " << col->getCedula() << ")\n";
    }

    s << "Dias de alquiler: " << dias << "\n";
    s << "Fecha inicio: " << fechaInicio << "\n";
    s << "Fecha entrega: " << fechaEntrega << "\n";
    s << "Precio por dia: $" << precioDia << "\n";
    s << "Precio total: $" << precioTotal << "\n";

    return s.str();
}