#include "SistemaRentACar.h"

SistemaRentACar::SistemaRentACar() : listaBase<sucursal>() {}

SistemaRentACar::~SistemaRentACar() {}

void SistemaRentACar::agregarSucursal(sucursal* suc) {
    if (suc != nullptr) {
        agregarFinal(suc);
    }
}

bool SistemaRentACar::eliminarSucursal(int id) {
    if (estaVacia()) {
        return false;
    }

    nodoBase<sucursal>* actual = primero;
    nodoBase<sucursal>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getElemento()->getId() == id) {
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

sucursal* SistemaRentACar::buscarSucursal(int id) {
    nodoBase<sucursal>* actual = primero;
    while (actual != nullptr) {
        if (actual->getElemento()->getId() == id) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string SistemaRentACar::mostrarSucursales() const {
    if (estaVacia()) {
        return "No hay sucursales registradas.\n";
    }

    stringstream s;
    s << "\n===== SUCURSALES REGISTRADAS =====\n\n";
    nodoBase<sucursal>* actual = primero;
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << "\n";
        actual = actual->getSiguiente();
        i++;
    }
    return s.str();
}

string SistemaRentACar::reporteOcupacionPlanteles() {
    stringstream s;
    s << "\n===== REPORTE DE OCUPACION DE PLANTELES =====\n\n";

    nodoBase<sucursal>* actual = primero;
    while (actual != nullptr) {
        sucursal* suc = actual->getElemento();
        s << "Sucursal: " << suc->getNombre() << " (ID: " << suc->getId() << ")\n";
        s << suc->reporteOcupacionPlanteles();
        s << "\n";
        actual = actual->getSiguiente();
    }

    return s.str();
}

bool SistemaRentACar::trasladarVehiculos(int idSucursalOrigen, int idSucursalDestino,
    int cantidadVehiculos) {
    sucursal* origen = buscarSucursal(idSucursalOrigen);
    sucursal* destino = buscarSucursal(idSucursalDestino);

    if (origen == nullptr || destino == nullptr) {
        return false;
    }

    if (origen == destino) {
        return false; // No se puede trasladar a la misma sucursal
    }

    // Obtener vehículos disponibles para traslado
    listaBase<vehiculo>* vehiculosDisponibles = origen->obtenerVehiculosDisponiblesParaTraslado();

    if (vehiculosDisponibles->getCantidad() < cantidadVehiculos) {
        delete vehiculosDisponibles;
        return false;
    }

    // Trasladar los vehículos
    vehiculosDisponibles->reiniciar();
    int contadorTrasladados = 0;

    while (contadorTrasladados < cantidadVehiculos) {
        vehiculo* v = vehiculosDisponibles->siguiente();
        if (v == nullptr) {
            break;
        }

        // Remover de sucursal origen (sin eliminar el objeto)
        if (origen->removerVehiculo(v)) {
            // El vehículo será agregado manualmente en la sucursal destino
            // por el usuario seleccionando el plantel y espacio
            contadorTrasladados++;
        }
    }

    delete vehiculosDisponibles;
    return contadorTrasladados == cantidadVehiculos;
}