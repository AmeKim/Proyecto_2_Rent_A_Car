#include "inventarioVehiculos.h"

inventarioVehiculos::inventarioVehiculos() : listaBase<vehiculo>() {}

inventarioVehiculos::~inventarioVehiculos() {}

void inventarioVehiculos::agregarVehiculo(vehiculo* v) {
    if (v != nullptr) {
        agregarFinal(v);
    }
}

bool inventarioVehiculos::eliminarVehiculoPorPlaca(string placa) {
    if (estaVacia()) {
        return false;
    }

    nodoBase<vehiculo>* actual = primero;
    nodoBase<vehiculo>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getElemento()->getPlaca() == placa) {
            if (anterior == nullptr) {
                primero = actual->getSiguiente();
            }
            else {
                anterior->setSiguiente(actual->getSiguiente());
            }
            delete actual->getElemento();
            delete actual;
            cantidad--;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}

vehiculo* inventarioVehiculos::buscarVehiculoPorPlaca(string placa) {
    nodoBase<vehiculo>* actual = primero;
    while (actual != nullptr) {
        if (actual->getElemento()->getPlaca() == placa) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string inventarioVehiculos::mostrarVehiculos() const {
    if (estaVacia()) {
        return "No hay vehiculos registrados.\n";
    }

    stringstream s;
    s << "\n===== INVENTARIO DE VEHICULOS =====\n\n";
    nodoBase<vehiculo>* actual = primero;
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << endl;
        actual = actual->getSiguiente();
        i++;
    }
    return s.str();
}

string inventarioVehiculos::mostrarVehiculosDisponibles() const {
    stringstream s;
    s << "\n===== VEHICULOS DISPONIBLES =====\n\n";

    nodoBase<vehiculo>* actual = primero;
    int i = 1;
    bool hayDisponibles = false;

    while (actual != nullptr) {
        if (actual->getElemento()->getEstado() == "Disponible") {
            s << i << ". " << actual->getElemento()->toString() << endl;
            hayDisponibles = true;
            i++;
        }
        actual = actual->getSiguiente();
    }

    if (!hayDisponibles) {
        s << "No hay vehiculos disponibles.\n";
    }

    return s.str();
}

string inventarioVehiculos::mostrarTotalDeEstados() {
    stringstream s;
    s << "\n===== RESUMEN DE ESTADOS DE VEHICULOS =====\n\n";

    int disponibles = 0, alquilados = 0, devueltos = 0, revision = 0, lavado = 0;

    nodoBase<vehiculo>* actual = primero;
    while (actual != nullptr) {
        string estado = actual->getElemento()->getEstado();
        if (estado == "Disponible") disponibles++;
        else if (estado == "Alquilado") alquilados++;
        else if (estado == "Devuelto") devueltos++;
        else if (estado == "Revision") revision++;
        else if (estado == "Lavado") lavado++;

        actual = actual->getSiguiente();
    }

    s << "Disponibles: " << disponibles << endl;
    s << "Alquilados: " << alquilados << endl;
    s << "Devueltos: " << devueltos << endl;
    s << "En Revision: " << revision << endl;
    s << "En Lavado: " << lavado << endl;
    s << "Total: " << cantidad << endl;

    return s.str();
}