#include "Interfaz.h"

int Interfaz::menuPrincipal() {
    int opcion;
    limpiar();
    print("========================================\n");
    cout << "   GESTI" << char(224) << "N DE D - R - T CAR RENTAL\n";
    print("========================================\n");
    cout << "Men" <<char(163) <<" Principal\n";
    print("========================================\n");
    cout << "(1) Submen" << char(163) << " de Sucursales\n";
    cout << "(2) Submen" << char(163) << " de Clientes\n";
    cout << "(3) Submen" << char(163) << " de Colaboradores\n";
    cout << "(4) Submen" << char(163) << " de Veh" << char(161)<< "culos y Planteles\n";
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
    cout << "         SUBMEN" << char(233)<< " DE SUCURSALES\n";
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
void Interfaz::agregarSucursal() {
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
    // Crear la sucursal
    sucursal* nuevaSucursal = new sucursal(id, nombre, provincia);
    // Agregar la sucursal al sistema (implementacion pendiente)
	print("Sucursal agregada exitosamente.\n");
}

void Interfaz::mostrarSucursales() {
	// Implementacion pendiente
}

void Interfaz::eliminarSucursal() {
    // Implementacion pendiente
}

//--------------------Metodos para Colaboradores-----------------------
void Interfaz::agregarColaborador() {
    // Implementacion pendiente
}
void Interfaz::mostrarColaboradorEspecifico() {
    // Implementacion pendiente
}
void Interfaz::eliminarColaborador() {
    // Implementacion pendiente
}
string Interfaz::reportesPorColaborador() {
    // Implementacion pendiente
    return "";
}
//------------------Metodos para Carros y Planteles---------------------
void Interfaz::agregarPlantel() {
    // Implementacion pendiente
}
    
void Interfaz::visualizarPlantel() {
    // Implementacion pendiente
}
void Interfaz::agregarVehiculo() {
    // Implementacion pendiente
}
void Interfaz::eliminarVehiculo() {
    // Implementacion pendiente
}
void Interfaz::reasignarVehiculo() {
    // Implementacion pendiente
}
void Interfaz::cambiarEstadoVehiculo() {
    // Implementacion pendiente
}
void Interfaz::visualizarEstadoVehiculo() {
    // Implementacion pendiente
}
void Interfaz::generarReportePorcentajeOcupacion() {
    // Implementacion pendiente
}
void Interfaz::trasladoVehiculosASucursal() {
    // Implementacion pendiente
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