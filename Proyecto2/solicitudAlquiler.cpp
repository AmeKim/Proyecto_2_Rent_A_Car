#include "solicitudAlquiler.h"

solicitudAlquiler::solicitudAlquiler() {
    codigo = "";
    cliente = nullptr;
    colaborador = nullptr;
    vehiculo = nullptr;
    dias = 0;
    fechaInicio = "";
    fechaEntrega = "";
    precioDia = 0.0;
    precioTotal = 0.0;
    estado = "Pendiente";
}

solicitudAlquiler::solicitudAlquiler(const string& cod, cliente* cli, colaborador* col, vehiculo* veh,
    int d, const string& fInicio, const string& fEntrega, double pDia) {
    codigo = cod;
    cliente = cli;
    colaborador = col;
    vehiculo = veh;
    dias = d;
    fechaInicio = fInicio;
    fechaEntrega = fEntrega;
    precioDia = pDia;
    precioTotal = d * pDia;
    estado = "Pendiente";
}

string solicitudAlquiler::getCodigo() const { return codigo; }
string solicitudAlquiler::getEstado() const { return estado; }
double solicitudAlquiler::getPrecioTotal() const { return precioTotal; }
int solicitudAlquiler::getDias() const { return dias; }

void solicitudAlquiler::aprobar() { estado = "Aprobada"; }
void solicitudAlquiler::rechazar() { estado = "Rechazada"; }
void solicitudAlquiler::anular() { estado = "Anulada"; }

void solicitudAlquiler::mostrarInfo() const {
    cout << "Solicitud #" << codigo << " | Estado: " << estado
        << "\nCliente: " << (cliente ? cliente->getNombre() : "N/A")
        << "\nVehículo: " << (vehiculo ? vehiculo->getPlaca() : "N/A")
        << "\nDías: " << dias
        << "\nPrecio diario: ?" << precioDia
        << "\nTotal: ?" << precioTotal
        << "\nFecha inicio: " << fechaInicio
        << "\nFecha entrega: " << fechaEntrega
        << "\n----------------------------------" << endl;
}

string solicitudAlquiler::toString() const {
    return "Solicitud #" + codigo + " | Estado: " + estado + " | Cliente: " +
        (cliente ? cliente->getNombre() : "N/A") +
        " | Vehículo: " + (vehiculo ? vehiculo->getPlaca() : "N/A");
}
