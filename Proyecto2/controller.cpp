#include "controller.h"

controller::controller() {
	sucursales = new SistemaRentACar();
	colaboradores = new conjuntoColaboradores();
	clientes = new carteraClientes();
	vehiculos = new inventarioVehiculos();
}

controller::~controller() {
	delete sucursales;
	delete colaboradores;
	delete clientes;
	delete vehiculos;
}

int controller::iniciarSistema() {
	int opcion;
	do {
		opcion = Interfaz::menuPrincipal();
		switch (opcion) {
		case 1:
			gestionarSucursales(); break;

		case 2:
			gestionarColaboradores(); break;

		case 3:
			gestionarVehiculos(); break;

		case 4:
			gestionarSolicitudes(); break;

		case 5:
			gestionarClientes(); break;

		case 0:
			print("Saliendo del sistema...");
			print("Gracias por usar R - T Car Rental.");
			print("Hasta luego!\n");
			break;
		default: {
			print("\nPor favor digite una opcion valida\n");
			print("\n----------------------------------------\n");
			limpiarEnter();
		}
		}
	} while (opcion != 0);
	return 0;
}

void controller::gestionarSucursales() {
	int opcion;
	do {
		opcion = Interfaz::submenuSucursal();
		switch (opcion) {
		case 1: {
			print("--------------Agregando una Sucursal-------------");
			sucursal* nuevaSucursal = Interfaz::capturarDatosSucursal();
			if (nuevaSucursal != nullptr) {
				if (!sucursales->buscarIDEntreSucursales(nuevaSucursal->getIdSucursal())) {
					sucursales->registrarSucursal(nuevaSucursal);
					Interfaz::imprimirMensaje("\n[EXITO] Sucursal agregada correctamente.");
				}
				else {
					Interfaz::imprimirMensaje("Ya existe una Sucursal con ese ID, ingrese uno nuevo");
					delete nuevaSucursal;
				}
			}
		} break;

		case 2: {
			Interfaz::imprimirTitulo("Lista de Sucursales");
			if (sucursales->estaVacio()) {
				Interfaz::imprimirMensaje("No hay sucursales registradas.");
			}
			else {
				sucursales->mostrarSucursales();
			}
			limpiarEnter();
		} break;

		case 3: {
			Interfaz::imprimirTitulo("Eliminando una Sucursal");

			if (sucursales->estaVacio()) {
				Interfaz::imprimirMensaje("No hay sucursales para eliminar.");
				break;
			}

			// Mostrar sucursales disponibles
			sucursales->mostrarSucursales();

			// Pedir ID
			int id = Interfaz::solicitarIDSucursal();

			// Eliminar
			if (sucursales->buscarIDEntreSucursales(id)) {
				sucursales->eliminarSucursal(id);
				Interfaz::imprimirMensaje("\n[EXITO] Sucursal eliminada correctamente.");
			}
			else {
				Interfaz::imprimirMensaje("\n[ERROR] No existe una sucursal con ese ID.");
			}
			break;
		}
		case 0:
			Interfaz::imprimirMensaje("\nVolviendo al menú principal...");
			break;

		default:
			Interfaz::imprimirMensaje("\n[ERROR] Opción inválida.");
			limpiar();
		}
	} while (opcion != 0);
}

void controller::gestionarColaboradores() {
	int opcion;
	do {
		opcion = Interfaz::submenuColaborador();
		switch (opcion) {
		case 1: {
			Interfaz::imprimirTitulo("Agregando un Colaborador");
			int idSucursal = seleccionarSucursal();
			if (idSucursal == -1) break;

			colaborador* nuevoColaborador = Interfaz::capturarDatosColaborador();
			sucursal* suc = sucursales->buscarSucursalPorId(idSucursal);

			if (suc != nullptr) {
				suc->getConjuntoColaboradores()->agregarColaborador(nuevoColaborador);
				Interfaz::imprimirMensaje("\n[EXITO] Colaborador agregado correctamente a la sucursal.");
			}
			else {
				Interfaz::imprimirMensaje("\n[ERROR] No se encontró la sucursal seleccionada.");
				delete nuevoColaborador;
			}
		} break;

		case 2: {
			Interfaz::imprimirTitulo("Mostrando Colaboradores por Sucursal");
			int idSucursal = seleccionarSucursal();
			if (idSucursal == -1) break;

			sucursal* suc = sucursales->buscarSucursalPorId(idSucursal);

			if (suc != nullptr) {
				string colaboradoresStr = suc->getConjuntoColaboradores()->mostrarColaboradores();
				Interfaz::imprimirMensaje(colaboradoresStr);
			}
			else {
				Interfaz::imprimirMensaje("\n[ERROR] No se encontró la sucursal seleccionada.");
			}
		} break;

		case 3: {
			Interfaz::imprimirTitulo("Eliminando un Colaborador");
			int idSucursal = seleccionarSucursal();

			if (idSucursal == -1) break;

			sucursal* suc = sucursales->buscarSucursalPorId(idSucursal);
			if (suc == nullptr) {
				Interfaz::imprimirMensaje("\n[ERROR] No se encontró la sucursal.");
				break;
			}

			// Mostrar colaboradores de esa sucursal
			Interfaz::imprimirMensaje("\n--- Colaboradores en esta sucursal ---");
			Interfaz::imprimirMensaje(suc->getConjuntoColaboradores()->mostrarColaboradores());

			string idColaborador = Interfaz::solicitarIDColaborador();

			if (suc->getConjuntoColaboradores()->eliminarColaborador(idColaborador)) {
				Interfaz::imprimirMensaje("\n[EXITO] Colaborador eliminado correctamente.");
			}
			else {
				Interfaz::imprimirMensaje("\n[ERROR] No se encontró un colaborador con ese ID.");
			}
		} break;

		case 4: {
			Interfaz::imprimirTitulo("Reporte de Alquileres por Colaborador");
			string idColaborador = Interfaz::solicitarIDColaborador();
			string reporte = sucursales->reporteAlquileresPorColaborador(idColaborador);
			Interfaz::imprimirMensaje(reporte);
		} break;

		case 0:
			Interfaz::imprimirMensaje("\nVolviendo al menú principal...");
			break;

		default:
			Interfaz::imprimirMensaje("\n[ERROR] Opción inválida.");
			break;
		}
	} while (opcion != 0);
}

void controller::gestionarVehiculos() {
	int opcion;
	do {
		opcion = Interfaz::submenuVehiculosYPlanteles();
		switch (opcion) {
		case 1:
			Interfaz::CapturarDatosVehiculo(); break;
		case 2:
		case 3:


		case 0:
			Interfaz::imprimirMensaje("\nVolviendo al menú principal...");
			break;
		default:
			Interfaz::imprimirMensaje("\n[ERROR] Opción inválida.");
			limpiar();
		}
	}
}

int controller::seleccionarSucursal() {
	if (sucursales->estaVacio()) {
		Interfaz::imprimirMensaje("\n[ERROR] No hay sucursales registradas.");
		Interfaz::imprimirMensaje("Debe crear una sucursal primero.");
		return -1;
	}
	Interfaz::imprimirTitulo("Sucursales Disponibles");
	sucursales->mostrarSucursales();
	Interfaz::imprimirMensaje("Seleccione la sucursal:");

	int idSucursal = Interfaz::solicitarIDSucursal();

	if (!sucursales->buscarIDEntreSucursales(idSucursal)) {
		Interfaz::imprimirMensaje("\n[ERROR] No existe una sucursal con ese ID.");
		return -1;
	}

	return idSucursal;
}