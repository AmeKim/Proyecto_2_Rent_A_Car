#include "contratoAlquiler.h"

contratoAlquiler::contratoAlquiler() : solicitudAlquiler() {
    estadoContrato = "Aprobado pendiente de ejecución";
    diasRealesUso = 0;
}

contratoAlquiler::contratoAlquiler(const solicitudAlquiler* solicitudAprobada)
	: solicitudAlquiler(*solicitudAprobada) {
    estadoContrato = "Aprobado en alquiler";
    diasRealesUso = 0;
}

string contratoAlquiler::getEstadoContrato() const {
    return estadoContrato;
}

int contratoAlquiler::getDiasRealesUso() const {
    return diasRealesUso;
}

void contratoAlquiler::finalizarContrato(int diasUtilizados) {
    diasRealesUso = diasUtilizados;
    int diasContratados = getDias();

    if (diasUtilizados < diasContratados) {
        estadoContrato = "Finalizado con reintegro";
    }
    else if (diasUtilizados > diasContratados) {
        estadoContrato = "Finalizado con multa";
    }
    else {
        estadoContrato = "Finalizado sin cargos adicionales";
    }
}

double contratoAlquiler::calcularMontoFinal() const {
    int diasContratados = getDias();
    double precioDia = getPrecioDia();

    if (diasRealesUso < diasContratados) {
        // Devolución anticipada: reintegro del 70% por día no usado
        int diasNoUsados = diasContratados - diasRealesUso;
        double reintegro = diasNoUsados * precioDia * 0.70;
        return (diasRealesUso * precioDia) + reintegro;
    }
    else if (diasRealesUso > diasContratados) {
        // Devolución tardía: multa del 130% por día extra
        int diasExtra = diasRealesUso - diasContratados;
        double multa = diasExtra * precioDia * 1.30;
        return (diasContratados * precioDia) + multa;
    }
    else {
        // Devolución a tiempo
        return getPrecioTotal();
    }
}

void contratoAlquiler::mostrarInfo() const {
    cout << "========================================" << endl;
    cout << "        CONTRATO DE ALQUILER" << endl;
    cout << "========================================" << endl;
    cout << "Código: " << getCodigo() << endl;
    cout << "Cliente: " << (getCliente() ? getCliente()->getNombre() : "N/A") << endl;
    cout << "  ID: " << (getCliente() ? getCliente()->getCedula() : "N/A") << endl;
    cout << "Colaborador: " << (getColaborador() ? getColaborador()->getNombre() : "N/A") << endl;
    cout << "Vehículo: " << (getVehiculo() ? getVehiculo()->getPlaca() : "N/A") << endl;
    cout << "Días contratados: " << getDias() << endl;
    cout << "Días reales de uso: " << diasRealesUso << endl;
    cout << "Fecha inicio: " << getFechaInicio() << endl;
    cout << "Fecha entrega: " << getFechaEntrega() << endl;
    cout << "Precio por día: $" << getPrecioDia() << endl;
    cout << "Precio total original: $" << getPrecioTotal() << endl;

    if (diasRealesUso > 0) {
        cout << "Monto final: $" << calcularMontoFinal() << endl;
    }

    cout << "Estado del contrato: " << estadoContrato << endl;
    cout << "Estado solicitud: " << getEstado() << endl;
    cout << "========================================" << endl;
}

string contratoAlquiler::toString() const {
    stringstream ss;
    ss << "Contrato " << getCodigo() << " - " << estadoContrato
        << " - Cliente: " << (getCliente() ? getCliente()->getNombre() : "N/A");
    return ss.str();
}