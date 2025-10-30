#include "controller.h"

controller::controller() {
    sistema = new SistemaRentACar();
    cargarDatosQuemados(); // Cargar datos de prueba
}

controller::~controller() {
    delete sistema;
}

void controller::cargarDatosQuemados() {
	// Crear datos de prueba
    sucursal* suc1 = new sucursal(1, "Heredia Centro", "Heredia");
    sucursal* suc2 = new sucursal(2, "San Jose Downtown", "San Jose");
    sistema->agregarSucursal(suc1);
    sistema->agregarSucursal(suc2);

    colaborador* col1 = new colaborador("Juan Perez", "101110111", "01/01/2020");
    colaborador* col2 = new colaborador("Maria Lopez", "202220222", "15/03/2021");
    suc1->getColaboradores()->agregarColaborador(col1);
    suc1->getColaboradores()->agregarColaborador(col2);

    personaFisica* pf1 = new personaFisica("303330333", "Carlos Mora", "Costa Rica", "B1");
    personaJuridica* pj1 = new personaJuridica("400440444", "Empresa ABC SA", "Costa Rica", "Tecnologia", 15.0);
    suc1->getClientes()->agregarClienteFisico(pf1);
    suc1->getClientes()->agregarClienteJuridico(pj1);

    plantel* p1 = new plantel('A', 12, 1, 3, 4);
    suc1->agregarPlantel(p1);

    vehiculo* v1 = new vehiculo("ABC123", "Corolla", "Toyota", "B1", 50.0, "Revision", 'A', "");
    vehiculo* v2 = new vehiculo("XYZ789", "Civic", "Honda", "B1", 55.0, "Revision", 'B', "");

    suc1->agregarVehiculoASucursal(v1, 'A', 0, 0);
    suc1->agregarVehiculoASucursal(v2, 'A', 0, 1);
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
            Interfaz::imprimirMensaje("Saliendo del sistema...");
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida. Intente de nuevo.");
            limpiarEnter();
        }
    } while (opcion != 0);

    return 0;
}

int controller::seleccionarSucursal() {
    limpiar();
    Interfaz::imprimirMensaje(sistema->mostrarSucursales());
    return Interfaz::solicitarIDSucursal();
}

sucursal* controller::obtenerSucursal() {
    int idSuc = seleccionarSucursal();
    sucursal* suc = sistema->buscarSucursal(idSuc);

    if (suc == nullptr) {
        Interfaz::imprimirMensaje("Sucursal no encontrada.");
        limpiarEnter();
    }

    return suc;
}

void controller::gestionarSucursales() {
    int opcion = 0;

    do {
        opcion = Interfaz::submenuSucursal();

        switch (opcion) {
        case 1: { // Agregar Sucursal
            limpiar();
            Interfaz::imprimirTitulo("AGREGAR SUCURSAL");
            sucursal* nuevaSuc = Interfaz::capturarDatosSucursal();

            if (sistema->agregarSucursal(nuevaSuc)) {
                Interfaz::imprimirMensaje("Sucursal agregada exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("Error al agregar sucursal.");
                delete nuevaSuc;
            }
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Sucursales
            limpiar();
            Interfaz::imprimirTitulo("SUCURSALES REGISTRADAS");
            Interfaz::imprimirMensaje(sistema->mostrarSucursales());
            limpiarEnter();
            break;
        }
        case 3: { // Eliminar Sucursal
            limpiar();
            Interfaz::imprimirTitulo("ELIMINAR SUCURSAL");
            Interfaz::imprimirMensaje(sistema->mostrarSucursales());
            int id = Interfaz::solicitarIDSucursal();

            if (sistema->eliminarSucursal(id)) {
                Interfaz::imprimirMensaje("Sucursal eliminada exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("No se pudo eliminar la sucursal.");
            }
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.");
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
            Interfaz::imprimirTitulo("AGREGAR COLABORADOR");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            colaborador* nuevoCol = Interfaz::capturarDatosColaborador();
            suc->getColaboradores()->agregarColaborador(nuevoCol);
            Interfaz::imprimirMensaje("Colaborador agregado exitosamente!");
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Colaboradores
            limpiar();
            Interfaz::imprimirTitulo("MOSTRAR COLABORADORES");

            sucursal* suc = obtenerSucursal();
            if (suc != nullptr) {
                Interfaz::imprimirMensaje(suc->getColaboradores()->mostrarColaboradores());
            }
            limpiarEnter();
            break;
        }
        case 3: { // Eliminar Colaborador
            limpiar();
            Interfaz::imprimirTitulo("ELIMINAR COLABORADOR");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->getColaboradores()->mostrarColaboradores());
            string idCol = Interfaz::solicitarIDColaborador();

            if (suc->getColaboradores()->eliminarColaborador(idCol)) {
                Interfaz::imprimirMensaje("Colaborador eliminado exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("No se pudo eliminar el colaborador.");
            }
            limpiarEnter();
            break;
        }
        case 4: { // Reporte por colaborador
            limpiar();
            Interfaz::imprimirTitulo("REPORTE DE ALQUILERES POR COLABORADOR");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            string idCol = Interfaz::solicitarIDColaborador();
            Interfaz::imprimirMensaje(suc->reporteAlquileresColaborador(idCol));
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.");
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
            Interfaz::imprimirTitulo("AGREGAR PLANTEL");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Ingrese la letra del plantel: ");
            char letra = digPalabra()[0];
            print("Ingrese la capacidad del plantel: ");
            int capacidad = digNum();
            print("Tipo de plantel:\n");
            print("(1) Techado y asfaltado\n");
            print("(2) Techado y lastreado\n");
            print("(3) Asfaltado\n");
            print("(4) Lastreado\n");
            print("Seleccione: ");
            int tipo = digNum();
            print("Ingrese numero de filas: ");
            int filas = digNum();
            print("Ingrese numero de columnas: ");
            int columnas = digNum();

            plantel* nuevoPlantel = new plantel(letra, capacidad, tipo, filas, columnas);
            suc->agregarPlantel(nuevoPlantel);

            limpiar();
            Interfaz::imprimirMensaje("Plantel creado exitosamente!");
            Interfaz::imprimirMensaje(nuevoPlantel->mostrarVistaGrafica());
            limpiarEnter();
            break;
        }
        case 2: { // Visualizar Plantel
            limpiar();
            Interfaz::imprimirTitulo("VISUALIZAR PLANTEL");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->mostrarPlanteles());
            print("Ingrese la letra del plantel a visualizar: ");
            char letra = digPalabra()[0];

            plantel* p = suc->buscarPlantel(letra);
            if (p != nullptr) {
                limpiar();
                Interfaz::imprimirMensaje(p->mostrarVistaGrafica());

                print("\n¿Desea ver detalles de un espacio especifico? (S/N): ");
                string resp = digPalabra();
                if (resp == "S" || resp == "s") {
                    print("Ingrese el codigo del espacio (ej: A01): ");
                    string codigo = digPalabra();
                    string placa = p->obtenerPlacaEnEspacio(codigo);
                    print("Resultado: ");
                    print(placa);
                    print("\n");
                }
            }
            else {
                Interfaz::imprimirMensaje("Plantel no encontrado.");
            }
            limpiarEnter();
            break;
        }
        case 3: { // Agregar Vehículo
            limpiar();
            Interfaz::imprimirTitulo("AGREGAR VEHICULO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Ingrese la placa: ");
            string placa = digPalabra();
            print("Ingrese la marca: ");
            string marca = digPalabra();
            print("Ingrese el modelo: ");
            string modelo = digPalabra();
            print("Ingrese tipo de licencia requerida: ");
            string licencia = digPalabra();
            print("Ingrese categoria (A/B/C/D): ");
            char cat = digPalabra()[0];
            print("Ingrese precio por dia: ");
            double precio = digDouble();

            vehiculo* nuevoVeh = new vehiculo(placa, modelo, marca, licencia,
                precio, "Revision", cat, "");

            Interfaz::imprimirMensaje(suc->mostrarPlanteles());
            plantel* plantelMasEspacios = suc->encontrarPlantelConMasEspacios();

            if (plantelMasEspacios != nullptr) {
                limpiar();
                print("Plantel recomendado: ");
                print(plantelMasEspacios->getLetra());
                print("\n\n");
                Interfaz::imprimirMensaje(plantelMasEspacios->mostrarVistaGrafica());

                vector<string> recomendaciones = plantelMasEspacios->recomendarEspacios();
                print("\nEspacios recomendados (menos vecinos ocupados):\n");
                for (size_t i = 0; i < recomendaciones.size(); i++) {
                    print((int)(i + 1));
                    print(". ");
                    print(recomendaciones[i]);
                    print("\n");
                }

                print("\nIngrese fila para estacionar: ");
                int fila = digNum();
                print("Ingrese columna para estacionar: ");
                int columna = digNum();

                if (suc->agregarVehiculoASucursal(nuevoVeh, plantelMasEspacios->getLetra(), fila, columna)) {
                    Interfaz::imprimirMensaje("\nVehiculo agregado exitosamente!");
                }
                else {
                    Interfaz::imprimirMensaje("\nError al agregar vehiculo.");
                    delete nuevoVeh;
                }
            }
            else {
                Interfaz::imprimirMensaje("No hay planteles disponibles.");
                delete nuevoVeh;
            }

            limpiarEnter();
            break;
        }
        case 4: { // Visualizar Vehículo
            limpiar();
            Interfaz::imprimirTitulo("VISUALIZAR VEHICULO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();

            vehiculo* v = suc->getVehiculos()->buscarVehiculoPorPlaca(placa);
            if (v != nullptr) {
                limpiar();
                Interfaz::imprimirMensaje("\n===== DETALLES DEL VEHICULO =====\n");
                Interfaz::imprimirMensaje(v->toString());
            }
            else {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.");
            }
            limpiarEnter();
            break;
        }
        case 5: { // Eliminar Vehículo
            limpiar();
            Interfaz::imprimirTitulo("ELIMINAR VEHICULO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->getVehiculos()->mostrarVehiculos());
            print("Ingrese la placa del vehiculo a eliminar: ");
            string placa = digPalabra();

            if (suc->eliminarVehiculoDeSucursal(placa)) {
                Interfaz::imprimirMensaje("Vehiculo eliminado exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("No se pudo eliminar el vehiculo. Verifique que no este alquilado.");
            }
            limpiarEnter();
            break;
        }
        case 6: { // Reasignar Vehículo
            limpiar();
            Interfaz::imprimirTitulo("REASIGNAR VEHICULO EN PLANTEL");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->getVehiculos()->mostrarVehiculos());
            print("Ingrese la placa del vehiculo a reubicar: ");
            string placa = digPalabra();

            vehiculo* v = suc->getVehiculos()->buscarVehiculoPorPlaca(placa);
            if (v == nullptr) {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.");
                limpiarEnter();
                break;
            }

            if (v->getEstado() == "Alquilado") {
                Interfaz::imprimirMensaje("No se puede reubicar un vehiculo alquilado.");
                limpiarEnter();
                break;
            }

            Interfaz::imprimirMensaje(suc->mostrarPlanteles());
            print("Ingrese la letra del nuevo plantel: ");
            char nuevaLetra = digPalabra()[0];

            plantel* p = suc->buscarPlantel(nuevaLetra);
            if (p != nullptr) {
                Interfaz::imprimirMensaje(p->mostrarVistaGrafica());

                print("Ingrese nueva fila: ");
                int fila = digNum();
                print("Ingrese nueva columna: ");
                int columna = digNum();

                if (suc->reubicarVehiculo(placa, nuevaLetra, fila, columna)) {
                    Interfaz::imprimirMensaje("Vehiculo reubicado exitosamente!");
                }
                else {
                    Interfaz::imprimirMensaje("Error al reubicar vehiculo.");
                }
            }
            else {
                Interfaz::imprimirMensaje("Plantel no encontrado.");
            }
            limpiarEnter();
            break;
        }
        case 7: { // Cambiar Estado de Vehículo
            limpiar();
            Interfaz::imprimirTitulo("CAMBIAR ESTADO DE VEHICULO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->getVehiculos()->mostrarVehiculos());
            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();

            vehiculo* v = suc->getVehiculos()->buscarVehiculoPorPlaca(placa);
            if (v == nullptr) {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.");
                limpiarEnter();
                break;
            }

            limpiar();
            print("Estado actual: ");
            print(v->getEstado());
            print("\n\n");
            print("Estados posibles:\n");
            print("1. Disponible\n");
            print("2. Alquilado\n");
            print("3. Devuelto\n");
            print("4. Revision\n");
            print("5. Lavado\n");
            print("Seleccione nuevo estado: ");
            int opEstado = digNum();

            string nuevoEstado;
            switch (opEstado) {
            case 1: nuevoEstado = "Disponible"; break;
            case 2: nuevoEstado = "Alquilado"; break;
            case 3: nuevoEstado = "Devuelto"; break;
            case 4: nuevoEstado = "Revision"; break;
            case 5: nuevoEstado = "Lavado"; break;
            default:
                Interfaz::imprimirMensaje("Opcion invalida.");
                limpiarEnter();
                break;
            }

            print("Ingrese fecha del cambio (DD/MM/AAAA): ");
            string fecha = digPalabra();

            string idCol = Interfaz::solicitarIDColaborador();
            colaborador* col = suc->getColaboradores()->buscarColaborador(idCol);

            if (col == nullptr) {
                Interfaz::imprimirMensaje("Colaborador no encontrado.");
                limpiarEnter();
                break;
            }

            if (v->cambiarEstado(nuevoEstado, fecha, col)) {
                Interfaz::imprimirMensaje("Estado cambiado exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("Transicion de estado invalida.");
            }
            limpiarEnter();
            break;
        }
        case 8: { // Visualizar Bitácora de Vehículo
            limpiar();
            Interfaz::imprimirTitulo("BITACORA DE VEHICULO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Ingrese la placa del vehiculo: ");
            string placa = digPalabra();

            vehiculo* v = suc->getVehiculos()->buscarVehiculoPorPlaca(placa);
            if (v != nullptr) {
                Interfaz::imprimirMensaje(v->mostrarBitacora());
            }
            else {
                Interfaz::imprimirMensaje("Vehiculo no encontrado.");
            }
            limpiarEnter();
            break;
        }
        case 9: { // Reporte de porcentaje de ocupación
            limpiar();
            Interfaz::imprimirTitulo("PORCENTAJE DE OCUPACION DE PLANTELES");

            sucursal* suc = obtenerSucursal();
            if (suc != nullptr) {
                Interfaz::imprimirMensaje(suc->reportePorcentajeOcupacion());
            }
            limpiarEnter();
            break;
        }
        case 10: { // Traslado entre sucursales (OPCIONAL)
            limpiar();
            Interfaz::imprimirTitulo("TRASLADO DE VEHICULO ENTRE SUCURSALES");

            Interfaz::imprimirMensaje("Funcionalidad opcional en desarrollo.");
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.");
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
            Interfaz::imprimirTitulo("CREAR SOLICITUD DE ALQUILER");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            // Generar código único 
            stringstream ss;
            ss << "SOL-" << (rand() % 9000 + 1000);
            string codigo = ss.str();

            // Seleccionar cliente
            Interfaz::imprimirMensaje(suc->getClientes()->mostrarTodosLosClientes());
            print("Ingrese cedula del cliente: ");
            string idCliente = digPalabra();
            cliente* cli = suc->getClientes()->buscarClientePorCedula(idCliente);

            if (cli == nullptr) {
                Interfaz::imprimirMensaje("Cliente no encontrado.");
                limpiarEnter();
                break;
            }

            // Seleccionar vehículo disponible
            Interfaz::imprimirMensaje(suc->getVehiculos()->mostrarVehiculosDisponibles());
            print("Ingrese placa del vehiculo: ");
            string placa = digPalabra();
            vehiculo* veh = suc->getVehiculos()->buscarVehiculoPorPlaca(placa);

            if (veh == nullptr || veh->getEstado() != "Disponible") {
                Interfaz::imprimirMensaje("Vehiculo no disponible.");
                limpiarEnter();
                break;
            }

            // Seleccionar colaborador
            string idCol = Interfaz::solicitarIDColaborador();
            colaborador* col = suc->getColaboradores()->buscarColaborador(idCol);

            if (col == nullptr) {
                Interfaz::imprimirMensaje("Colaborador no encontrado.");
                limpiarEnter();
                break;
            }

            print("Ingrese cantidad de dias: ");
            int dias = digNum();
            print("Ingrese fecha de inicio (DD/MM/AAAA): ");
            string fInicio = digPalabra();
            print("Ingrese fecha de entrega (DD/MM/AAAA): ");
            string fEntrega = digPalabra();

            solicitudAlquiler* sol = new solicitudAlquiler(codigo, cli, col, veh,
                dias, fInicio, fEntrega,
                veh->getPrecio());

            suc->agregarSolicitud(sol);
            limpiar();
            Interfaz::imprimirMensaje("Solicitud creada exitosamente!");
            Interfaz::imprimirMensaje(sol->toString());
            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Solicitudes
            limpiar();
            Interfaz::imprimirTitulo("SOLICITUDES POR SUCURSAL");

            sucursal* suc = obtenerSucursal();
            if (suc != nullptr) {
                Interfaz::imprimirMensaje(suc->mostrarSolicitudes());
                Interfaz::imprimirMensaje("\n--- CONTRATOS ---");
                Interfaz::imprimirMensaje(suc->mostrarContratos());
            }
            limpiarEnter();
            break;
        }
        case 3: { // Mostrar Solicitud Específica
            limpiar();
            Interfaz::imprimirTitulo("BUSCAR SOLICITUD/CONTRATO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Ingrese codigo de solicitud/contrato: ");
            string codigo = digPalabra();

            solicitudAlquiler* sol = suc->buscarSolicitud(codigo);
            if (sol != nullptr) {
                Interfaz::imprimirMensaje(sol->toString());
            }
            else {
                contratoAlquiler* cont = suc->buscarContrato(codigo);
                if (cont != nullptr) {
                    Interfaz::imprimirMensaje(cont->toString());
                }
                else {
                    Interfaz::imprimirMensaje("No encontrado.");
                }
            }
            limpiarEnter();
            break;
        }
        case 4: { // Aprobar/Rechazar Solicitud
            limpiar();
            Interfaz::imprimirTitulo("APROBAR/RECHAZAR SOLICITUD");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->mostrarSolicitudes());
            print("Ingrese codigo de solicitud: ");
            string codigo = digPalabra();

            print("1. Aprobar\n2. Rechazar\nSeleccione: ");
            int accion = digNum();

            if (accion == 1) {
                if (suc->aprobarSolicitud(codigo)) {
                    Interfaz::imprimirMensaje("Solicitud aprobada y convertida en contrato!");
                }
                else {
                    Interfaz::imprimirMensaje("Error al aprobar solicitud.");
                }
            }
            else if (accion == 2) {
                if (suc->rechazarSolicitud(codigo)) {
                    Interfaz::imprimirMensaje("Solicitud rechazada.");
                }
                else {
                    Interfaz::imprimirMensaje("Error al rechazar solicitud.");
                }
            }
            limpiarEnter();
            break;
        }
        case 5: { // Recibir Vehículo (Finalizar Contrato)
            limpiar();
            Interfaz::imprimirTitulo("RECIBIR VEHICULO ALQUILADO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->mostrarContratos());
            print("Ingrese codigo del contrato: ");
            string codigo = digPalabra();

            contratoAlquiler* contrato = suc->buscarContrato(codigo);
            if (contrato == nullptr) {
                Interfaz::imprimirMensaje("Contrato no encontrado.");
                limpiarEnter();
                break;
            }

            print("Ingrese cantidad de dias realmente utilizados: ");
            int diasReales = digNum();

            contrato->finalizarContrato(diasReales);

            // Cambiar estado del vehículo a Devuelto
            vehiculo* v = contrato->getVehiculo();
            if (v != nullptr) {
                v->setEstado("Devuelto");
            }

            limpiar();
            Interfaz::imprimirMensaje("===== CONTRATO FINALIZADO =====\n");
            Interfaz::imprimirMensaje(contrato->toString());
            limpiarEnter();
            break;
        }
        case 6: { // Reporte de contratos para vehículo
            limpiar();
            Interfaz::imprimirTitulo("CONTRATOS PARA VEHICULO ESPECIFICO");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Ingrese placa del vehiculo: ");
            string placa = digPalabra();

            Interfaz::imprimirMensaje(suc->reporteContratosVehiculo(placa));
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.");
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
            Interfaz::imprimirTitulo("AGREGAR CLIENTE");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("Tipo de cliente:\n");
            print("1. Persona Fisica\n");
            print("2. Persona Juridica\n");
            print("Seleccione: ");
            int tipo = digNum();

            print("Ingrese cedula: ");
            string cedula = digPalabra();
            print("Ingrese nombre: ");
            string nombre = digPalabra();
            print("Ingrese pais de residencia: ");
            string pais = digPalabra();

            if (tipo == 1) {
                print("Ingrese tipo de licencia: ");
                string licencia = digPalabra();

                personaFisica* pf = new personaFisica(cedula, nombre, pais, licencia);
                suc->getClientes()->agregarClienteFisico(pf);
                Interfaz::imprimirMensaje("Cliente fisico agregado exitosamente!");
            }
            else if (tipo == 2) {
                print("Ingrese actividad economica: ");
                string actividad = digPalabra();
                print("Ingrese porcentaje de descuento: ");
                double descuento = digDouble();

                personaJuridica* pj = new personaJuridica(cedula, nombre, pais, actividad, descuento);
                suc->getClientes()->agregarClienteJuridico(pj);
                Interfaz::imprimirMensaje("Cliente juridico agregado exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("Opcion invalida.");
            }

            limpiarEnter();
            break;
        }
        case 2: { // Mostrar Clientes
            limpiar();
            Interfaz::imprimirTitulo("MOSTRAR CLIENTES");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            print("1. Mostrar todos los clientes\n");
            print("2. Mostrar solo personas fisicas\n");
            print("3. Mostrar solo personas juridicas\n");
            print("Seleccione: ");
            int subOpcion = digNum();

            limpiar();
            switch (subOpcion) {
            case 1:
                Interfaz::imprimirMensaje(suc->getClientes()->mostrarTodosLosClientes());
                break;
            case 2:
                Interfaz::imprimirMensaje(suc->getClientes()->mostrarClientesFisicos());
                break;
            case 3:
                Interfaz::imprimirMensaje(suc->getClientes()->mostrarClientesJuridicos());
                break;
            default:
                Interfaz::imprimirMensaje("Opcion invalida.");
            }

            limpiarEnter();
            break;
        }
        case 3: { // Eliminar Cliente
            limpiar();
            Interfaz::imprimirTitulo("ELIMINAR CLIENTE");

            sucursal* suc = obtenerSucursal();
            if (suc == nullptr) break;

            Interfaz::imprimirMensaje(suc->getClientes()->mostrarTodosLosClientes());
            print("Ingrese cedula del cliente a eliminar: ");
            string cedula = digPalabra();

            if (suc->getClientes()->eliminarCliente(cedula)) {
                Interfaz::imprimirMensaje("Cliente eliminado exitosamente!");
            }
            else {
                Interfaz::imprimirMensaje("No se pudo eliminar el cliente.");
            }

            limpiarEnter();
            break;
        }
        case 4: { // Historial del Cliente
            limpiar();
            Interfaz::imprimirTitulo("HISTORIAL DE ALQUILERES DEL CLIENTE");

            print("Ingrese cedula del cliente: ");
            string cedula = digPalabra();

            Interfaz::imprimirMensaje(sistema->reporteHistorialCliente(cedula));
            limpiarEnter();
            break;
        }
        case 5: { // Reporte de Clientes por Cantidad de Contratos
            limpiar();
            Interfaz::imprimirTitulo("CLIENTES POR CANTIDAD DE CONTRATOS");

            Interfaz::imprimirMensaje(sistema->reporteClientesPorContratos());
            limpiarEnter();
            break;
        }
        case 0:
            break;
        default:
            Interfaz::imprimirMensaje("Opcion invalida.");
            limpiarEnter();
        }
    } while (opcion != 0);
}