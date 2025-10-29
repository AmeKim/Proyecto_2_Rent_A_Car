#include "interfaz.h"

void Interfaz::imprimirMensaje(string m) {
    cout << m << endl;
}

void Interfaz::imprimirTitulo(string t) {
    limpiar();
    cout << "\n========================================" << endl;
    cout << "  " << t << endl;
    cout << "========================================\n" << endl;
}

int Interfaz::menuPrincipal() {
    int opcion;
    limpiar();
    cout << "========================================" << endl;
    cout << "   GESTION DE D - R - T CAR RENTAL" << endl;
    cout << "========================================" << endl;
    cout << "Menu Principal" << endl;
    cout << "========================================" << endl;
    cout << "(1) Submenu de Sucursales" << endl;
    cout << "(2) Submenu de Clientes" << endl;
    cout << "(3) Submenu de Colaboradores" << endl;
    cout << "(4) Submenu de Vehiculos y Planteles" << endl;
    cout << "(5) Submenu de Solicitudes y Contratos" << endl;
    cout << "(0) Salir" << endl;
    cout << "========================================" << endl;
    cout << "Digite la opcion deseada: ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuSucursal() {
    int opcion;
    limpiar();
    cout << "========================================" << endl;
    cout << "         SUBMENU DE SUCURSALES" << endl;
    cout << "========================================" << endl;
    cout << "(1) Ingresar Sucursal" << endl;
    cout << "(2) Mostrar Sucursales" << endl;
    cout << "(3) Eliminar Sucursal" << endl;
    cout << "(0) Regresar Menu Principal" << endl;
    cout << "========================================" << endl;
    cout << "Digite la opcion deseada: ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuColaborador() {
    int opcion;
    limpiar();
    cout << "========================================" << endl;
    cout << "       SUBMENU DE COLABORADORES" << endl;
    cout << "========================================" << endl;
    cout << "(1) Incluir Colaborador en Sucursal" << endl;
    cout << "(2) Mostrar Colaborador" << endl;
    cout << "(3) Eliminar Colaborador" << endl;
    cout << "(4) Reporte de Alquileres por Colaborador" << endl;
    cout << "(0) Regresar al Menu Principal" << endl;
    cout << "========================================" << endl;
    cout << "Digite la opcion deseada: ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuVehiculosYPlanteles() {
    int opcion;
    limpiar();
    cout << "========================================" << endl;
    cout << "   SUBMENU DE VEHICULOS Y PLANTELES" << endl;
    cout << "========================================" << endl;
    cout << "(1) Crear Plantel" << endl;
    cout << "(2) Visualizacion Grafica de Plantel" << endl;
    cout << "(3) Ingreso de Vehiculo" << endl;
    cout << "(4) Visualizacion de Vehiculo" << endl;
    cout << "(5) Eliminacion de Vehiculo" << endl;
    cout << "(6) Reasignacion de vehiculo en Plantel" << endl;
    cout << "(7) Cambio de Estado de Vehiculo" << endl;
    cout << "(8) Estados de un vehiculo especifico" << endl;
    cout << "(9) Reporte de porcentaje de ocupacion de los planteles" << endl;
    cout << "(10) Traslado de vehiculos a sucursal (OPCIONAL)" << endl;
    cout << "(0) Regresar al Menu Principal" << endl;
    cout << "========================================" << endl;
    cout << "Digite la opcion deseada: ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuSolicitudesYContratos() {
    int opcion;
    limpiar();
    cout << "========================================" << endl;
    cout << " SUBMENU DE SOLICITUDES Y CONTRATOS" << endl;
    cout << "========================================" << endl;
    cout << "(1) Creacion de Solicitud" << endl;
    cout << "(2) Visualizacion de Solicitudes/Contratos por Sucursal" << endl;
    cout << "(3) Visualizacion de Solicitud/Contratos Especifica" << endl;
    cout << "(4) Aprobacion/Rechazo de Solicitud" << endl;
    cout << "(5) Recepcion de Vehiculo en Prestado" << endl;
    cout << "(6) Reporte de Contratos para Vehiculo Especifico" << endl;
    cout << "(0) Regresar al Menu Principal" << endl;
    cout << "========================================" << endl;
    cout << "Digite la opcion deseada: ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuClientes() {
    int opcion;
    limpiar();
    cout << "========================================" << endl;
    cout << "        SUBMENU DE CLIENTES" << endl;
    cout << "========================================" << endl;
    cout << "(1) Ingresar Cliente" << endl;
    cout << "(2) Mostrar Cliente" << endl;
    cout << "(3) Eliminar Cliente" << endl;
    cout << "(4) Historial del Cliente" << endl;
    cout << "(5) Reporte de Clientes por Cantidad de Contratos" << endl;
    cout << "(0) Regresar al Menu Principal" << endl;
    cout << "========================================" << endl;
    cout << "Digite la opcion deseada: ";
    opcion = digNum();
    return opcion;
}

// ==================== METODOS PARA SUCURSALES ====================

sucursal* Interfaz::capturarDatosSucursal() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS DE SUCURSAL");

    cout << "Ingrese el ID de la sucursal: ";
    int id = digNum();

    cout << "Ingrese el nombre de la sucursal: ";
    string nombre = digPalabra();

    cout << "Ingrese la provincia de la sucursal: ";
    string provincia = digPalabra();

    sucursal* nuevaSucursal = new sucursal(id, nombre, provincia);
    return nuevaSucursal;
}

int Interfaz::solicitarIDSucursal() {
    cout << "\nIngrese el ID de la Sucursal: ";
    int id = digNum();
    return id;
}

// ==================== METODOS PARA COLABORADORES ====================

colaborador* Interfaz::capturarDatosColaborador() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS DE COLABORADOR");

    cout << "Ingrese el nombre del Colaborador: ";
    string nombre = digPalabra();

    cout << "Ingrese la cedula del Colaborador: ";
    string cedula = digPalabra();

    cout << "Ingrese la Fecha de Ingreso (DD/MM/AAAA): ";
    string fechaIngreso = digPalabra();

    colaborador* nuevoColaborador = new colaborador(nombre, cedula, fechaIngreso);
    return nuevoColaborador;
}

string Interfaz::solicitarIDColaborador() {
    cout << "\nIngrese la cedula del Colaborador: ";
    string id = digPalabra();
    return id;
}

// ==================== METODOS PARA VEHICULOS Y PLANTELES ====================

vehiculo* Interfaz::capturarDatosVehiculo() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS DE VEHICULO");

    cout << "Ingrese la placa del vehiculo: ";
    string placa = digPalabra();

    cout << "Ingrese la marca del vehiculo: ";
    string marca = digPalabra();

    cout << "Ingrese el modelo del vehiculo: ";
    string modelo = digPalabra();

    cout << "Ingrese el tipo de licencia requerida: ";
    string tipoLicencia = digPalabra();

    cout << "Ingrese la categoria del vehiculo (A/B/C/D): ";
    string catStr = digPalabra();
    char categoria = (catStr.length() > 0) ? catStr[0] : 'A';

    cout << "Ingrese el precio por dia de alquiler: ";
    double precio = digDouble();

    // Estado inicial siempre es "Revision" cuando se ingresa un vehículo nuevo
    vehiculo* nuevoVehiculo = new vehiculo(placa, modelo, marca, tipoLicencia,
        precio, "Revision", categoria, "");

    return nuevoVehiculo;
}

plantel* Interfaz::capturarDatosPlantel() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS DE PLANTEL");

    cout << "Ingrese la letra identificadora del plantel: ";
    string letraStr = digPalabra();
    char letra = (letraStr.length() > 0) ? letraStr[0] : 'A';

    cout << "Ingrese la capacidad maxima del plantel: ";
    int capacidad = digNum();

    cout << "\nTipos de plantel:" << endl;
    cout << "(1) Techado y asfaltado" << endl;
    cout << "(2) Techado y lastreado" << endl;
    cout << "(3) Asfaltado" << endl;
    cout << "(4) Lastreado" << endl;
    cout << "Seleccione el tipo de plantel: ";
    int tipo = digNum();

    cout << "Ingrese el numero de filas para los espacios: ";
    int filas = digNum();

    cout << "Ingrese el numero de columnas para los espacios: ";
    int columnas = digNum();

    plantel* nuevoPlantel = new plantel(letra, capacidad, tipo, filas, columnas);
    return nuevoPlantel;
}

// ==================== METODOS PARA CLIENTES ====================

cliente* Interfaz::capturarDatosCliente() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS DE CLIENTE");

    cout << "Tipo de cliente:" << endl;
    cout << "(1) Persona Fisica" << endl;
    cout << "(2) Persona Juridica" << endl;
    cout << "Seleccione: ";
    int tipo = digNum();

    if (tipo == 1) {
        return capturarDatosPersonaFisica();
    }
    else if (tipo == 2) {
        return capturarDatosPersonaJuridica();
    }
    else {
        imprimirMensaje("Opcion invalida. Se creara persona fisica por defecto.");
        return capturarDatosPersonaFisica();
    }
}

personaFisica* Interfaz::capturarDatosPersonaFisica() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS - PERSONA FISICA");

    cout << "Ingrese la cedula: ";
    string cedula = digPalabra();

    cout << "Ingrese el nombre completo: ";
    string nombre = digPalabra();

    cout << "Ingrese el pais de residencia: ";
    string pais = digPalabra();

    cout << "Ingrese el tipo de licencia: ";
    string tipoLicencia = digPalabra();

    personaFisica* nuevaPersonaFisica = new personaFisica(cedula, nombre, pais, tipoLicencia);
    return nuevaPersonaFisica;
}

personaJuridica* Interfaz::capturarDatosPersonaJuridica() {
    limpiar();
    imprimirTitulo("CAPTURA DE DATOS - PERSONA JURIDICA");

    cout << "Ingrese la cedula juridica: ";
    string cedula = digPalabra();

    cout << "Ingrese el nombre de la empresa: ";
    string nombre = digPalabra();

    cout << "Ingrese el pais de residencia: ";
    string pais = digPalabra();

    cout << "Ingrese la actividad economica: ";
    string actividad = digPalabra();

    cout << "Ingrese el porcentaje de descuento (0-100): ";
    double descuento = digDouble();

    personaJuridica* nuevaPersonaJuridica = new personaJuridica(cedula, nombre, pais,
        actividad, descuento);
    return nuevaPersonaJuridica;
}

// ==================== METODOS PARA SOLICITUDES ====================

solicitudAlquiler* Interfaz::capturarDatosSolicitud() {
    // Este método se implementa directamente en el controller
    // porque necesita acceso a las colecciones de clientes, vehículos y colaboradores
    return nullptr;
}