#include "contratoAlquiler.h"

contratoAlquiler::contratoAlquiler(): solicitudAlquiler(), estadoContrato("pendiente"), diasRealesUso(0) {
}

contratoAlquiler::contratoAlquiler(const solicitudAlquiler& s)
    : solicitudAlquiler(s), estadoContrato("aprobado pendiente de ejecución"), diasRealesUso(0) {
}

void contratoAlquiler::finalizarContrato(int diasUtilizados) {
    diasRealesUso = diasUtilizados;

    if (diasRealesUso == dias)
        estadoContrato = "finalizado sin cargos adicionales";
    else if (diasRealesUso < dias)
        estadoContrato = "finalizado con reintegro";
    else
        estadoContrato = "finalizado con multa";
}

void contratoAlquiler::mostrarInfo() const {
    std::cout << "Contrato (Solicitud #" << getIdSolicitud()
        << ") - Estado: " << estadoContrato
        << ", Días usados: " << diasRealesUso << std::endl;
}