#pragma once
#include <iostream>
using namespace std;

template <class T>
class nodoBase {
	private:
	T dato;
	nodoBase<T>* siguiente;
public:
	nodoBase(T*);
	nodoBase<T>* getSiguiente();
	T* getElemento();
	void setSiguiente(nodoBase<T>*);
};
