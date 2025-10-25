#include "sucursal.h"

sucursal::sucursal() {
	idSucursal = 0;
	nombre = "";
	provincia = "";
}

sucursal::sucursal(int id, const string& nom, const string& prov) {
	idSucursal = id;
	nombre = nom;
	provincia = prov;
}

sucursal::~sucursal() {
}

int sucursal::getIdSucursal() const {
	return idSucursal;
}
string sucursal::getNombre() const {
	return nombre;
}

string sucursal::getProvincia() const {
	return provincia;
}

bool sucursal::agregarPlantel(plantel* p) {
	if(p == nullptr) {
		return false;
	}
	
}