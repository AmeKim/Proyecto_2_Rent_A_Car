#include "controller.h"

controller::controller() {
    sucursales = new SistemaRentACar();
}

controller::~controller() {
    delete sucursales;
}

int controller::iniciarSistema() {
    int opcion = 0;

    do {
        opcion = Interfaz::menuPrincipal();

        switch (opcion) {
        case 1:
            gestionarSucursales();
            break;
        case 2:
            gestionarClientes();
            break;
        case 3:
            gestionarColaboradores();
            break;
        case 4:
            gestionarVehiculos();
            break;
        case 5:
            gestionarSolicitudes();
            break;
        case 0:
            Interfaz::imprimirMensaje("Saliendo del sistema...\n");
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida. Intente de nuevo.\n");
            limpiarEnter();
        }
    } while (opcion != 0);

    return 0;
}

void controller::gestionarSucursales() {
    int opcion = 0;

    do {
        opcion = Interfaz::submenuSucursal();

        switch (opcion) {
        case 1: { // Agregar Sucursal
            limpiar();
            Interfaz::imprimirTitulo("AGREGAR SUCURSAL");
            sucursal* nuevaSucursal = Interfaz::capturarDatosSucursal();

            if (sucursales->buscarSucursal(nuevaSucursal->getId()) != nullptr) {
                Interfaz::imprimirMensaje("Error: Ya existe una sucursal con ese ID.\n");
                delete nuevaSucursal;
            }
            else {
                sucursales->agregarSucursal(nuevaSucursal);
                Interfaz::imprimirMensaje("Sucursal agregada exitosamente.\n");
            }
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Sucursales
            limpiar();
            Interfaz::imprimirTitulo("LISTADO DE SUCURSALES");
            cout << sucursales->mostrarSucursales();
            limpiarEnter();
            break;
        }
        case 3: { // Eliminar Sucursal
            limpiar();
            Interfaz::imprimirTitulo("ELIMINAR SUCURSAL");
            int id = Interfaz::solicitarIDSucursal();

            if (sucursales->eliminarSucursal(id)) {
                Interfaz::imprimirMensaje("Sucursal eliminada exitosamente.\n");
            }
            else {
                Interfaz::imprimirMensaje("Error: No se encontro la sucursal.\n");
            }
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.\n");
            limpiarEnter();
        }
    } while (opcion != 0);
}

void controller::gestionarColaboradores() {
    int opcion = 0;

    do {
        opcion = Interfaz::submenuColaborador();

        switch (opcion) {
        case 1: { // Agregar Colaborador
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirTitulo("AGREGAR COLABORADOR");
            colaborador* nuevoColab = Interfaz::capturarDatosColaborador();

            if (suc->getColaboradores()->buscarColaborador(nuevoColab->getCedula()) != nullptr) {
                Interfaz::imprimirMensaje("Error: Ya existe un colaborador con ese ID.\n");
                delete nuevoColab;
            }
            else {
                suc->agregarColaborador(nuevoColab);
                Interfaz::imprimirMensaje("Colaborador agregado exitosamente.\n");
            }
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Colaborador
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            string id = Interfaz::solicitarIDColaborador();
            colaborador* col = suc->getColaboradores()->buscarColaborador(id);

            if (col != nullptr) {
                limpiar();
                Interfaz::imprimirTitulo("DATOS DEL COLABORADOR");
                cout << col->toString();
            }
            else {
                Interfaz::imprimirMensaje("Colaborador no encontrado.\n");
            }
            limpiarEnter();
            break;
        }
        case 3: { // Eliminar Colaborador
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            string id = Interfaz::solicitarIDColaborador();

            if (suc->eliminarColaborador(id)) {
                Interfaz::imprimirMensaje("Colaborador eliminado exitosamente.\n");
            }
            else {
                Interfaz::imprimirMensaje("Error: No se encontro el colaborador.\n");
            }
            limpiarEnter();
            break;
        }
        case 4: { // Reportes por Colaborador
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            string id = Interfaz::solicitarIDColaborador();
            cout << suc->reporteAlquileresPorColaborador(id);
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.\n");
            limpiarEnter();
        }
    } while (opcion != 0);
}

void controller::gestionarVehiculos() {
    int opcion = 0;

    do {
        opcion = Interfaz::submenuVehiculosYPlanteles();

        switch (opcion) {
        case 1: { // Agregar Plantel
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirTitulo("CREAR PLANTEL");
            print("Ingrese el nombre del plantel (letra): ");
            string nombre = digPalabra();

            print("Ingrese el tipo de plantel:\n");
            print("(1) Techado y asfaltado\n");
            print("(2) Techado y lastreado\n");
            print("(3) Asfaltado\n");
            print("(4) Lastreado\n");
            print("Tipo: ");
            int tipo = digNum();

            print("Ingrese la cantidad de filas: ");
            int filas = digNum();
            print("Ingrese la cantidad de columnas: ");
            int columnas = digNum();

            plantel* nuevoPlantel = new plantel(nombre, tipo, filas, columnas);
            suc->agregarPlantel(nuevoPlantel);

            limpiar();
            cout << nuevoPlantel->mostrarGrafico();
            Interfaz::imprimirMensaje("\nPlantel creado exitosamente.\n");
            limpiarEnter();
            break;
        }
        case 2: { // Visualizar Plantel
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese el nombre del plantel: ");
            string nombre = digPalabra();
            plantel* p = suc->buscarPlantel(nombre);

            if (p != nullptr) {
                limpiar();
                cout << p->mostrarGrafico();
            }
            else {
                Interfaz::imprimirMensaje("Plantel no encontrado.\n");
            }
            limpiarEnter();
            break;
        }
        case 3: { // Agregar Vehículo
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirTitulo("AGREGAR VEHICULO");
            print("Ingrese la placa: ");
            string placa = digPalabra();
            print("Ingrese el modelo: ");
            string modelo = digPalabra();
            print("Ingrese la marca: ");
            string marca = digPalabra();
            print("Ingrese el tipo de licencia requerida: ");
            string tipoLic = digPalabra();
            print("Ingrese el precio por dia: ");
            double precio = digDouble();
            print("Ingrese la categoria (A/B/C/D): ");
            string catStr = digPalabra();
            char categoria = catStr[0];
            print("Ingrese el plantel: ");
            string nombrePlantel = digPalabra();

            vehiculo* nuevoVehiculo = new vehiculo(placa, modelo, marca, tipoLic,
                precio, "Revision", categoria, nombrePlantel);
            suc->agregarVehiculo(nuevoVehiculo);

            Interfaz::imprimirMensaje("Vehiculo agregado exitosamente en estado Revision.\n");
            limpiarEnter();
            break;
        }
        case 4: { // Visualizar Vehículo
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            cout << suc->mostrarVehiculos();
            limpiarEnter();
            break;
        }
        case 5: { // Eliminar Vehículo
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la placa del vehiculo a eliminar: ");
            string placa = digPalabra();

            vehiculo* v = suc->buscarVehiculo(placa);
            if (v != nullptr && v->getEstado() == "Alquilado") {
                Interfaz::imprimirMensaje("Error: No se puede eliminar un vehiculo alquilado.\n");
            }
            else if (suc->eliminarVehiculo(placa)) {
                Interfaz::imprimirMensaje("Vehiculo eliminado exitosamente.\n");
            }
            else {
                Interfaz::imprimirMensaje("Error: Vehiculo no encontrado.\n");
            }
            limpiarEnter();
            break;
        }
        case 6: { // Reasignar Vehículo en Plantel
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirTitulo("REASIGNAR VEHICULO EN PLANTEL");

            print("Ingrese la placa del vehiculo a reasignar: ");
            string placa = digPalabra();
            vehiculo* v = suc->buscarVehiculo(placa);

            if (v == nullptr) {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.\n");
                limpiarEnter();
                break;
            }

            if (v->getEstado() == "Alquilado") {
                Interfaz::imprimirMensaje("Error: No se puede reasignar un vehiculo alquilado.\n");
                limpiarEnter();
                break;
            }

            limpiar();
            cout << "Vehiculo actual: " << v->toString() << "\n";
            cout << "Ubicacion actual: Plantel " << v->getUbicacionPlantel() << "\n\n";

            // Mostrar planteles disponibles
            print("Planteles disponibles:\n");
            cout << suc->mostrarPlanteles() << "\n";

            print("Ingrese el nombre del nuevo plantel: ");
            string nombrePlantel = digPalabra();

            plantel* plantelNuevo = suc->buscarPlantel(nombrePlantel);
            if (plantelNuevo == nullptr) {
                Interfaz::imprimirMensaje("Plantel no encontrado.\n");
                limpiarEnter();
                break;
            }

            // Liberar espacio actual si está en un plantel
            if (!v->getUbicacionPlantel().empty()) {
                plantel* plantelActual = suc->buscarPlantel(v->getUbicacionPlantel());
                if (plantelActual != nullptr) {
                    // Buscar y liberar el espacio actual
                    for (int i = 0; i < plantelActual->getEspacios()->getFilas(); i++) {
                        for (int j = 0; j < plantelActual->getEspacios()->getColumnas(); j++) {
                            espacioEstacionamiento* esp = static_cast<espacioEstacionamiento*>(
                                plantelActual->getEspacios()->getValor(i, j));
                            if (esp != nullptr && esp->getVehiculo() == v) {
                                esp->liberarEspacio();
                            }
                        }
                    }
                }
            }

            // Mostrar nuevo plantel con espacios recomendados
            limpiar();
            cout << plantelNuevo->mostrarGrafico();

            listaBase<string>* recomendaciones = plantelNuevo->recomendarEspacios();
            if (!recomendaciones->estaVacia()) {
                cout << "\n=== ESPACIOS RECOMENDADOS ===\n";
                recomendaciones->reiniciar();
                string* espacio = recomendaciones->siguiente();
                int numRec = 1;
                while (espacio != nullptr && numRec <= 3) {
                    cout << numRec << ". " << *espacio << endl;
                    espacio = recomendaciones->siguiente();
                    numRec++;
                }
            }
            delete recomendaciones;

            print("\nIngrese el codigo del nuevo espacio de estacionamiento: ");
            string codigoEspacio = digPalabra();

            if (plantelNuevo->asignarEspacioManual(codigoEspacio, v)) {
                v->setUbicacionPlantel(nombrePlantel);
                Interfaz::imprimirMensaje("Vehiculo reasignado exitosamente.\n");
            }
            else {
                Interfaz::imprimirMensaje("Error: No se pudo asignar el espacio (puede estar ocupado).\n");
            }

            limpiarEnter();
            break;
        }
        case 7: { // Cambiar Estado de Vehículo
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();
            vehiculo* v = suc->buscarVehiculo(placa);

            if (v == nullptr) {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.\n");
                limpiarEnter();
                break;
            }

            limpiar();
            cout << "Estado actual: " << v->getEstado() << "\n\n";
            print("Ingrese el nuevo estado:\n");
            print("(1) Disponible\n(2) Alquilado\n(3) Devuelto\n(4) Revision\n(5) Lavado\n");
            print("Opcion: ");
            int est = digNum();

            string nuevoEstado;
            switch (est) {
            case 1: nuevoEstado = "Disponible"; break;
            case 2: nuevoEstado = "Alquilado"; break;
            case 3: nuevoEstado = "Devuelto"; break;
            case 4: nuevoEstado = "Revision"; break;
            case 5: nuevoEstado = "Lavado"; break;
            default:
                Interfaz::imprimirMensaje("Estado invalido.\n");
                limpiarEnter();
                continue;
            }

            print("Ingrese la fecha del cambio (DD/MM/AAAA): ");
            string fecha = digPalabra();
            string idColab = Interfaz::solicitarIDColaborador();
            colaborador* col = suc->getColaboradores()->buscarColaborador(idColab);

            if (col == nullptr) {
                Interfaz::imprimirMensaje("Colaborador no encontrado.\n");
                limpiarEnter();
                break;
            }

            if (v->cambiarEstado(nuevoEstado, fecha, col)) {
                Interfaz::imprimirMensaje("Estado cambiado exitosamente.\n");
            }
            else {
                Interfaz::imprimirMensaje("Error: Cambio de estado no permitido.\n");
            }
            limpiarEnter();
            break;
        }
        case 8: { // Estados de vehículo específico
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();
            vehiculo* v = suc->buscarVehiculo(placa);

            if (v != nullptr) {
                limpiar();
                cout << v->mostrarBitacora();
            }
            else {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.\n");
            }
            limpiarEnter();
            break;
        }
        case 9: { // Reporte de ocupación
            limpiar();
            cout << sucursales->reporteOcupacionPlanteles();
            limpiarEnter();
            break;
        }
        case 10: { // Traslado de vehículos (OPCIONAL)
            limpiar();
            Interfaz::imprimirTitulo("TRASLADO DE VEHICULOS ENTRE SUCURSALES");

            cout << "=== SUCURSAL ORIGEN ===\n";
            cout << sucursales->mostrarSucursales();
            print("\nIngrese el ID de la sucursal origen: ");
            int idOrigen = digNum();

            sucursal* sucOrigen = sucursales->buscarSucursal(idOrigen);
            if (sucOrigen == nullptr) {
                Interfaz::imprimirMensaje("Sucursal origen no encontrada.\n");
                limpiarEnter();
                break;
            }

            limpiar();
            cout << "=== SUCURSAL DESTINO ===\n";
            cout << sucursales->mostrarSucursales();
            print("\nIngrese el ID de la sucursal destino: ");
            int idDestino = digNum();

            sucursal* sucDestino = sucursales->buscarSucursal(idDestino);
            if (sucDestino == nullptr) {
                Interfaz::imprimirMensaje("Sucursal destino no encontrada.\n");
                limpiarEnter();
                break;
            }

            if (idOrigen == idDestino) {
                Interfaz::imprimirMensaje("Error: No se puede trasladar a la misma sucursal.\n");
                limpiarEnter();
                break;
            }

            // Mostrar vehículos disponibles para traslado
            limpiar();
            listaBase<vehiculo>* vehiculosDisp = sucOrigen->obtenerVehiculosDisponiblesParaTraslado();

            if (vehiculosDisp->estaVacia()) {
                Interfaz::imprimirMensaje("No hay vehiculos disponibles para trasladar.\n");
                delete vehiculosDisp;
                limpiarEnter();
                break;
            }

            cout << "\n=== VEHICULOS DISPONIBLES PARA TRASLADO ===\n";
            cout << "(Solo vehiculos NO alquilados)\n\n";

            vehiculosDisp->reiniciar();
            vehiculo* v = vehiculosDisp->siguiente();
            int contador = 1;

            while (v != nullptr) {
                cout << contador << ". " << v->toString() << endl;
                v = vehiculosDisp->siguiente();
                contador++;
            }

            print("\nIngrese la cantidad de vehiculos a trasladar: ");
            int cantidad = digNum();

            if (cantidad <= 0 || cantidad > vehiculosDisp->getCantidad()) {
                Interfaz::imprimirMensaje("Cantidad invalida.\n");
                delete vehiculosDisp;
                limpiarEnter();
                break;
            }

            // Crear lista temporal para almacenar los vehículos a trasladar
            listaBase<vehiculo>* vehiculosATraslado = new listaBase<vehiculo>();

            vehiculosDisp->reiniciar();
            for (int i = 0; i < cantidad; i++) {
                vehiculo* vTras = vehiculosDisp->siguiente();
                if (vTras != nullptr) {
                    vehiculosATraslado->agregarFinal(vTras);
                }
            }

            delete vehiculosDisp;

            // Proceso de traslado vehiculo por vehiculo
            vehiculosATraslado->reiniciar();
            vehiculo* vActual = vehiculosATraslado->siguiente();
            int trasladados = 0;

            while (vActual != nullptr) {
                limpiar();
                cout << "\n=== TRASLADANDO VEHICULO " << (trasladados + 1) << " de " << cantidad << " ===\n";
                cout << "Vehiculo: " << vActual->toString() << "\n\n";

                // Seleccionar plantel destino
                print("Planteles disponibles en sucursal destino:\n");
                cout << sucDestino->mostrarPlanteles() << "\n";

                print("Ingrese el nombre del plantel destino: ");
                string nombrePlantel = digPalabra();

                plantel* plantelDest = sucDestino->buscarPlantel(nombrePlantel);
                if (plantelDest == nullptr) {
                    Interfaz::imprimirMensaje("Plantel no encontrado. Saltando vehiculo.\n");
                    limpiarEnter();
                    vActual = vehiculosATraslado->siguiente();
                    continue;
                }

                // Mostrar espacios recomendados
                limpiar();
                cout << plantelDest->mostrarGrafico();

                listaBase<string>* recomendaciones = plantelDest->recomendarEspacios();
                if (!recomendaciones->estaVacia()) {
                    cout << "\n=== ESPACIOS RECOMENDADOS ===\n";
                    recomendaciones->reiniciar();
                    string* espacio = recomendaciones->siguiente();
                    int numRec = 1;
                    while (espacio != nullptr && numRec <= 3) {
                        cout << numRec << ". " << *espacio << endl;
                        espacio = recomendaciones->siguiente();
                        numRec++;
                    }
                }
                delete recomendaciones;

                print("\nIngrese el codigo del espacio de estacionamiento: ");
                string codigoEspacio = digPalabra();

                // Remover de sucursal origen
                if (sucOrigen->removerVehiculo(vActual)) {
                    // Agregar a sucursal destino
                    if (sucDestino->agregarVehiculoDeTraslado(vActual, nombrePlantel, codigoEspacio)) {
                        trasladados++;
                        Interfaz::imprimirMensaje("Vehiculo trasladado exitosamente.\n");
                    }
                    else {
                        // Si falla, devolver a sucursal origen
                        sucOrigen->agregarVehiculo(vActual);
                        Interfaz::imprimirMensaje("Error al asignar espacio. Vehiculo no trasladado.\n");
                    }
                }
                else {
                    Interfaz::imprimirMensaje("Error al remover vehiculo de origen.\n");
                }

                limpiarEnter();
                vActual = vehiculosATraslado->siguiente();
            }

            delete vehiculosATraslado;

            limpiar();
            cout << "\n=== RESUMEN DEL TRASLADO ===\n";
            cout << "Vehiculos trasladados exitosamente: " << trasladados << " de " << cantidad << endl;
            cout << "De: " << sucOrigen->getNombre() << " (ID: " << idOrigen << ")\n";
            cout << "A: " << sucDestino->getNombre() << " (ID: " << idDestino << ")\n";

            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.\n");
            limpiarEnter();
        }
    } while (opcion != 0);
}

void controller::gestionarSolicitudes() {
    int opcion = 0;

    do {
        opcion = Interfaz::submenuSolicitudesYContratos();

        switch (opcion) {
        case 1: { // Crear Solicitud
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirTitulo("CREAR SOLICITUD DE ALQUILER");
            print("Ingrese el codigo de la solicitud: ");
            string codigo = digPalabra();

            print("Ingrese la cedula del cliente: ");
            string cedCli = digPalabra();
            cliente* cli = suc->getClientes()->buscarClientePorCedula(cedCli);

            if (cli == nullptr) {
                Interfaz::imprimirMensaje("Cliente no encontrado.\n");
                limpiarEnter();
                break;
            }

            string cedCol = Interfaz::solicitarIDColaborador();
            colaborador* col = suc->getColaboradores()->buscarColaborador(cedCol);

            if (col == nullptr) {
                Interfaz::imprimirMensaje("Colaborador no encontrado.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();
            vehiculo* veh = suc->buscarVehiculo(placa);

            if (veh == nullptr) {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la cantidad de dias: ");
            int dias = digNum();
            print("Ingrese la fecha de inicio (DD/MM/AAAA): ");
            string fInicio = digPalabra();
            print("Ingrese la fecha de entrega (DD/MM/AAAA): ");
            string fEntrega = digPalabra();

            double precioDia = veh->getPrecio();

            solicitudAlquiler* sol = new solicitudAlquiler(codigo, cli, col, veh,
                dias, fInicio, fEntrega, precioDia);
            suc->agregarSolicitud(sol);

            Interfaz::imprimirMensaje("Solicitud creada exitosamente.\n");
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Solicitudes
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            cout << suc->mostrarSolicitudes();
            cout << "\n" << suc->mostrarContratos();
            limpiarEnter();
            break;
        }
        case 4: { // Aprobar/Rechazar Solicitud
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese el codigo de la solicitud: ");
            string codigo = digPalabra();
            solicitudAlquiler* sol = suc->buscarSolicitud(codigo);

            if (sol == nullptr) {
                Interfaz::imprimirMensaje("Solicitud no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("(1) Aprobar\n(2) Rechazar\nOpcion: ");
            int opt = digNum();

            if (opt == 1) {
                sol->aprobar();
                contratoAlquiler* contrato = new contratoAlquiler(*sol);
                suc->agregarContrato(contrato);
                Interfaz::imprimirMensaje("Solicitud aprobada y convertida en contrato.\n");
            }
            else if (opt == 2) {
                sol->rechazar();
                Interfaz::imprimirMensaje("Solicitud rechazada.\n");
            }
            limpiarEnter();
            break;
        }
        case 6: { // Reporte de contratos para vehículo
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();
            cout << suc->reporteContratosVehiculo(placa);
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.\n");
            limpiarEnter();
        }
    } while (opcion != 0);
}

void controller::gestionarClientes() {
    int opcion = 0;

    do {
        opcion = Interfaz::submenuClientes();

        switch (opcion) {
        case 1: { // Agregar Cliente
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirTitulo("AGREGAR CLIENTE");
            print("Tipo de cliente:\n(1) Persona Fisica\n(2) Persona Juridica\nOpcion: ");
            int tipo = digNum();

            print("Ingrese la cedula: ");
            string cedula = digPalabra();
            print("Ingrese el nombre: ");
            string nombre = digPalabra();
            print("Ingrese el pais de residencia: ");
            string pais = digPalabra();

            if (tipo == 1) {
                print("Ingrese el tipo de licencia: ");
                string tipoLic = digPalabra();
                personaFisica* pf = new personaFisica(cedula, nombre, pais, tipoLic);
                suc->agregarClienteFisico(pf);
            }
            else if (tipo == 2) {
                print("Ingrese la actividad economica: ");
                string actEco = digPalabra();
                print("Ingrese el porcentaje de descuento: ");
                float desc = digDouble();
                personaJuridica* pj = new personaJuridica(cedula, nombre, pais, actEco, desc);
                suc->agregarClienteJuridico(pj);
            }

            Interfaz::imprimirMensaje("Cliente agregado exitosamente.\n");
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Clientes
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            cout << suc->mostrarClientes();
            limpiarEnter();
            break;
        }
        case 3: { // Eliminar Cliente
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la cedula del cliente: ");
            string cedula = digPalabra();

            if (suc->eliminarCliente(cedula)) {
                Interfaz::imprimirMensaje("Cliente eliminado exitosamente.\n");
            }
            else {
                Interfaz::imprimirMensaje("Error: Cliente no encontrado.\n");
            }
            limpiarEnter();
            break;
        }
        case 4: { // Historial del Cliente
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            print("Ingrese la cedula del cliente: ");
            string cedula = digPalabra();
            cout << suc->historialCliente(cedula);
            limpiarEnter();
            break;
        }
        case 5: { // Reporte de clientes por contratos
            limpiar();
            int idSucursal = seleccionarSucursal();
            sucursal* suc = sucursales->buscarSucursal(idSucursal);

            if (suc == nullptr) {
                Interfaz::imprimirMensaje("Sucursal no encontrada.\n");
                limpiarEnter();
                break;
            }

            cout << suc->reporteClientesPorContratos();
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.\n");
            limpiarEnter();
        }
    } while (opcion != 0);
}

int controller::seleccionarSucursal() {
    cout << sucursales->mostrarSucursales();
    int id = Interfaz::solicitarIDSucursal();
    return id;
}