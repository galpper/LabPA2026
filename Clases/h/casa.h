#pragma once

#include <string>
#include "inmueble.h"
#include "TipoTecho.h"

class casa : public inmueble {
private:
    bool horizontal;
    TipoTecho tipoTecho;

public:
    casa();

    casa(direccion dir, float superficie, int anioConstruccion, int codigo, bool horizontal, TipoTecho tipoTecho);
    bool getHorizontal();
    TipoTecho getTipoTecho();
};