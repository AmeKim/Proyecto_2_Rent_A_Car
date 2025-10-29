#include "SistemaRentACar.h"

SistemaRentACar::SistemaRentACar() {
    sucursales = new listaBase<sucursal>();
    contadorCodigoSolicitud = 1000;
    contadorCodigoContrato = 2000;
}

SistemaRentACar::~SistemaRentACar() {
    delete sucursales;
}

void SistemaRentACar::registrarSucursal(sucursal* s) {
    if (s != nullptr) {
        sucursales->agregarFinal(s);
    }
}

bool SistemaRentACar::eliminarSucursal(int id) {
    nodoBase<sucursal>* anterior = nullptr;
    nodoBase<sucursal>* actual = sucursales->retornarPrimero();

    while (actual != nullptr) {
        if (actual->getElemento()->getIdSucursal() == id) {
            if (anterior == nullptr) {
                // Eliminar el primero
                sucursales->eliminarInicio();
            }
            else {
                // Eliminar en medio o al final
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

sucursal* SistemaRentACar::buscarSucursalPorId(int id) {
    nodoBase<sucursal>* actual = sucursales->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getIdSucursal() == id) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string SistemaRentACar::mostrarSucursales() {
    if (sucursales->estaVacia()) {
        return "No hay sucursales registradas.\n";
    }

    stringstream s;
    s << "\n===== LISTADO DE SUCURSALES =====\n\n";

    nodoBase<sucursal>* actual = sucursales->retornarPrimero();
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << "\n";
        actual = actual->getSiguiente();
        i++;
    }

    return s.str();
}

bool SistemaRentACar::buscarIDEntreSucursales(int id) {
    nodoBase<sucursal>* actual = sucursales->retornarPrimero();
    while (actual != nullptr) {
        if (actual->getElemento()->getIdSucursal() == id) {
            return true;
        }
        actual = actual->getSiguiente();
    }
    return false;
}

bool SistemaRentACar::estaVacio() {
    if (sucursales->retornarPrimero() == nullptr) {
        return true;
    }
    return false;
}

string SistemaRentACar::generarCodigoSolicitud() {
    stringstream ss;
    ss << "SOL-" << contadorCodigoSolicitud;
    contadorCodigoSolicitud++;
    return ss.str();
}

string SistemaRentACar::generarCodigoContrato() {
    stringstream ss;
    ss << "CON-" << contadorCodigoContrato;
    contadorCodigoContrato++;
    return ss.str();
}

string SistemaRentACar::reporteClientesPorContratos() {
    stringstream s;
    s << "\n===== REPORTE: CLIENTES POR CANTIDAD DE CONTRATOS =====\n\n";

    // Estructura simple para almacenar cliente y cantidad de contratos
    struct ClienteContratos {
        cliente* cli;
        int cantidad;
        listaBase<string>* codigosContratos;
    };

    // Lista temporal para almacenar datos
    listaBase<ClienteContratos>* clientesConConteo = new listaBase<ClienteContratos>();

    // Recorrer todas las sucursales
    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();
    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();

        // Recorrer contratos de la sucursal
        nodoBase<contratoAlquiler>* actualCon = suc->mostrarContratos() != "No hay contratos registrados.\n"
            ? nullptr : nullptr; // Esta lógica necesita acceso directo a la lista

        actualSuc = actualSuc->getSiguiente();
    }

    s << "Nota: Para implementar completamente este reporte se necesita\n";
    s << "acceso directo a las listas de contratos de cada sucursal.\n";

    delete clientesConConteo;
    return s.str();
}

string SistemaRentACar::reporteAlquileresPorColaborador(string cedulaColaborador) {
    stringstream s;
    s << "\n===== REPORTE: ALQUILERES POR COLABORADOR =====\n";
    s << "Cedula del colaborador: " << cedulaColaborador << "\n\n";

    bool encontrado = false;

    // Buscar en todas las sucursales
    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();
    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();

        // Buscar el colaborador en esta sucursal
        colaborador* col = suc->getConjuntoColaboradores()->buscarColaborador(cedulaColaborador);

        if (col != nullptr) {
            s << "Colaborador encontrado: " << col->getNombre() << "\n";
            s << "Sucursal: " << suc->getNombre() << "\n\n";
            encontrado = true;

            s << "Contratos realizados:\n";
            // Aquí necesitaríamos recorrer los contratos y filtrar por colaborador
            s << "(Se necesita implementar acceso a contratos por colaborador)\n";
        }

        actualSuc = actualSuc->getSiguiente();
    }

    if (!encontrado) {
        s << "No se encontro colaborador con esa cedula.\n";
    }

    return s.str();
}