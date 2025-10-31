#include "carteraClientes.h"

carteraClientes::carteraClientes() : listaBase<cliente>() {}

carteraClientes::~carteraClientes() {}

bool carteraClientes::agregarClienteFisico(personaFisica* fis) {
    if (fis == nullptr) {
        return false;
    }
    return agregarFinal(dynamic_cast<cliente*>(fis));
}

bool carteraClientes::agregarClienteJuridico(personaJuridica* jur) {
    if (jur == nullptr) {
        return false;
    }
    return agregarFinal(dynamic_cast<cliente*>(jur));
}

bool carteraClientes::eliminarCliente(string id) {
    if (estaVacia()) {
        return false;
    }

    nodoBase<cliente>* actual = primero;
    nodoBase<cliente>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getElemento()->getCedula() == id) {
            if (anterior == nullptr) {
                // Eliminar el primero
                primero = actual->getSiguiente();
            }
            else {
                anterior->setSiguiente(actual->getSiguiente());
            }
            delete actual->getElemento();
            delete actual;
            cantidad--;
            return true;
        }
        anterior = actual;
        actual = actual->getSiguiente();
    }

    return false;
}

bool carteraClientes::estaVacio(){
	if(primero == nullptr){
        return true;
	}
    return false;
}

personaFisica* carteraClientes::buscarporCedula(string id) {
    nodoBase<cliente>* actual = primero;
    while (actual != nullptr) {
        personaFisica* pf = dynamic_cast<personaFisica*>(actual->getElemento());
        if (pf != nullptr && pf->getCedula() == id) {
            return pf;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

personaJuridica* carteraClientes::buscarporCedulaJuridica(string id) {
    nodoBase<cliente>* actual = primero;
    while (actual != nullptr) {
        personaJuridica* pj = dynamic_cast<personaJuridica*>(actual->getElemento());
        if (pj != nullptr && pj->getCedula() == id) {
            return pj;
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

cliente* carteraClientes::buscarClientePorCedula(string id) {
    nodoBase<cliente>* actual = primero;
    while (actual != nullptr) {
        if (actual->getElemento()->getCedula() == id) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string carteraClientes::mostrarClientesFisicos() {
    nodoBase<cliente>* actual = primero;
    stringstream s;
    int i = 1;
    while (actual != nullptr) {
        personaFisica* pf = dynamic_cast<personaFisica*>(actual->getElemento());
        if (pf != nullptr) {
            s << i << ". " << pf->toString() << endl;
            i++;
        }
        actual = actual->getSiguiente();
    }
    if (i == 1) {
        s << "No hay clientes fisicos registrados.\n";
    }
    return s.str();
}

string carteraClientes::mostrarClientesJuridicos() {
    nodoBase<cliente>* actual = primero;
    stringstream s;
    int i = 1;
    while (actual != nullptr) {
        personaJuridica* pj = dynamic_cast<personaJuridica*>(actual->getElemento());
        if (pj != nullptr) {
            s << i << ". " << pj->toString() << endl;
            i++;
        }
        actual = actual->getSiguiente();
    }
    if (i == 1) {
        s << "No hay clientes juridicos registrados.\n";
    }
    return s.str();
}

string carteraClientes::mostrarTodosLosClientes() {
    nodoBase<cliente>* actual = primero;
    stringstream s;
    s << "\n===== CLIENTES REGISTRADOS =====\n\n";
    int i = 1;
    while (actual != nullptr) {
        s << i << ". " << actual->getElemento()->toString() << endl;
        actual = actual->getSiguiente();
        i++;
    }
    if (i == 1) {
        s << "No hay clientes registrados.\n";
        
    }
    return s.str();
}

