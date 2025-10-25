#pragma once
#include "nodoBase.h"

template <class T>
class listaBase{
protected:
	nodoBase<T>* primero;
	int cantidad;
public:
	listaBase();
	~listaBase();

	bool agregarInicio(T* elemento);
	bool agregarFinal(T* elemento);

	bool eliminarInicio();
	bool eliminarFinal();

	bool estaVacia() const;

	string toStringLista();

	nodoBase<T>* retornarPrimero();
	nodoBase<T>* retornarUltimo();

};

