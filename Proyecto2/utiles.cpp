#pragma once
#include <iostream>
#include "utiles.h"
using namespace std;

void print(string valor) { cout << valor; }
void print(int valor) { cout << valor; }

string digPalabra() {
	string valor;
	// Limpiar buffer antes de leer
	if (cin.rdbuf()->in_avail() > 0) {
		cin.ignore(1000, '\n');
	}
	getline(cin, valor);
	return valor;
}

int digNum() {
	int valor;
	if (cin >> valor) {
		cin.ignore(1000, '\n');  // Limpiar TODO el buffer
		return valor;
	}
	else {
		cin.clear();
		cin.ignore(1000, '\n');
		print("Error: Solo se permiten digitos\n");
		return 0;
	}
}

double digDouble() {
	double valor;
	if (cin >> valor) {
		cin.ignore(1000, '\n');  // Limpiar TODO el buffer
		return valor;
	}
	else {
		cin.clear();
		cin.ignore(1000, '\n');
		print("Error: Solo se permiten digitos\n");
		return 0.0;
	}
}

void limpiar() { system("cls"); }

void limpiarEnter() {
	print("\nPresione ENTER para continuar\n");
	// Consumir todo hasta el Enter, incluyendo el Enter
	while (cin.get() != '\n');
	system("cls");
}