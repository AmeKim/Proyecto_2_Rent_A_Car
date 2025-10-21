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
    colaborador* colaborador, vehiculo* vehiculo, int d, const string& fInicio,
    const string& fEntrega, double pDia) {
    codigo = cod;
    cli = cliente;
    col = colaborador;
    veh = vehiculo;
    dias = d;
    fechaInicio = fInicio;
    fechaEntrega = fEntrega;
    precioDia = pDia;
    precioTotal = pDia * d;
    estado = "Pendiente";
}

string solicitudAlquiler::getCodigo() const {
    return codigo;
}

string solicitudAlquiler::getEstado() const {
    return estado;
}

double solicitudAlquiler::getPrecioTotal() const {
    return precioTotal;
}

int solicitudAlquiler::getDias() const {
    return dias;
}

string solicitudAlquiler::getFechaInicio() const {
    return fechaInicio;
}

string solicitudAlquiler::getFechaEntrega() const {
    return fechaEntrega;
}

double solicitudAlquiler::getPrecioDia() const {
    return precioDia;
}

cliente* solicitudAlquiler::getCliente() const {
    return cli;
}

colaborador* solicitudAlquiler::getColaborador() const {
    return col;
}

vehiculo* solicitudAlquiler::getVehiculo() const {
    return veh;
}

void solicitudAlquiler::aprobar() {
    estado = "Aprobada";
}

void solicitudAlquiler::rechazar() {
    estado = "Rechazada";
}

void solicitudAlquiler::anular() {
    estado = "Anulada";
}

void solicitudAlquiler::mostrarInfo() const {
    cout << "========================================" << endl;
    cout << "        SOLICITUD DE ALQUILER" << endl;
    cout << "========================================" << endl;
    cout << "Código: " << codigo << endl;
    cout << "Cliente: " << (cli ? cli->getNombre() : "N/A") << endl;
    cout << "  ID: " << (cli ? cli->getCedula() : "N/A") << endl;
    cout << "Colaborador: " << (col ? col->getNombre() : "N/A") << endl;
    cout << "Vehículo: " << (veh ? veh->getPlaca() : "N/A") << endl;
    cout << "Días de alquiler: " << dias << endl;
    cout << "Fecha inicio: " << fechaInicio << endl;
    cout << "Fecha entrega: " << fechaEntrega << endl;
    cout << "Precio por día: $" << precioDia << endl;
    cout << "Precio total: $" << precioTotal << endl;
    cout << "Estado: " << estado << endl;
    cout << "========================================" << endl;
}

string solicitudAlquiler::toString() const {
    stringstream ss;
    ss << "Solicitud " << codigo << " - Estado: " << estado
        << " - Cliente: " << (cli ? cli->getNombre() : "N/A");
    return ss.str();
}