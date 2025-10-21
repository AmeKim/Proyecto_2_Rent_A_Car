#include <string>
#include "colaborador.h"

using namespace std;

class registroBitacora {
private:
    string estadoAnterior;
    string estadoNuevo;
    string fechaCambio;   // ahora se ingresa manualmente
    colaborador* responsable;

public:
    registroBitacora();
    registroBitacora(const string& anterior, const string& nuevo,const string& fecha, colaborador* colab);

    string getEstadoAnterior() const;
    string getEstadoNuevo() const;
    string getFechaCambio() const;
    colaborador* getResponsable() const;

    void mostrarRegistro() const;
};