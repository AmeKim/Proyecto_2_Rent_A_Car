#include "personaJuridica.h"

personaJuridica::personaJuridica(){
    actividadEconomica = "";
	porcDescuento = 0.0;

}

personaJuridica::personaJuridica(string nombre, string cedula, string paisResidencia, string actividadEconomica, float porcDescuento){
    setNombre(nombre);
    setCedula(cedula);
    setPaisResidencia(paisResidencia);
    setActividadEconomica(actividadEconomica);
    setPorcDescuento(porcDescuento);
}

personaJuridica::~personaJuridica(){
}

void personaJuridica::setActividadEconomica(string actividad) {actividadEconomica = actividad;}

string personaJuridica::getActividadEconomica() const {	return actividadEconomica; }

void personaJuridica::setPorcDescuento(float descuento) { porcDescuento = descuento; }

float personaJuridica::getPorcDescuento() const { return porcDescuento; }

string personaJuridica::toString(){
    stringstream s;
    s << cliente::toString();
    s << "Actividad Economica: " << actividadEconomica << endl;
    s << "Porcentaje de Descuento: " << porcDescuento << "%" << endl;
    return s.str();	
}
