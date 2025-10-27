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
            // Verificar que no esté alquilado
            if (actual->getElemento()->getEstado() == "Alquilado") {
                return false; // No se puede eliminar un vehículo alquilado
            }

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

    nodoBase<vehiculo>* actual = primero;
    stringstream s;
    s << "\n===== INVENTARIO DE VEHICULOS =====\n\n";
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << endl;
        actual = actual->getSiguiente();
        i++;
    }
    return s.str();
}

string inventarioVehiculos::mostrarVehiculosDisponibles() const {
    nodoBase<vehiculo>* actual = primero;
    stringstream s;
    s << "\n===== VEHICULOS DISPONIBLES =====\n\n";
    int i = 1;
    while (actual != nullptr) {
        if (actual->getElemento()->getEstado() == "Disponible") {
            s << i << ". " << actual->getElemento()->toString() << endl;
            i++;
        }
        actual = actual->getSiguiente();
    }
    if (i == 1) {
        s << "No hay vehiculos disponibles.\n";
    }
    return s.str();
}

string inventarioVehiculos::mostrarTotalDeEstados() {
    stringstream s;
    int disponibles = 0;
    int revision = 0;
    int alquilados = 0;
    int devueltos = 0;
    int lavados = 0;

    nodoBase<vehiculo>* actual = primero;
    while (actual != nullptr) {
        string estado = actual->getElemento()->getEstado();
        if (estado == "Disponible") {
            disponibles++;
        }
        else if (estado == "Revision") {
            revision++;
        }
        else if (estado == "Alquilado") {
            alquilados++;
        }
        else if (estado == "Devuelto") {
            devueltos++;
        }
        else if (estado == "Lavado") {
            lavados++;
        }
        actual = actual->getSiguiente();
    }

    s << "\n===== TOTAL DE VEHICULOS POR ESTADO =====\n\n";
    s << "Disponibles: " << disponibles << endl;
    s << "En Revision: " << revision << endl;
    s << "Alquilados: " << alquilados << endl;
    s << "Devueltos: " << devueltos << endl;
    s << "En Lavado: " << lavados << endl;
    s << "\nTotal: " << cantidad << endl;

    return s.str();
}