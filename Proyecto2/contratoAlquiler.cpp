#include "contratoAlquiler.h"

contratoAlquiler::contratoAlquiler() : solicitudAlquiler() {
    estadoContrato = "Aprobado pendiente de ejecucion";
    diasRealesUso = 0;
}

contratoAlquiler::contratoAlquiler(const solicitudAlquiler& solicitudAprobada)
    : solicitudAlquiler(solicitudAprobada) {
    estadoContrato = "Aprobado en alquiler";
    diasRealesUso = 0;
    estado = "Aprobada";
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
        // Entrega anticipada - reintegro del 70%
        estadoContrato = "Finalizado con reintegro";
    }
    else if (diasUtilizados > dias) {
        // Entrega tardía - multa del 130%
        estadoContrato = "Finalizado con multa";
    }
    else {
        // Entrega a tiempo
        estadoContrato = "Finalizado sin cargos adicionales";
    }
}

double contratoAlquiler::calcularMontoFinal() const {
    if (estadoContrato == "Finalizado con reintegro") {
        // Reintegro del 70% por días no utilizados
        int diasNoUtilizados = dias - diasRealesUso;
        double reintegro = diasNoUtilizados * precioDia * 0.70;
        return precioTotal - reintegro;
    }
    else if (estadoContrato == "Finalizado con multa") {
        // Multa del 130% por días de atraso
        int diasAtraso = diasRealesUso - dias;
        double multa = diasAtraso * precioDia * 1.30;
        return precioTotal + multa;
    }
    return precioTotal;
}

string contratoAlquiler::toString() const {
    stringstream s;
    s << "\n===== CONTRATO DE ALQUILER =====\n";
    s << "Codigo: " << codigo << endl;
    s << "Estado del Contrato: " << estadoContrato << endl;
    s << "Cliente: " << (cli ? cli->getNombre() : "N/A") << " (ID: " << (cli ? cli->getCedula() : "N/A") << ")\n";
    s << "Colaborador: " << (col ? col->getNombre() : "N/A") << endl;
    s << "Vehiculo: " << (veh ? veh->getPlaca() : "N/A") << endl;
    s << "Dias contratados: " << dias << endl;

    if (diasRealesUso > 0) {
        s << "Dias reales de uso: " << diasRealesUso << endl;
    }

    s << "Fecha de inicio: " << fechaInicio << endl;
    s << "Fecha de entrega programada: " << fechaEntrega << endl;
    s << "Precio por dia: $" << precioDia << endl;
    s << "Precio total inicial: $" << precioTotal << endl;

    if (estadoContrato.find("Finalizado") != string::npos) {
        s << "Monto final: $" << calcularMontoFinal() << endl;
    }

    return s.str();
}