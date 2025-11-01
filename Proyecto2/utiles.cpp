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
	cin.ignore(1000, '\n');  // Limpiar buffer antes
	cin.get();
	system("cls");
}