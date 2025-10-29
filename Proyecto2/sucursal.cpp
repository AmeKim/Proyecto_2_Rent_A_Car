#include "sucursal.h"

sucursal::sucursal() {
    idSucursal = 0;
    nombre = "";
    provincia = "";
    planteles = new listaBase<plantel>();
    clientes = new carteraClientes();
    colaboradores = new conjuntoColaboradores();
    vehiculos = new inventarioVehiculos();
    solicitudes = new listaBase<solicitudAlquiler>();
    contratos = new listaBase<contratoAlquiler>();
}

sucursal::sucursal(int id, const string& nombre, const string& provincia) {
    this->idSucursal = id;
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

int sucursal::getIdSucursal() const { return idSucursal; }
string sucursal::getNombre() const { return nombre; }
string sucursal::getProvincia() const { return provincia; }

void sucursal::setIdSucursal(int id) { idSucursal = id; }
void sucursal::setNombre(const string& nombre) { this->nombre = nombre; }
void sucursal::setProvincia(const string& provincia) { this->provincia = provincia; }

bool sucursal::agregarPlantel(plantel* p) {
    if (p == nullptr) return false;
    return planteles->agregarFinal(p);
}

plantel* sucursal::buscarPlantel(char letra) {
    planteles->reiniciar();
    plantel* p = planteles->siguiente();
    while (p != nullptr) {
        if (p->getLetra() == letra) {
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

    stringstream s;
    s << "\n===== PLANTELES DE SUCURSAL " << nombre << " =====\n\n";

    nodoBase<plantel>* actual = planteles->retornarPrimero();
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << "\n";
        actual = actual->getSiguiente();
        i++;
    }
    return s.str();
}

plantel* sucursal::encontrarPlantelConMasEspacios() {
    if (planteles->estaVacia()) return nullptr;

    plantel* mejorPlantel = nullptr;
    int maxEspacios = -1;

    nodoBase<plantel>* actual = planteles->retornarPrimero();
    while (actual != nullptr) {
        plantel* p = actual->getElemento();
        int espaciosDisp = p->getEspaciosDisponibles();
        if (espaciosDisp > maxEspacios) {
            maxEspacios = espaciosDisp;
            mejorPlantel = p;
        }
        actual = actual->getSiguiente();
    }

    return mejorPlantel;
}

string sucursal::reportePorcentajeOcupacion() const {
    stringstream s;
    s << "\n===== PORCENTAJE DE OCUPACION - SUCURSAL " << nombre << " =====\n\n";

    if (planteles->estaVacia()) {
        s << "No hay planteles registrados.\n";
        return s.str();
    }

    nodoBase<plantel>* actual = planteles->retornarPrimero();
    while (actual != nullptr) {
        plantel* p = actual->getElemento();
        s << "Plantel " << p->getLetra() << ": ";
        s << p->getEspaciosOcupados() << "/" << p->getCapacidad() << " espacios ";
        s << "(" << p->getPorcentajeOcupacion() << "%)\n";
        actual = actual->getSiguiente();
    }

    return s.str();
}

carteraClientes* sucursal::getClientes() { return clientes; }
conjuntoColaboradores* sucursal::getColaboradores() { return colaboradores; }
inventarioVehiculos* sucursal::getVehiculos() { return vehiculos; }

bool sucursal::agregarVehiculoASucursal(vehiculo* v, char letraPlantel, int fila, int columna) {
    if (v == nullptr) return false;

    plantel* p = buscarPlantel(letraPlantel);
    if (p == nullptr) return false;

    if (p->asignarVehiculo(fila, columna, v)) {
        vehiculos->agregarVehiculo(v);
        return true;
    }
    return false;
}

bool sucursal::eliminarVehiculoDeSucursal(const string& placa) {
    vehiculo* v = vehiculos->buscarVehiculoPorPlaca(placa);
    if (v == nullptr || v->getEstado() == "Alquilado") {
        return false;
    }

    // Liberar el espacio en el plantel
    string ubicacion = v->getUbicacionPlantel();
    // Formato: "A-0-1"
    if (ubicacion.length() > 0) {
        char letra = ubicacion[0];
        plantel* p = buscarPlantel(letra);
        if (p != nullptr) {
            // Extraer fila y columna
            int fila = ubicacion[2] - '0';
            int columna = ubicacion[4] - '0';
            p->liberarEspacio(fila, columna);
        }
    }

    return vehiculos->eliminarVehiculoPorPlaca(placa);
}

bool sucursal::reubicarVehiculo(const string& placa, char nuevoPlantel, int fila, int columna) {
    vehiculo* v = vehiculos->buscarVehiculoPorPlaca(placa);
    if (v == nullptr || v->getEstado() == "Alquilado") {
        return false;
    }

    // Liberar espacio anterior
    string ubicacionAnterior = v->getUbicacionPlantel();
    if (ubicacionAnterior.length() > 0) {
        char letraAnterior = ubicacionAnterior[0];
        plantel* pAnterior = buscarPlantel(letraAnterior);
        if (pAnterior != nullptr) {
            int filaAnt = ubicacionAnterior[2] - '0';
            int colAnt = ubicacionAnterior[4] - '0';
            pAnterior->liberarEspacio(filaAnt, colAnt);
        }
    }

    // Asignar nuevo espacio
    plantel* pNuevo = buscarPlantel(nuevoPlantel);
    if (pNuevo != nullptr) {
        return pNuevo->asignarVehiculo(fila, columna, v);
    }

    return false;
}

bool sucursal::agregarSolicitud(solicitudAlquiler* sol) {
    if (sol == nullptr) return false;
    return solicitudes->agregarFinal(sol);
}

solicitudAlquiler* sucursal::buscarSolicitud(const string& codigo) {
    nodoBase<solicitudAlquiler>* actual = solicitudes->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getCodigo() == codigo) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string sucursal::mostrarSolicitudes() const {
    if (solicitudes->estaVacia()) {
        return "No hay solicitudes registradas.\n";
    }

    stringstream s;
    s << "\n===== SOLICITUDES DE ALQUILER =====\n\n";
    nodoBase<solicitudAlquiler>* actual = solicitudes->retornarPrimero();
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << "\n";
        actual = actual->getSiguiente();
        i++;
    }
    return s.str();
}

bool sucursal::aprobarSolicitud(const string& codigo) {
    solicitudAlquiler* sol = buscarSolicitud(codigo);
    if (sol == nullptr || sol->getEstado() != "Pendiente") {
        return false;
    }

    sol->aprobar();

    // Crear contrato a partir de la solicitud
    contratoAlquiler* contrato = new contratoAlquiler(*sol);
    contratos->agregarFinal(contrato);

    // Cambiar estado del vehículo a "Alquilado"
    vehiculo* v = sol->getVehiculo();
    if (v != nullptr) {
        v->setEstado("Alquilado");
    }

    return true;
}

bool sucursal::rechazarSolicitud(const string& codigo) {
    solicitudAlquiler* sol = buscarSolicitud(codigo);
    if (sol == nullptr) return false;
    sol->rechazar();
    return true;
}

bool sucursal::agregarContrato(contratoAlquiler* contrato) {
    if (contrato == nullptr) return false;
    return contratos->agregarFinal(contrato);
}

contratoAlquiler* sucursal::buscarContrato(const string& codigo) {
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getCodigo() == codigo) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string sucursal::mostrarContratos() const {
    if (contratos->estaVacia()) {
        return "No hay contratos registrados.\n";
    }

    stringstream s;
    s << "\n===== CONTRATOS DE ALQUILER =====\n\n";
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << "\n";
        actual = actual->getSiguiente();
        i++;
    }
    return s.str();
}

string sucursal::mostrarContratosOrdenados() const {
    // Implementación simple: copiar a array y ordenar
    // En producción se usaría una lista ordenada
    return mostrarContratos();
}

string sucursal::reporteContratosVehiculo(const string& placa) const {
    stringstream s;
    s << "\n===== CONTRATOS PARA VEHICULO " << placa << " =====\n\n";

    bool encontrado = false;
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
    int i = 1;

    while (actual != nullptr) {
        contratoAlquiler* c = actual->getElemento();
        if (c->getVehiculo() != nullptr && c->getVehiculo()->getPlaca() == placa) {
            s << i << ". " << c->toString() << "\n";
            encontrado = true;
            i++;
        }
        actual = actual->getSiguiente();
    }

    if (!encontrado) {
        s << "No hay contratos para este vehiculo.\n";
    }

    return s.str();
}

string sucursal::reporteAlquileresColaborador(const string& idColaborador) const {
    stringstream s;
    s << "\n===== ALQUILERES POR COLABORADOR " << idColaborador << " =====\n\n";

    bool encontrado = false;
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
    int i = 1;

    while (actual != nullptr) {
        contratoAlquiler* c = actual->getElemento();
        if (c->getColaborador() != nullptr && c->getColaborador()->getCedula() == idColaborador) {
            s << i << ". Codigo: " << c->getCodigo();
            if (c->getVehiculo() != nullptr) {
                s << " - Placa: " << c->getVehiculo()->getPlaca();
            }
            if (c->getCliente() != nullptr) {
                s << " - Cliente: " << c->getCliente()->getCedula();
            }
            s << "\n";
            encontrado = true;
            i++;
        }
        actual = actual->getSiguiente();
    }

    if (!encontrado) {
        s << "No hay alquileres para este colaborador.\n";
    }

    return s.str();
}

string sucursal::toString() const {
    stringstream s;
    s << "Sucursal #" << idSucursal << " - " << nombre << " (" << provincia << ")";
    return s.str();
}