#pragma once

#include <string>

using namespace std;

class dtdireccion {

private:
    int numeroPuerta;
    string calle;
    string departamento;

public:
    dtdireccion();

    dtdireccion(int numeroPuerta, string calle, string departamento);

    int getNumeroPuerta();
    string getCalle();
    string getDepartamento();
};