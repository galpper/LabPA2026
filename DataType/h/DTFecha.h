#pragma once
#include <iostream>
using namespace std;

class DTFecha {
private:
    int dia;
    int mes;
    int anio;
public:
    DTFecha(){
        this->dia = 0;
        this->mes = 0;
        this->anio = 0;
    }

    DTFecha(int dia, int mes, int anio);
    int getDia();
    int getMes();
    int getAnio();

    bool operator==(const DTFecha& otra) const {
        return dia == otra.dia && mes == otra.mes && anio == otra.anio;
    }
}; 