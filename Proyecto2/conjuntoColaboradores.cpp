#include "conjuntoColaboradores.h"

conjuntoColaboradores::conjuntoColaboradores() : listaBase<colaborador>() {}

conjuntoColaboradores::~conjuntoColaboradores() {}

void conjuntoColaboradores::agregarColaborador(colaborador* col) {
    if (col != nullptr) {
        agregarFinal(col);
    }
}

bool conjuntoColaboradores::eliminarColaborador(string id) {
    if (estaVacia()) {
        return false;
    }

    nodoBase<colaborador>* actual = primero;
    nodoBase<colaborador>* anterior = nullptr;

    while (actual != nullptr) {
        if (actual->getElemento()->getCedula() == id) {
            if (anterior == nullptr) {
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

colaborador* conjuntoColaboradores::buscarColaborador(string id) {
    nodoBase<colaborador>* actual = primero;
    while (actual != nullptr) {
        if (actual->getElemento()->getCedula() == id) {
            return actual->getElemento();
        }
        actual = actual->getSiguiente();
    }
    return nullptr;
}

string conjuntoColaboradores::mostrarColaboradores() {
    if (estaVacia()) {
        return "No hay colaboradores registrados.\n";
    }

    stringstream ss;
    ss << "\n===== COLABORADORES REGISTRADOS =====\n\n";
    nodoBase<colaborador>* actual = primero;
    int i = 1;
    while (actual != nullptr) {
        ss << i << ". " << actual->getElemento()->toString() << endl;
        actual = actual->getSiguiente();
        i++;
    }
    return ss.str();
}