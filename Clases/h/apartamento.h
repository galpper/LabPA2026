#pragma once

#include <iostream>
#include <string>
#include "inmueble.h"

class apartamento : public inmueble {
private:
    int numeroPiso;
    bool ascensor;
    float gastosComunes;

public:
    apartamento();

    apartamento(direccion dir, float superficie, int anioConstruccion, int codigo, int numeroPiso, bool ascensor, float gastosComunes);
    int getNumeroPiso();
    bool getAscensor();
    float getGastosComunes();
};