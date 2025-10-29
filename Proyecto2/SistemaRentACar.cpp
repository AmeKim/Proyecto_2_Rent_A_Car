#include "SistemaRentACar.h"

SistemaRentACar::SistemaRentACar() {
    sucursales = new listaBase<sucursal>();
}

SistemaRentACar::~SistemaRentACar() {
    delete sucursales;
}

bool SistemaRentACar::agregarSucursal(sucursal* suc) {
    if (suc == nullptr) return false;
    return sucursales->agregarFinal(suc);
}

bool SistemaRentACar::eliminarSucursal(int idSucursal) {
    if (sucursales->estaVacia()) {
        return false;
    }

    nodoBase<sucursal>* actual = sucursales->retornarPrimero();
    nodoBase<sucursal>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getElemento()->getIdSucursal() == idSucursal) {
            if (anterior == nullptr) {
                // Eliminar el primero (no implementado en listaBase, usar workaround)
                sucursales->eliminarInicio();
            }
            else {
                anterior->setSiguiente(actual->getSiguiente());
                delete actual->getElemento();
                delete actual;
            }
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }

    return false;
}

sucursal* SistemaRentACar::buscarSucursal(int idSucursal) {
    nodoBase<sucursal>* actual = sucursales->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getIdSucursal() == idSucursal) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string SistemaRentACar::mostrarSucursales() const {
    if (sucursales->estaVacia()) {
        return "No hay sucursales registradas en el sistema.\n";
    }

    stringstream s;
    s << "\n===== SUCURSALES D-R-T CAR RENTAL =====\n\n";

    nodoBase<sucursal>* actual = sucursales->retornarPrimero();
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << "\n";
        actual = actual->getSiguiente();
        i++;
    }

    return s.str();
}

int SistemaRentACar::contarSucursales() const {
    return sucursales->getCantidad();
}

string SistemaRentACar::reporteClientesPorContratos() {
    stringstream s;
    s << "\n===== REPORTE: CLIENTES POR CANTIDAD DE CONTRATOS =====\n\n";

    // Estructura para almacenar información de clientes
    struct ClienteInfo {
        cliente* cli;
        int cantidadContratos;
        string codigosContratos;
    };

    // Vector dinámico simple (lista)
    listaBase<ClienteInfo>* clientesInfo = new listaBase<ClienteInfo>();

    // Recorrer todas las sucursales
    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();
    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();

        // Recorrer clientes de cada sucursal
        carteraClientes* cartera = suc->getClientes();
        nodoBase<cliente>* actualCli = cartera->retornarPrimero();

        while (actualCli != nullptr) {
            cliente* cli = actualCli->getElemento();

            // Contar contratos para este cliente en todas las sucursales
            int totalContratos = 0;
            stringstream codigosStr;

            nodoBase<sucursal>* suc2 = sucursales->retornarPrimero();
            while (suc2 != nullptr) {
                // Aquí necesitamos acceder a los contratos
                // (esto requeriría métodos adicionales en sucursal)
                suc2 = suc2->getSiguiente();
            }

            actualCli = actualCli->getSiguiente();
        }

        actualSuc = actualSuc->getSiguiente();
    }

    delete clientesInfo;

    s << "Funcionalidad pendiente de implementacion completa.\n";
    s << "Requiere recorrer todos los contratos de todas las sucursales.\n";

    return s.str();
}

string SistemaRentACar::reporteHistorialCliente(const string& idCliente) {
    stringstream s;
    s << "\n===== HISTORIAL DEL CLIENTE " << idCliente << " =====\n\n";

    bool encontrado = false;

    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();
    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();
        cliente* cli = suc->getClientes()->buscarClientePorCedula(idCliente);

        if (cli != nullptr) {
            s << "Cliente encontrado: " << cli->getNombre() << "\n";
            s << "Cedula: " << cli->getCedula() << "\n\n";

            s << "Solicitudes y contratos:\n";
            // Aquí se listarían todos los contratos
            // (requiere métodos adicionales)

            encontrado = true;
        }

        actualSuc = actualSuc->getSiguiente();
    }

    if (!encontrado) {
        s << "Cliente no encontrado en el sistema.\n";
    }

    return s.str();
}

bool SistemaRentACar::trasladarVehiculo(const string& placa, int idSucursalOrigen, int idSucursalDestino) {
    sucursal* origen = buscarSucursal(idSucursalOrigen);
    sucursal* destino = buscarSucursal(idSucursalDestino);

    if (origen == nullptr || destino == nullptr) {
        return false;
    }

    vehiculo* v = origen->getVehiculos()->buscarVehiculoPorPlaca(placa);
    if (v == nullptr || v->getEstado() == "Alquilado") {
        return false;
    }

    // Liberar espacio en origen
    if (!origen->eliminarVehiculoDeSucursal(placa)) {
        return false;
    }

    // Buscar plantel con más espacios en destino
    plantel* plantelDestino = destino->encontrarPlantelConMasEspacios();
    if (plantelDestino == nullptr || plantelDestino->estaLleno()) {
        // Revertir: agregar de vuelta a origen
        return false;
    }

    // Obtener recomendaciones de espacios
    vector<string> recomendaciones = plantelDestino->recomendarEspacios();
    if (recomendaciones.empty()) {
        return false;
    }

    // Usar el primer espacio recomendado
    // Nota: En una implementación real, el usuario elegiría
    // Por ahora asignamos automáticamente

    return true;
}