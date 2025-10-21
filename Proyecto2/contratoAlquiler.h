#include <string>
#include <iostream>
#include "solicitudAlquiler.h"

class contratoAlquiler : public solicitudAlquiler {
private:
    string estadoContrato;
    int diasRealesUso;

public:
    contratoAlquiler();
    contratoAlquiler(const solicitudAlquiler& solicitudAprobada);

    void finalizarContrato(int diasUtilizados);
    void mostrarInfo() const;
};