#pragma once
#include <iostream>
#include <string>
#include <sstream>
#include "listaBase.h"
#include "colaborador.h"
using namespace std;

class conjuntoColaboradores : public listaBase<colaborador> {
public:
    conjuntoColaboradores();
    ~conjuntoColaboradores();

    void agregarColaborador(colaborador* col);
    void eliminarColaborador(string id);
    colaborador* buscarColaborador(string id);
    string mostrarColaboradores();
};