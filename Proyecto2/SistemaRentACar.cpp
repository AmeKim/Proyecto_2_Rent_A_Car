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

    listaBase<ClienteConteo>* listaClientes = new listaBase<ClienteConteo>();

    // 1. FASE 1: Recolectar todos los clientes únicos del sistema
    nodoBase<sucursal>* actualSuc = sucursales->retornarPrimero();

    while (actualSuc != nullptr) {
        sucursal* suc = actualSuc->getElemento();
        carteraClientes* cartera = suc->getClientes();

        // Recorrer clientes de esta sucursal
        nodoBase<cliente>* actualCli = cartera->retornarPrimero();

        while (actualCli != nullptr) {
            cliente* cli = actualCli->getElemento();

            // Verificar si el cliente ya está en la lista
            bool existe = false;
            nodoBase<ClienteConteo>* temp = listaClientes->retornarPrimero();

            while (temp != nullptr) {
                if (temp->getElemento()->cli->getCedula() == cli->getCedula()) {
                    existe = true;
                    break;
                }
                temp = temp->getSiguiente();
            }

            // Si no existe, agregarlo
            if (!existe) {
                ClienteConteo* nuevoConteo = new ClienteConteo();
                nuevoConteo->cli = cli;
                nuevoConteo->cantidadContratos = 0;
                nuevoConteo->codigosContratos = "";
                nuevoConteo->nombreSucursal = suc->getNombre();
                listaClientes->agregarFinal(nuevoConteo);
            }

            actualCli = actualCli->getSiguiente();
        }

        actualSuc = actualSuc->getSiguiente();
    }

    // 2. FASE 2: Contar contratos para cada cliente
    nodoBase<ClienteConteo>* nodoCliente = listaClientes->retornarPrimero();

    while (nodoCliente != nullptr) {
        ClienteConteo* clienteActual = nodoCliente->getElemento();
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
                    cont->getCliente()->getCedula() == clienteActual->cli->getCedula()) {

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

        clienteActual->cantidadContratos = conteo;
        clienteActual->codigosContratos = codigosStream.str();

        nodoCliente = nodoCliente->getSiguiente();
    }

    // 3. FASE 3: ORDENAR por cantidad de contratos (Bubble Sort descendente)
    if (!listaClientes->estaVacia()) {
        nodoBase<ClienteConteo>* i = listaClientes->retornarPrimero();

        while (i != nullptr) {
            nodoBase<ClienteConteo>* j = i->getSiguiente();

            while (j != nullptr) {
                if (j->getElemento()->cantidadContratos > i->getElemento()->cantidadContratos) {
                    // Intercambiar elementos
                    ClienteConteo temp = *(i->getElemento());
                    *(i->getElemento()) = *(j->getElemento());
                    *(j->getElemento()) = temp;
                }
                j = j->getSiguiente();
            }
            i = i->getSiguiente();
        }
    }

    // 4. FASE 4: Mostrar resultados ordenados
    if (listaClientes->estaVacia()) {
        s << "No hay clientes registrados en el sistema.\n";
    }
    else {
        s << "Total de clientes: " << listaClientes->getCantidad() << "\n";
        s << "Ordenados por cantidad de contratos (mayor a menor)\n\n";

        nodoBase<ClienteConteo>* actual = listaClientes->retornarPrimero();
        int i = 1;

        while (actual != nullptr) {
            ClienteConteo* c = actual->getElemento();

            s << i << ". ";
            s << "ID: " << c->cli->getCedula() << " | ";
            s << "Nombre: " << c->cli->getNombre() << "\n";
            s << "   Sucursal: " << c->nombreSucursal << "\n";
            s << "   Total de contratos: " << c->cantidadContratos << "\n";

            if (c->cantidadContratos > 0) {
                s << "   Codigos: " << c->codigosContratos << "\n";
            }
            else {
                s << "   (Sin contratos)\n";
            }

            s << "\n";

            actual = actual->getSiguiente();
            i++;
        }
    }

    s << "========================================\n";

    // Liberar memoria
    delete listaClientes;

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
        // No hay espacio en destino
        return false;
    }

    // Obtener recomendaciones de espacios
    listaBase<string>* recomendaciones = plantelDestino->recomendarEspacios();

    if (recomendaciones->estaVacia()) {
        delete recomendaciones;
        return false;
    }

    // Aquí deberías implementar la lógica para:
    // 1. Seleccionar un espacio de las recomendaciones
    // 2. Agregar el vehículo al plantel destino en ese espacio
    // Por ahora, solo limpiamos y retornamos true como ejemplo básico

    delete recomendaciones;
    return true;
}