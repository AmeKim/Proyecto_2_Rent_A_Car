#include <iostream>
#include "controller.h"

using namespace std;

int main() {
    controller* controlador = new controller();

    controlador->iniciarSistema();

    delete controlador;

    return 0;
}