#include "sucursal.h"

int sucursal::compararFechas(const string& fecha1, const string& fecha2) const {
    int dia1, mes1, anio1;
    int dia2, mes2, anio2;
    char separador;

    stringstream s1(fecha1);
    s1 >> dia1 >> separador >> mes1 >> separador >> anio1;

    stringstream s2(fecha2);
    s2 >> dia2 >> separador >> mes2 >> separador >> anio2;

    // Comparar años
    if (anio1 != anio2) { return anio1 - anio2; }

    // Comparar meses
    if (mes1 != mes2) { return mes1 - mes2; }

    // Comparar días
    return dia1 - dia2;
}

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

// ==================== GESTION DE PLANTELES ====================

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

        // Formatear porcentaje con 2 decimales
        double porcentaje = p->getPorcentajeOcupacion();
        s.precision(2);
        s << fixed << "(" << porcentaje << "%)\n";

        actual = actual->getSiguiente();
    }

    return s.str();
}

// ==================== GESTION DE CLIENTES ====================

carteraClientes* sucursal::getClientes() {
    return clientes;
}

// ==================== GESTION DE COLABORADORES ====================

conjuntoColaboradores* sucursal::getColaboradores() {
    return colaboradores;
}

// ==================== GESTION DE VEHICULOS ====================

inventarioVehiculos* sucursal::getVehiculos() {
    return vehiculos;
}

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

    if (ubicacion.length() >= 5) {  // Formato: "A-0-1"
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

    if (ubicacionAnterior.length() >= 5) {
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

// ==================== GESTION DE SOLICITUDES ====================

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

// ==================== GESTION DE CONTRATOS ====================

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
    stringstream s;
    if (contratos->estaVacia()) {
        return "No hay contratos registrados.\n";
    }

    // Crear lista temporal para ordenar contratos
    listaBase<contratoAlquiler>* contratosOrdenados = new listaBase<contratoAlquiler>();

    // Copiar contratos a lista temporal
    nodoBase<contratoAlquiler>* temp = contratos->retornarPrimero();
    while (temp != nullptr) {
        contratosOrdenados->agregarFinal(temp->getElemento());
        temp = temp->getSiguiente();
    }

    // Ordenar del más reciente al más antiguo (Bubble Sort)
    bool cambio = true;
    while (cambio) {
        cambio = false;
        nodoBase<contratoAlquiler>* actual = contratosOrdenados->retornarPrimero();

        while (actual != nullptr && actual->getSiguiente() != nullptr) {
            contratoAlquiler* c1 = actual->getElemento();
            contratoAlquiler* c2 = actual->getSiguiente()->getElemento();

            // Comparar fechas (más reciente primero = orden descendente)
            if (compararFechas(c1->getFechaInicio(), c2->getFechaInicio()) < 0) {
                // Intercambiar
                actual->setElemento(c2);
                actual->getSiguiente()->setElemento(c1);
                cambio = true;
            }
            actual = actual->getSiguiente();
        }
    }

    s << "\n===== CONTRATOS DE LA SUCURSAL (DEL MAS RECIENTE AL MAS ANTIGUO) =====\n\n";

    int pos = 1;
    nodoBase<contratoAlquiler>* mostrar = contratosOrdenados->retornarPrimero();

    while (mostrar != nullptr) {
        s << "--- CONTRATO #" << pos << " ---\n";
        s << mostrar->getElemento()->toString();
        s << "\n";
        pos++;
        mostrar = mostrar->getSiguiente();
    }

    delete contratosOrdenados;
    return s.str();
}

// ==================== REPORTES ====================

string sucursal::reporteContratosVehiculo(const string& placa) const {
    stringstream s;
    s << "\n===== CONTRATOS PARA VEHICULO " << placa << " =====\n\n";

    bool encontrado = false;
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
    int i = 1;

    while (actual != nullptr) {
        contratoAlquiler* c = actual->getElemento();
        if (c->getVehiculo() != nullptr && c->getVehiculo()->getPlaca() == placa) {
            s << i << ". Codigo: " << c->getCodigo() << "\n";

            if (c->getCliente() != nullptr) {
                s << "   Cliente: " << c->getCliente()->getNombre();
                s << " (ID: " << c->getCliente()->getCedula() << ")\n";
            }

            s << "   Dias: " << c->getDias() << "\n";
            s << "   Fecha inicio: " << c->getFechaInicio() << "\n";
            s << "   Fecha devolucion: " << c->getFechaEntrega() << "\n";
            s << "   Estado: " << c->getEstadoContrato() << "\n\n";

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

    // Buscar el colaborador primero
    colaborador* col = colaboradores->buscarColaborador(idColaborador);

    if (col == nullptr) {
        s << "Colaborador no encontrado.\n";
        return s.str();
    }

    s << "\n===== ALQUILERES POR COLABORADOR =====\n\n";
    s << "ID: " << col->getCedula() << "\n";
    s << "Nombre: " << col->getNombre() << "\n\n";
    s << "Contratos realizados:\n\n";

    bool encontrado = false;
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
    int i = 1;

    while (actual != nullptr) {
        contratoAlquiler* c = actual->getElemento();

        if (c->getColaborador() != nullptr &&
            c->getColaborador()->getCedula() == idColaborador) {

            s << i << ". Codigo contrato: " << c->getCodigo() << "\n";

            if (c->getVehiculo() != nullptr) {
                s << "   Placa vehiculo: " << c->getVehiculo()->getPlaca() << "\n";
            }

            if (c->getCliente() != nullptr) {
                s << "   ID Cliente: " << c->getCliente()->getCedula() << "\n";
            }

            s << "   Estado: " << c->getEstadoContrato() << "\n";
            s << "   Precio total: $" << c->getPrecioTotal() << "\n\n";

            encontrado = true;
            i++;
        }
        actual = actual->getSiguiente();
    }

    if (!encontrado) {
        s << "No hay alquileres registrados para este colaborador.\n";
    }
    else {
        s << "Total de alquileres: " << (i - 1) << "\n";
    }

    return s.str();
}

string sucursal::toString() const {
    stringstream s;
    s << "Sucursal #" << idSucursal << " - " << nombre << " (" << provincia << ")";
    return s.str();
}

bool sucursal::trasladarVehiculoA(vehiculo* v, sucursal* destino, char letraPlantel, int fila, int columna) {
    if (v == nullptr || destino == nullptr) {
        return false;
    }

    // Verificar que el vehículo no esté alquilado
    if (v->getEstado() == "Alquilado") {
        return false;
    }

    // Verificar que el vehículo pertenezca a esta sucursal
    vehiculo* encontrado = vehiculos->buscarVehiculoPorPlaca(v->getPlaca());
    if (encontrado == nullptr) {
        return false;
    }

    // Guardar información del vehículo
    string placa = v->getPlaca();

    // Liberar espacio en la sucursal origen
    string ubicacionActual = v->getUbicacionPlantel();
    if (ubicacionActual.length() >= 5) {
        char letraActual = ubicacionActual[0];
        plantel* pActual = buscarPlantel(letraActual);

        if (pActual != nullptr) {
            // Extraer fila y columna de la ubicación
            size_t pos1 = ubicacionActual.find('-');
            size_t pos2 = ubicacionActual.find('-', pos1 + 1);

            if (pos1 != string::npos && pos2 != string::npos) {
                int filaActual = stoi(ubicacionActual.substr(pos1 + 1, pos2 - pos1 - 1));
                int colActual = stoi(ubicacionActual.substr(pos2 + 1));
                pActual->liberarEspacio(filaActual, colActual);
            }
        }
    }

    // Crear una copia de los datos del vehículo
    vehiculo* vehCopia = new vehiculo(
        v->getPlaca(),
        v->getModelo(),
        v->getMarca(),
        v->getTipoLicencia(),
        v->getPrecio(),
        v->getEstado(),
        v->getCategoria(),
        ""
    );

    // Eliminar de origen usando el método existente
    if (!vehiculos->eliminarVehiculoPorPlaca(placa)) {
        delete vehCopia;
        return false;
    }

    // Agregar a destino
    if (destino->agregarVehiculoASucursal(vehCopia, letraPlantel, fila, columna)) {
        return true;
    }
    else {
        // Si falla, revertir eliminación agregando de nuevo a origen
        vehiculos->agregarVehiculo(vehCopia);
        return false;
    }
}

listaBase<vehiculo>* sucursal::obtenerVehiculosDisponiblesParaTraslado() {
    listaBase<vehiculo>* disponibles = new listaBase<vehiculo>();

    nodoBase<vehiculo>* actual = vehiculos->retornarPrimero();

    while (actual != nullptr) {
        vehiculo* v = actual->getElemento();
        if (v != nullptr && v->getEstado() != "Alquilado") {
            disponibles->agregarFinal(v);
        }
        actual = actual->getSiguiente();
    }

    return disponibles;
}