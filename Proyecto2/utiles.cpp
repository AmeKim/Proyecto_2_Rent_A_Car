#pragma once
#include <iostream>
#include "utiles.h"
using namespace std;

void print(string valor) { cout << valor; }
void print(int valor) { cout << valor; }
string digPalabra() {
	string valor;
	getline(cin, valor);
	return valor;
}

int digNum() {
	int valor;
	if (cin >> valor) {
		cin.ignore();
		return valor;
	}
	else {
		cin.ignore();
		print("Error: Solo se permiten digitos\n");
		return 0;
	}
}

double digDouble() {
	double valor;
	if (cin >> valor) {
		cin.ignore();
		return valor;
	}
	else {
		cin.ignore();
		print("Error: Solo se permiten digitos\n");
		return 0.0;
	}
}

void limpiar() { system("cls"); }
void limpiarEnter() {
	print("\nPresione ENTER para continuar\n");
	cin.get();
	system("cls");
}