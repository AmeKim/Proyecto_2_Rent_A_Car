#include "sucursal.h"

sucursal::sucursal() {
    id = 0;
    nombre = "";
    provincia = "";
    planteles = new listaBase<plantel>();
    clientes = new carteraClientes();
    colaboradores = new conjuntoColaboradores();
    vehiculos = new inventarioVehiculos();
    solicitudes = new listaBase<solicitudAlquiler>();
    contratos = new listaBase<contratoAlquiler>();
}

sucursal::sucursal(int id, string nombre, string provincia) {
    this->id = id;
    this->nombre = nombre;
    this->provincia = provincia;
    planteles = new listaBase<plantel>();
    clientes = new carteraClientes();
    colaboradores = new conjuntoColaboradores();
    vehiculos = new inventarioVehiculos();
    solicitudes = new listaBase<solicitudAlquiler>();
    contratos = new listaBase<contratoAlquiler>();
}

sucursal::~sucursal() {
    delete planteles;
    delete clientes;
    delete colaboradores;
    delete vehiculos;
    delete solicitudes;
    delete contratos;
}

int sucursal::getId() const { return id; }
string sucursal::getNombre() const { return nombre; }
string sucursal::getProvincia() const { return provincia; }

void sucursal::setId(int id) { this->id = id; }
void sucursal::setNombre(string nombre) { this->nombre = nombre; }
void sucursal::setProvincia(string provincia) { this->provincia = provincia; }

// Gestión de planteles
void sucursal::agregarPlantel(plantel* p) {
    if (p != nullptr) {
        planteles->agregarFinal(p);
    }
}

plantel* sucursal::buscarPlantel(string nombre) {
    planteles->reiniciar();
    plantel* p = planteles->siguiente();
    while (p != nullptr) {
        if (p->getNombre() == nombre) {
            return p;
        }
        p = planteles->siguiente();
    }
    return nullptr;
}

string sucursal::mostrarPlanteles() const {
    if (planteles->estaVacia()) {
        return "No hay planteles registrados en esta sucursal.\n";
    }
    return planteles->toStringLista();
}

string sucursal::reporteOcupacionPlanteles() {
    stringstream s;
    planteles->reiniciar();
    plantel* p = planteles->siguiente();

    if (p == nullptr) {
        s << "  No hay planteles registrados.\n";
        return s.str();
    }

    while (p != nullptr) {
        s << "  Plantel " << p->getNombre() << ": ";
        s << p->calcularPorcentajeOcupacion() << "% ocupado\n";
        s << "  Espacios libres: " << p->contarEspaciosLibres();
        s << "/" << p->getCapacidadMax() << "\n";
        p = planteles->siguiente();
    }
    return s.str();
}

// Gestión de clientes
carteraClientes* sucursal::getClientes() { return clientes; }

void sucursal::agregarClienteFisico(personaFisica* pf) {
    if (pf != nullptr) {
        clientes->agregarClienteFisico(pf);
    }
}

void sucursal::agregarClienteJuridico(personaJuridica* pj) {
    if (pj != nullptr) {
        clientes->agregarClienteJuridico(pj);
    }
}

bool sucursal::eliminarCliente(string id) {
    return clientes->eliminarCliente(id);
}

string sucursal::mostrarClientes() {
    return clientes->mostrarTodosLosClientes();
}

// Gestión de colaboradores
conjuntoColaboradores* sucursal::getColaboradores() { return colaboradores; }

void sucursal::agregarColaborador(colaborador* col) {
    if (col != nullptr) {
        colaboradores->agregarColaborador(col);
    }
}

bool sucursal::eliminarColaborador(string id) {
    return colaboradores->eliminarColaborador(id);
}

string sucursal::mostrarColaboradores() {
    return colaboradores->mostrarColaboradores();
}

// Gestión de vehículos
inventarioVehiculos* sucursal::getVehiculos() { return vehiculos; }

void sucursal::agregarVehiculo(vehiculo* v) {
    if (v != nullptr) {
        vehiculos->agregarVehiculo(v);
    }
}

bool sucursal::eliminarVehiculo(string placa) {
    return vehiculos->eliminarVehiculoPorPlaca(placa);
}

string sucursal::mostrarVehiculos() {
    return vehiculos->mostrarVehiculos();
}

vehiculo* sucursal::buscarVehiculo(string placa) {
    return vehiculos->buscarVehiculoPorPlaca(placa);
}

// Gestión de solicitudes y contratos
void sucursal::agregarSolicitud(solicitudAlquiler* sol) {
    if (sol != nullptr) {
        solicitudes->agregarFinal(sol);
    }
}

void sucursal::agregarContrato(contratoAlquiler* con) {
    if (con != nullptr) {
        contratos->agregarFinal(con);
    }
}

solicitudAlquiler* sucursal::buscarSolicitud(string codigo) {
    solicitudes->reiniciar();
    solicitudAlquiler* s = solicitudes->siguiente();
    while (s != nullptr) {
        if (s->getCodigo() == codigo) {
            return s;
        }
        s = solicitudes->siguiente();
    }
    return nullptr;
}

contratoAlquiler* sucursal::buscarContrato(string codigo) {
    contratos->reiniciar();
    contratoAlquiler* c = contratos->siguiente();
    while (c != nullptr) {
        if (c->getCodigo() == codigo) {
            return c;
        }
        c = contratos->siguiente();
    }
    return nullptr;
}

string sucursal::mostrarSolicitudes() {
    if (solicitudes->estaVacia()) {
        return "No hay solicitudes registradas.\n";
    }
    return solicitudes->toStringLista();
}

string sucursal::mostrarContratos() {
    if (contratos->estaVacia()) {
        return "No hay contratos registrados.\n";
    }
    return contratos->toStringLista();
}

string sucursal::mostrarContratosOrdenados() {
    // Implementación simplificada - en una versión completa debería ordenar por fecha
    return mostrarContratos();
}

// Reportes
string sucursal::historialCliente(string idCliente) {
    stringstream s;
    s << "\n===== HISTORIAL DEL CLIENTE =====\n";
    s << "ID Cliente: " << idCliente << "\n\n";

    bool encontrado = false;

    s << "--- Solicitudes ---\n";
    solicitudes->reiniciar();
    solicitudAlquiler* sol = solicitudes->siguiente();
    while (sol != nullptr) {
        if (sol->getCliente()->getCedula() == idCliente) {
            s << "Codigo: " << sol->getCodigo();
            s << " | Placa: " << sol->getVehiculo()->getPlaca();
            s << " | Estado: " << sol->getEstado() << "\n";
            encontrado = true;
        }
        sol = solicitudes->siguiente();
    }

    s << "\n--- Contratos ---\n";
    contratos->reiniciar();
    contratoAlquiler* con = contratos->siguiente();
    while (con != nullptr) {
        if (con->getCliente()->getCedula() == idCliente) {
            s << "Codigo: " << con->getCodigo();
            s << " | Placa: " << con->getVehiculo()->getPlaca();
            s << " | Estado: " << con->getEstadoContrato() << "\n";
            encontrado = true;
        }
        con = contratos->siguiente();
    }

    if (!encontrado) {
        s << "No se encontro historial para este cliente.\n";
    }

    return s.str();
}

string sucursal::reporteClientesPorContratos() {
    stringstream s;
    s << "\n===== REPORTE: CLIENTES POR CANTIDAD DE CONTRATOS =====\n\n";

    // Implementación simplificada - versión completa requeriría ordenamiento
    clientes->reiniciar();
    cliente* cli = clientes->siguiente();

    while (cli != nullptr) {
        int contador = 0;
        contratos->reiniciar();
        contratoAlquiler* con = contratos->siguiente();

        while (con != nullptr) {
            if (con->getCliente()->getCedula() == cli->getCedula()) {
                contador++;
            }
            con = contratos->siguiente();
        }

        if (contador > 0) {
            s << "Cliente: " << cli->getNombre();
            s << " (ID: " << cli->getCedula() << ")\n";
            s << "Total de contratos: " << contador << "\n\n";
        }

        cli = clientes->siguiente();
    }

    return s.str();
}

string sucursal::reporteContratosVehiculo(string placa) {
    stringstream s;
    s << "\n===== REPORTE: CONTRATOS PARA VEHICULO " << placa << " =====\n\n";

    contratos->reiniciar();
    contratoAlquiler* con = contratos->siguiente();
    bool encontrado = false;

    while (con != nullptr) {
        if (con->getVehiculo()->getPlaca() == placa) {
            s << con->toString() << "\n";
            encontrado = true;
        }
        con = contratos->siguiente();
    }

    if (!encontrado) {
        s << "No se encontraron contratos para este vehiculo.\n";
    }

    return s.str();
}

string sucursal::reporteAlquileresPorColaborador(string idColaborador) {
    stringstream s;
    colaborador* col = colaboradores->buscarColaborador(idColaborador);

    if (col == nullptr) {
        return "Colaborador no encontrado.\n";
    }

    s << "\n===== REPORTE: ALQUILERES POR COLABORADOR =====\n";
    s << "Colaborador: " << col->getNombre();
    s << " (ID: " << col->getCedula() << ")\n\n";

    contratos->reiniciar();
    contratoAlquiler* con = contratos->siguiente();
    bool encontrado = false;

    while (con != nullptr) {
        if (con->getColaborador()->getCedula() == idColaborador) {
            s << "Contrato: " << con->getCodigo();
            s << " | Placa: " << con->getVehiculo()->getPlaca();
            s << " | Cliente: " << con->getCliente()->getCedula() << "\n";
            encontrado = true;
        }
        con = contratos->siguiente();
    }

    if (!encontrado) {
        s << "No se encontraron alquileres para este colaborador.\n";
    }

    return s.str();
}

// Traslado de vehículos
listaBase<vehiculo>* sucursal::obtenerVehiculosDisponiblesParaTraslado() {
    listaBase<vehiculo>* vehiculosDisponibles = new listaBase<vehiculo>();

    vehiculos->reiniciar();
    vehiculo* v = vehiculos->siguiente();

    while (v != nullptr) {
        // Solo vehículos que NO estén alquilados pueden ser trasladados
        if (v->getEstado() != "Alquilado") {
            vehiculosDisponibles->agregarFinal(v);
        }
        v = vehiculos->siguiente();
    }

    return vehiculosDisponibles;
}

bool sucursal::removerVehiculo(vehiculo* v) {
    if (v == nullptr) {
        return false;
    }

    // Buscar y remover de la lista de vehículos sin eliminar el objeto
    if (vehiculos->estaVacia()) {
        return false;
    }

    nodoBase<vehiculo>* actual = vehiculos->primero;
    nodoBase<vehiculo>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getElemento() == v) {
            if (anterior == nullptr) {
                vehiculos->primero = actual->getSiguiente();
            }
            else {
                anterior->setSiguiente(actual->getSiguiente());
            }

            // Solo eliminar el nodo, NO el vehículo
            delete actual;
            vehiculos->cantidad--;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }
    return false;
}

bool sucursal::agregarVehiculoDeTraslado(vehiculo* v, string nombrePlantel, string espacioEstacionamiento) {
    if (v == nullptr) {
        return false;
    }

    // Buscar el plantel
    plantel* p = buscarPlantel(nombrePlantel);
    if (p == nullptr) {
        return false;
    }

    // Intentar asignar el espacio de estacionamiento
    if (!p->asignarEspacioManual(espacioEstacionamiento, v)) {
        return false;
    }

    // Actualizar la ubicación del vehículo
    v->setUbicacionPlantel(nombrePlantel);

    // Agregar el vehículo al inventario de esta sucursal
    vehiculos->agregarFinal(v);

    return true;
}

string sucursal::toString() const {
    stringstream s;
    s << "ID: " << id << " - " << nombre << " (" << provincia << ")";
    return s.str();
}