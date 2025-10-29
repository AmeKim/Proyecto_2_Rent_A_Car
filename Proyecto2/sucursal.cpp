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

sucursal::sucursal(int id, const string nom, const string prov) {
    idSucursal = id;
    nombre = nom;
    provincia = prov;
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

bool sucursal::agregarPlantel(plantel* p) {
    if (p == nullptr) {
        return false;
    }
    return planteles->agregarFinal(p);
}

plantel* sucursal::buscarPlantel(string nombre) {
    nodoBase<plantel>* actual = planteles->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getNombre() == nombre) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string sucursal::mostrarPlanteles() const {
    if (planteles->estaVacia()) {
        return "No hay planteles registrados.\n";
    }
    return planteles->toStringLista();
}

carteraClientes* sucursal::getCarteraClientes() {
    return clientes;
}

conjuntoColaboradores* sucursal::getConjuntoColaboradores() {
    return colaboradores;
}

inventarioVehiculos* sucursal::getInventarioVehiculos() {
    return vehiculos;
}

vehiculo* sucursal::buscarVehiculoPorPlaca(string placa) {
    nodoBase<vehiculo>* actual = vehiculos->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getPlaca() == placa) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

bool sucursal::agregarSolicitud(solicitudAlquiler* sol) {
    if (sol == nullptr) {
        return false;
    }
    return solicitudes->agregarFinal(sol);
}

bool sucursal::agregarContrato(contratoAlquiler* con) {
    if (con == nullptr) {
        return false;
    }
    return contratos->agregarFinal(con);
}

solicitudAlquiler* sucursal::buscarSolicitudPorCodigo(string codigo) {
    nodoBase<solicitudAlquiler>* actual = solicitudes->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getCodigo() == codigo) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

contratoAlquiler* sucursal::buscarContratoPorCodigo(string codigo) {
    nodoBase<contratoAlquiler>* actual = contratos->retornarPrimero();
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
    return solicitudes->toStringLista();
}

string sucursal::mostrarContratos() const {
    if (contratos->estaVacia()) {
        return "No hay contratos registrados.\n";
    }
    return contratos->toStringLista();
}

string sucursal::recomendarEspacioEstacionamiento() {
    stringstream s;

    // Buscar plantel con más espacios libres
    plantel* mejorPlantel = nullptr;
    int maxEspaciosLibres = -1;

    nodoBase<plantel>* actual = planteles->retornarPrimero();
    while (actual != nullptr) {
        plantel* p = actual->getElemento();
        int libres = p->contarEspaciosLibres();

        if (libres > maxEspaciosLibres) {
            maxEspaciosLibres = libres;
            mejorPlantel = p;
        }

        actual = actual->getSiguiente();
    }

    if (mejorPlantel == nullptr || maxEspaciosLibres == 0) {
        s << "No hay espacios disponibles en ningún plantel.\n";
        return s.str();
    }

    s << "Plantel recomendado: " << mejorPlantel->getNombre() << "\n";
    s << "Espacios libres: " << maxEspaciosLibres << "\n\n";

    // Buscar espacios con menos vehículos alrededor
    s << "Espacios recomendados (con menos vecinos ocupados):\n";

    int mejoresPosiciones = 0;
    int minVecinos = 999;

    for (int i = 0; i < mejorPlantel->getFilas() && mejoresPosiciones < 3; i++) {
        for (int j = 0; j < mejorPlantel->getColumnas() && mejoresPosiciones < 3; j++) {
            espacioEstacionamiento* espacio = mejorPlantel->obtenerEspacio(i, j);

            if (espacio != nullptr && !espacio->estaOcupado()) {
                // Contar vecinos ocupados
                int vecinosOcupados = 0;

                // Verificar 8 direcciones
                for (int di = -1; di <= 1; di++) {
                    for (int dj = -1; dj <= 1; dj++) {
                        if (di == 0 && dj == 0) continue;

                        int ni = i + di;
                        int nj = j + dj;

                        espacioEstacionamiento* vecino = mejorPlantel->obtenerEspacio(ni, nj);
                        if (vecino != nullptr && vecino->estaOcupado()) {
                            vecinosOcupados++;
                        }
                    }
                }

                if (vecinosOcupados <= minVecinos) {
                    if (vecinosOcupados < minVecinos) {
                        mejoresPosiciones = 0;
                        minVecinos = vecinosOcupados;
                    }

                    s << (mejoresPosiciones + 1) << ". " << espacio->getCodigo();
                    s << " (vecinos ocupados: " << vecinosOcupados << ")\n";
                    mejoresPosiciones++;
                }
            }
        }
    }

    return s.str();
}

void sucursal::mostrarResumen() const {
    cout << toString();
}

string sucursal::toString() const {
    stringstream s;
    s << "===== Sucursal =====\n";
    s << "ID: " << idSucursal << endl;
    s << "Nombre: " << nombre << endl;
    s << "Provincia: " << provincia << endl;
    s << "Planteles: " << planteles->getCantidad() << endl;
    s << "Clientes: " << clientes->getCantidad() << endl;
    s << "Colaboradores: " << colaboradores->getCantidad() << endl;
    s << "Vehiculos: " << vehiculos->getCantidad() << endl;
    return s.str();
}