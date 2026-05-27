#pragma once

#include <iostream>
#include <string>
using namespace std;

class direccion {
private:
    string calle;
    int numero;
    string departamento;
public:
    direccion();
    direccion(string calle, int numero, string departamento);

    string getCalle();
    int getNumero();
    string getDepartamento();
};