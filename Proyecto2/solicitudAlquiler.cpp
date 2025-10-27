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

solicitudAlquiler::solicitudAlquiler(const string& cod, cliente* cliente,
    colaborador* colaborador, vehiculo* vehiculo,
    int dias, const string& fInicio,
    const string& fEntrega, double pDia) {
    this->codigo = cod;
    this->cli = cliente;
    this->col = colaborador;
    this->veh = vehiculo;
    this->dias = dias;
    this->fechaInicio = fInicio;
    this->fechaEntrega = fEntrega;
    this->precioDia = pDia;

    // Aplicar descuento si es persona jurídica
    personaJuridica* pj = dynamic_cast<personaJuridica*>(cliente);
    if (pj != nullptr) {
        double descuento = pj->getPorcDescuento() / 100.0;
        this->precioTotal = pDia * dias * (1.0 - descuento);
    }
    else {
        this->precioTotal = pDia * dias;
    }

    this->estado = "Pendiente";
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
    s << "===== Solicitud de Alquiler =====\n";
    s << "Codigo: " << codigo << endl;
    s << "Cliente: " << (cli ? cli->getNombre() : "N/A") << " (ID: "
        << (cli ? cli->getCedula() : "N/A") << ")" << endl;
    s << "Colaborador: " << (col ? col->getNombre() : "N/A") << endl;
    s << "Vehiculo: " << (veh ? veh->getPlaca() : "N/A") << endl;
    s << "Dias: " << dias << endl;
    s << "Fecha Inicio: " << fechaInicio << endl;
    s << "Fecha Entrega: " << fechaEntrega << endl;
    s << "Precio por Dia: " << precioDia << endl;
    s << "Precio Total: " << precioTotal << endl;
    s << "Estado: " << estado << endl;
    return s.str();
}