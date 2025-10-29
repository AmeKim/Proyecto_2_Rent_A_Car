#include "contratoAlquiler.h"

contratoAlquiler::contratoAlquiler() : solicitudAlquiler() {
    estadoContrato = "Aprobado pendiente de ejecucion";
    diasRealesUso = 0;
}

contratoAlquiler::contratoAlquiler(const solicitudAlquiler& solicitudAprobada)
    : solicitudAlquiler(solicitudAprobada) {
    estadoContrato = "Aprobado en alquiler";
    diasRealesUso = 0;
    estado = "Aprobada"; // Heredado de solicitudAlquiler
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
    if (diasRealesUso == 0) {
        return precioTotal;
    }

    if (diasRealesUso < dias) {
        // Reintegro del 70% por cada día no utilizado
        int diasNoUsados = dias - diasRealesUso;
        double reintegro = diasNoUsados * precioDia * 0.70;
        return precioTotal - reintegro;
    }
    else if (diasRealesUso > dias) {
        // Multa del 130% por cada día de atraso
        int diasAtraso = diasRealesUso - dias;
        double multa = diasAtraso * precioDia * 1.30;
        return precioTotal + multa;
    }

    return precioTotal;
}

string contratoAlquiler::toString() const {
    stringstream s;
    s << "===== CONTRATO DE ALQUILER =====\n";
    s << "Codigo: " << codigo << "\n";
    s << "Estado Contrato: " << estadoContrato << "\n";

    if (cli != nullptr) {
        s << "Cliente: " << cli->getNombre() << " (ID: " << cli->getCedula() << ")\n";
    }

    if (veh != nullptr) {
        s << "Vehiculo: " << veh->getPlaca() << " - " << veh->getMarca() << " " << veh->getModelo() << "\n";
    }

    if (col != nullptr) {
        s << "Colaborador: " << col->getNombre() << " (ID: " << col->getCedula() << ")\n";
    }

    s << "Dias contratados: " << dias << "\n";

    if (diasRealesUso > 0) {
        s << "Dias realmente usados: " << diasRealesUso << "\n";
    }

    s << "Fecha inicio: " << fechaInicio << "\n";
    s << "Fecha entrega programada: " << fechaEntrega << "\n";
    s << "Precio por dia: $" << precioDia << "\n";
    s << "Precio contratado: $" << precioTotal << "\n";

    if (diasRealesUso > 0) {
        s << "Monto final a pagar: $" << calcularMontoFinal() << "\n";

        if (diasRealesUso < dias) {
            s << "Reintegro aplicado (70% por dia no usado)\n";
        }
        else if (diasRealesUso > dias) {
            s << "Multa aplicada (130% por dia de atraso)\n";
        }
    }

    return s.str();
}