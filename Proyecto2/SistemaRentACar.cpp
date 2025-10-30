#include "SistemaRentACar.h"

SistemaRentACar::SistemaRentACar() {
    sucursales = new listaBase<sucursal>();
}

SistemaRentACar::~SistemaRentACar() {
    delete sucursales;
}

// ==================== GESTION DE SUCURSALES ====================

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
                // Eliminar el primero
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

// ==================== REPORTES GLOBALES ====================

string SistemaRentACar::reporteHistorialCliente(const string& idCliente) {
    stringstream s;
    s << "\n========================================\n";
    s << "  HISTORIAL DEL CLIENTE " << idCliente << "\n";
    s << "========================================\n\n";

    cliente* clienteEncontrado = nullptr;
    string nombreCliente = "";

    // 1. Buscar cliente en todas las sucursales
    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();
    while (actualSuc != nullptr && clienteEncontrado == nullptr) {
        sucursal* suc = actualSuc->getElemento();
        clienteEncontrado = suc->getClientes()->buscarClientePorCedula(idCliente);
        if (clienteEncontrado != nullptr) {
            nombreCliente = clienteEncontrado->getNombre();
        }
        actualSuc = actualSuc->getSiguiente();
    }

    if (clienteEncontrado == nullptr) {
        s << "Cliente no encontrado en el sistema.\n";
        return s.str();
    }

    s << "Cliente: " << nombreCliente << "\n";
    s << "Cedula: " << idCliente << "\n";
    s << "Pais: " << clienteEncontrado->getPaisResidencia() << "\n\n";

    // Verificar si es persona juridica
    personaJuridica* pj = dynamic_cast<personaJuridica*>(clienteEncontrado);
    if (pj != nullptr) {
        s << "Tipo: Persona Juridica\n";
        s << "Actividad Economica: " << pj->getActividadEconomica() << "\n";
        s << "Descuento: " << pj->getPorcDescuento() << "%\n\n";
    }
    else {
        s << "Tipo: Persona Fisica\n\n";
    }

    s << "========================================\n";
    s << "         SOLICITUDES Y CONTRATOS        \n";
    s << "========================================\n\n";

    int totalSolicitudes = 0;
    int totalContratos = 0;
    double montoTotal = 0.0;

    // 2. Recorrer TODAS las sucursales buscando solicitudes y contratos
    actualSuc = sucursales->retornarPrimero();
    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();

        // --- Buscar SOLICITUDES ---
        listaBase<solicitudAlquiler>* listaSolicitudes = suc->getSolicitudes();
        nodoBase<solicitudAlquiler>* actualSol = listaSolicitudes->retornarPrimero();

        while (actualSol != nullptr) {
            solicitudAlquiler* sol = actualSol->getElemento();

            if (sol->getCliente() != nullptr &&
                sol->getCliente()->getCedula() == idCliente) {

                s << "[SOLICITUD] Codigo: " << sol->getCodigo() << "\n";
                s << "  Sucursal: " << suc->getNombre() << "\n";

                if (sol->getVehiculo() != nullptr) {
                    s << "  Vehiculo: " << sol->getVehiculo()->getPlaca()
                        << " (" << sol->getVehiculo()->getMarca() << ")\n";
                }

                s << "  Estado: " << sol->getEstado() << "\n";
                s << "  Fecha inicio: " << sol->getFechaInicio() << "\n";
                s << "  Fecha entrega: " << sol->getFechaEntrega() << "\n";
                s << "  Precio total: $" << sol->getPrecioTotal() << "\n\n";

                totalSolicitudes++;
            }
            actualSol = actualSol->getSiguiente();
        }

        // --- Buscar CONTRATOS ---
        listaBase<contratoAlquiler>* listaContratos = suc->getContratos();
        nodoBase<contratoAlquiler>* actualCont = listaContratos->retornarPrimero();

        while (actualCont != nullptr) {
            contratoAlquiler* cont = actualCont->getElemento();

            if (cont->getCliente() != nullptr &&
                cont->getCliente()->getCedula() == idCliente) {

                s << "[CONTRATO] Codigo: " << cont->getCodigo() << "\n";
                s << "  Sucursal: " << suc->getNombre() << "\n";

                if (cont->getVehiculo() != nullptr) {
                    s << "  Vehiculo: " << cont->getVehiculo()->getPlaca()
                        << " (" << cont->getVehiculo()->getMarca() << ")\n";
                }

                s << "  Estado: " << cont->getEstadoContrato() << "\n";
                s << "  Dias contratados: " << cont->getDias() << "\n";

                if (cont->getDiasRealesUso() > 0) {
                    s << "  Dias reales de uso: " << cont->getDiasRealesUso() << "\n";
                }

                s << "  Fecha inicio: " << cont->getFechaInicio() << "\n";
                s << "  Fecha entrega: " << cont->getFechaEntrega() << "\n";
                s << "  Precio total: $" << cont->getPrecioTotal() << "\n";

                if (cont->getDiasRealesUso() > 0) {
                    s << "  Monto final: $" << cont->calcularMontoFinal() << "\n";
                    montoTotal += cont->calcularMontoFinal();
                }
                else {
                    montoTotal += cont->getPrecioTotal();
                }

                s << "\n";
                totalContratos++;
            }
            actualCont = actualCont->getSiguiente();
        }

        actualSuc = actualSuc->getSiguiente();
    }

    // 3. Resumen final
    s << "========================================\n";
    s << "              RESUMEN                   \n";
    s << "========================================\n";
    s << "Total solicitudes: " << totalSolicitudes << "\n";
    s << "Total contratos: " << totalContratos << "\n";
    s << "Monto total facturado: $" << montoTotal << "\n";
    s << "========================================\n";

    return s.str();
}

string SistemaRentACar::reporteClientesPorContratos() {
    stringstream s;
    s << "\n========================================\n";
    s << "  CLIENTES POR CANTIDAD DE CONTRATOS    \n";
    s << "========================================\n\n";

    // Estructura para almacenar información de clientes
    struct ClienteConteo {
        cliente* cli;
        int cantidadContratos;
        string codigosContratos;
        string nombreSucursal;
    };

    // Array dinámico para almacenar hasta 200 clientes
    ClienteConteo* clientesArray = new ClienteConteo[200];
    int totalClientes = 0;

    // 1. FASE 1: Recolectar todos los clientes únicos del sistema
    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();

    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();
        carteraClientes* cartera = suc->getClientes();

        // Recorrer clientes de esta sucursal
        nodoBase<cliente>* actualCli = cartera->retornarPrimero();

        while (actualCli != nullptr) {
            cliente* cli = actualCli->getElemento();

            // Verificar si el cliente ya está en el array
            bool existe = false;
            for (int i = 0; i < totalClientes; i++) {
                if (clientesArray[i].cli->getCedula() == cli->getCedula()) {
                    existe = true;
                    break;
                }
            }

            // Si no existe, agregarlo
            if (!existe && totalClientes < 200) {
                clientesArray[totalClientes].cli = cli;
                clientesArray[totalClientes].cantidadContratos = 0;
                clientesArray[totalClientes].codigosContratos = "";
                clientesArray[totalClientes].nombreSucursal = suc->getNombre();
                totalClientes++;
            }

            actualCli = actualCli->getSiguiente();
        }

        actualSuc = actualSuc->getSiguiente();
    }

    // 2. FASE 2: Contar contratos para cada cliente
    for (int i = 0; i < totalClientes; i++) {
        stringstream codigosStream;
        int conteo = 0;

        // Recorrer todas las sucursales
        nodoBase<sucursal>* suc = sucursales->retornarPrimero();

        while (suc != nullptr) {
            sucursal* sucActual = suc->getElemento();
            listaBase<contratoAlquiler>* contratos = sucActual->getContratos();

            // Recorrer contratos de esta sucursal
            nodoBase<contratoAlquiler>* actualCont = contratos->retornarPrimero();

            while (actualCont != nullptr) {
                contratoAlquiler* cont = actualCont->getElemento();

                // Si el contrato pertenece a este cliente
                if (cont->getCliente() != nullptr &&
                    cont->getCliente()->getCedula() == clientesArray[i].cli->getCedula()) {

                    conteo++;

                    if (conteo > 1) {
                        codigosStream << ", ";
                    }
                    codigosStream << cont->getCodigo();
                }

                actualCont = actualCont->getSiguiente();
            }

            suc = suc->getSiguiente();
        }

        clientesArray[i].cantidadContratos = conteo;
        clientesArray[i].codigosContratos = codigosStream.str();
    }

    // 3. FASE 3: ORDENAR por cantidad de contratos (Bubble Sort descendente)
    for (int i = 0; i < totalClientes - 1; i++) {
        for (int j = 0; j < totalClientes - i - 1; j++) {
            if (clientesArray[j].cantidadContratos < clientesArray[j + 1].cantidadContratos) {
                // Swap
                ClienteConteo temp = clientesArray[j];
                clientesArray[j] = clientesArray[j + 1];
                clientesArray[j + 1] = temp;
            }
        }
    }

    // 4. FASE 4: Mostrar resultados ordenados
    if (totalClientes == 0) {
        s << "No hay clientes registrados en el sistema.\n";
    }
    else {
        s << "Total de clientes: " << totalClientes << "\n";
        s << "Ordenados por cantidad de contratos (mayor a menor)\n\n";

        for (int i = 0; i < totalClientes; i++) {
            s << (i + 1) << ". ";
            s << "ID: " << clientesArray[i].cli->getCedula() << " | ";
            s << "Nombre: " << clientesArray[i].cli->getNombre() << "\n";
            s << "   Sucursal: " << clientesArray[i].nombreSucursal << "\n";
            s << "   Total de contratos: " << clientesArray[i].cantidadContratos << "\n";

            if (clientesArray[i].cantidadContratos > 0) {
                s << "   Codigos: " << clientesArray[i].codigosContratos << "\n";
            }
            else {
                s << "   (Sin contratos)\n";
            }

            s << "\n";
        }
    }

    s << "========================================\n";

    // Liberar memoria
    delete[] clientesArray;

    return s.str();
}

// ==================== TRASLADO DE VEHICULOS ====================

bool SistemaRentACar::trasladarVehiculo(const string& placa, int idSucursalOrigen, int idSucursalDestino) {
    sucursal* origen = buscarSucursal(idSucursalOrigen);
    sucursal* destino = buscarSucursal(idSucursalDestino);

    if (origen == nullptr || destino == nullptr) {
        return false;
    }

    if (idSucursalOrigen == idSucursalDestino) {
        return false; // No se puede trasladar a la misma sucursal
    }

    // Buscar el vehículo en la sucursal origen
    vehiculo* v = origen->getVehiculos()->buscarVehiculoPorPlaca(placa);

    if (v == nullptr) {
        return false; // Vehículo no encontrado
    }

    if (v->getEstado() == "Alquilado") {
        return false; // No se puede trasladar vehículo alquilado
    }

    // Eliminar de sucursal origen (libera espacio en plantel)
    if (!origen->eliminarVehiculoDeSucursal(placa)) {
        return false;
    }

    // Buscar plantel con más espacios en destino
    plantel* plantelDestino = destino->encontrarPlantelConMasEspacios();

    if (plantelDestino == nullptr || plantelDestino->estaLleno()) {
        // Revertir: agregar de vuelta a origen (esto requeriría lógica adicional)
        return false;
    }

    // Obtener recomendaciones de espacios
    vector<string> recomendaciones = plantelDestino->recomendarEspacios();

    if (recomendaciones.empty()) {
        return false;
    }
    return true;
}