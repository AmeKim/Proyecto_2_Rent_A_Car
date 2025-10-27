#include "contratoAlquiler.h"

contratoAlquiler::contratoAlquiler() : solicitudAlquiler() {
    estadoContrato = "Aprobado pendiente de ejecucion";
    diasRealesUso = 0;
}

contratoAlquiler::contratoAlquiler(const solicitudAlquiler& solicitudAprobada) {
    this->codigo = solicitudAprobada.getCodigo();
    this->cli = solicitudAprobada.getCliente();
    this->col = solicitudAprobada.getColaborador();
    this->veh = solicitudAprobada.getVehiculo();
    this->dias = solicitudAprobada.getDias();
    this->fechaInicio = solicitudAprobada.getFechaInicio();
    this->fechaEntrega = solicitudAprobada.getFechaEntrega();
    this->precioDia = solicitudAprobada.getPrecioDia();
    this->precioTotal = solicitudAprobada.getPrecioTotal();
    this->estado = "Aprobada";
    this->estadoContrato = "Aprobado pendiente de ejecucion";
    this->diasRealesUso = 0;
}

string contratoAlquiler::getEstadoContrato() const {
    return estadoContrato;
}

int contratoAlquiler::getDiasRealesUso() const {
    return diasRealesUso;
}

void contratoAlquiler::finalizarContrato(int diasUtilizados) {
    diasRealesUso = diasUtilizados;

    if (diasUtilizados < dias) {
        // Devolución anticipada: reintegro del 70%
        int diasNoUsados = dias - diasUtilizados;
        double reintegro = diasNoUsados * precioDia * 0.70;
        precioTotal = precioTotal - reintegro;
        estadoContrato = "Finalizado con reintegro";
    }
    else if (diasUtilizados > dias) {
        // Devolución tardía: multa del 130%
        int diasAtraso = diasUtilizados - dias;
        double multa = diasAtraso * precioDia * 1.30;
        precioTotal = precioTotal + multa;
        estadoContrato = "Finalizado con multa";
    }
    else {
        // Devolución a tiempo
        estadoContrato = "Finalizado sin cargos adicionales";
    }
}

double contratoAlquiler::calcularMontoFinal() const {
    return precioTotal;
}

string contratoAlquiler::toString() const {
    stringstream s;
    s << "===== Contrato de Alquiler =====\n";
    s << "Codigo: " << codigo << endl;
    s << "Cliente: " << (cli ? cli->getNombre() : "N/A") << " (ID: "
        << (cli ? cli->getCedula() : "N/A") << ")" << endl;
    s << "Colaborador: " << (col ? col->getNombre() : "N/A") << endl;
    s << "Vehiculo: " << (veh ? veh->getPlaca() : "N/A") << endl;
    s << "Dias Contratados: " << dias << endl;
    s << "Dias Reales de Uso: " << diasRealesUso << endl;
    s << "Fecha Inicio: " << fechaInicio << endl;
    s << "Fecha Entrega: " << fechaEntrega << endl;
    s << "Precio por Dia: " << precioDia << endl;
    s << "Precio Total Final: " << precioTotal << endl;
    s << "Estado Contrato: " << estadoContrato << endl;
    return s.str();
}