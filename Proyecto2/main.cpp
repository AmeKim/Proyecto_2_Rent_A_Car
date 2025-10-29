#include <iostream>
#include "controller.h"

using namespace std;

int main() {
    controller* controlador = new controller();

    cout << "========================================\n";
    cout << "   SISTEMA D-R-T CAR RENTAL\n";
    cout << "========================================\n";
    cout << "\nPresione ENTER para continuar...\n";
    cin.get();

    controlador->iniciarSistema();

    delete controlador;

    return 0;
}