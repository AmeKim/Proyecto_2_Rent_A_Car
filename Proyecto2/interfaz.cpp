#include "Interfaz.h"



void Interfaz::imprimirMensaje(string m) { cout << m << endl; }

void Interfaz::imprimirTitulo(string t) {
    limpiar();
    cout << "-------------" << t << "-------------" << endl;
}

int Interfaz::menuPrincipal() {
    int opcion;
    limpiar();
    print("========================================\n");
    cout << "   GESTI" << char(224) << "N DE D - R - T CAR RENTAL\n";
    print("========================================\n");
    cout << "Men" << char(163) << " Principal\n";
    print("========================================\n");
    cout << "(1) Submen" << char(163) << " de Sucursales\n";
    cout << "(2) Submen" << char(163) << " de Clientes\n";
    cout << "(3) Submen" << char(163) << " de Colaboradores\n";
    cout << "(4) Submen" << char(163) << " de Veh" << char(161) << "culos y Planteles\n";
    cout << "(5) Submen" << char(163) << " de Solicitudes y Contratos\n";
    print("(0) Salir\n");
    print("========================================\n");
    cout << "Digite la opci" << char(162) << "n deseada : ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuSucursal() {
    int opcion;
    limpiar();
    print("========================================\n");
    cout << "         SUBMEN" << char(233) << " DE SUCURSALES\n";
    print("========================================\n");
    print("(1) Agregar Sucursal\n");
    print("(2) Mostrar Sucursales\n");
    print("(3) Eliminar Sucursal\n");
    cout << "(0) Volver al Men" << char(163) << " Principal\n";
    print("========================================\n");
    cout << "Digite la opci" << char(162) << "n deseada : ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuColaborador() {
    int opcion;
    limpiar();
    print("========================================\n");
    cout << "       SUBMEN" << char(233) << " DE COLABORADORES\n";
    print("========================================\n");
    print("(1) Agregar Colaborador\n");
    print("(2) Mostrar Colaborador Especifico\n");
    print("(3) Eliminar Colaborador\n");
    print("(4) Reportes por Colaborador\n");
    cout << "(0) Volver al Men" << char(163) << " Principal\n";
    print("========================================\n");
    cout << "Digite la opci" << char(162) << "n deseada : ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuVehiculosYPlanteles() {
    int opcion;
    limpiar();
    print("========================================\n");
    cout << "   SUBMEN" << char(233) << " DE VEH" << char(214) << "CULOS Y PLANTELES\n";
    print("========================================\n");
    print("(1) Agregar Plantel\n");
    print("(2) Visualizar Plantel\n");
    cout << "(3) Agregar Veh" << char(161) << "culo\n";
    cout << "(4) Visualizar Veh" << char(161) << "culo\n";
    cout << "(5) Eliminar Veh" << char(161) << "culo\n";
    cout << "(6) Reasignar Veh" << char(161) << "culo\n";
    cout << "(7) Cambiar Estado del Veh" << char(161) << "culo\n";
    cout << "(8) Visualizar Estado de un Veh" << char(161) << "culo Especi" << char(161) << "fico\n";
    cout << "(9) Generar Reporte Porcentaje Ocupaci" << char(162) << "on de los planteles\n";
    cout << "(10) Traslado Veh" << char(161) << "culos a Sucursal\n";
    cout << "(0) Volver al Men" << char(163) << " Principal\n";
    print("========================================\n");
    cout << "Digite la opci" << char(162) << "n deseada : ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuSolicitudesYContratos() {
    int opcion;
    limpiar();
    print("========================================\n");
    cout << " SUBMEN" << char(233) << " DE SOLICITUDES Y CONTRATOS\n";
    print("========================================\n");
    print("(1) Crear Solicitud de Alquiler\n");
    print("(2) Mostrar Solicitudes por Sucursal\n");
    cout << "(3) Mostrar Solicitud Espec" << char(161) << "fica\n";
    print("(4) Aprobar/Rechazar Solicitud\n");
    cout << "(5) Recibir Veh" << char(161) << "culo Alquilado\n";
    print("(6) Generar Reporte de Contratos\n");
    cout << "(0) Volver al Men" << char(163) << " Principal\n";
    print("========================================\n");
    cout << "Digite la opci" << char(162) << "n deseada : ";
    opcion = digNum();
    return opcion;
}

int Interfaz::submenuClientes() {
    int opcion;
    limpiar();
    print("========================================\n");
    print("        SUBMENU DE CLIENTES\n");
    print("========================================\n");
    print("(1) Agregar Cliente\n");
    print("(2) Mostrar Cliente\n");
    print("(3) Eliminar Cliente\n");
    print("(4) Historial de Alquileres del Cliente\n");
    print("(5) Reporte de Cantidad de Contratos por Cliente\n");
    cout << "(0) Volver al Men" << char(163) << " Principal\n";
    print("========================================\n");
    cout << "Digite la opci" << char(162) << "n deseada : ";
    opcion = digNum();
    return opcion;
}

//--------------------Metodos para Sucursales--------------------------
sucursal* Interfaz::capturarDatosSucursal() {
    print("Ingrese el ID de la sucursal: ");
    int id = digNum();
    limpiar();
    print("Ingrese el nombre de la sucursal: ");
    string nombre;
    getline(cin, nombre);
    limpiar();
    print("Ingrese la provincia de la sucursal: ");
    string provincia;
    getline(cin, provincia);
    limpiar();

    sucursal* nuevaSucursal = new sucursal(id, nombre, provincia);

    return nuevaSucursal;
}

int Interfaz::solicitarIDSucursal() {
    print("Ingrese el ID de la Sucursal: ");
    int id = digNum();
    limpiar();
    return id;
}

//--------------------Metodos para Colaboradores-----------------------
colaborador* Interfaz::capturarDatosColaborador() {
    print("Ingrese el nombre del Colaborador: ");
    string nombre = digPalabra();
    limpiar();
    print("Ingrese el ID del Colaborador: ");
    string id = digPalabra();
    print("Ingrese la Fecha de Ingreso del Colaborador (DD/MM/AAAA): ");
    string fechaIngreso = digPalabra();
    limpiar();

    colaborador* nuevoColaborador = new colaborador(nombre, id, fechaIngreso);

    return nuevoColaborador;
}

string Interfaz::solicitarIDColaborador() {
    print("Ingrese el ID del Colaborador: ");
    string id = digPalabra();
    limpiar();
    return id;
}

//------------------Metodos para Carros y Planteles---------------------
void Interfaz::capturarDatosPlantel() {
    print("Ingrese el nombre del Plantel: ");
}

//--------------Metodos para Solicitudes y Contratos--------------------

void Interfaz::crearSolicitudAlquiler() {
    // Implementacion pendiente
}
void Interfaz::mostrarSolicitudesPorSucursal() {
    // Implementacion pendiente
}
void Interfaz::mostrarSolicitudEspecifica() {
    // Implementacion pendiente
}
void Interfaz::aprobarRechazarSolicitud() {
    // Implementacion pendiente
}
void Interfaz::recibirVehiculoAlquilado() {
    // Implementacion pendiente
}
void Interfaz::generarReporteContratos() {
    // Implementacion pendiente
}

//----------------------Metodos para Clientes----------------------------
cliente* Interfaz::agregarCliente() {
    //Implementacion pendiente
    return nullptr;
}

string Interfaz::mostrarCliente() {
    //Implementacion pendiente
    return "";
}
void Interfaz::eliminarCliente() {
    //Implementacion pendiente
}
void Interfaz::historialAlquileresCliente() {
    //Implementacion pendiente
}
void Interfaz::reporteCantidadContratosPorCliente() {
    //Implementacion pendiente
}