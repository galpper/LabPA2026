#pragma once

#include <string>
#include "../../Clases/h/TipoInmueble.h"
#include "dtdireccion.h"

using namespace std;

class dtinmueble {

private:
    string fechaInicio;
    dtdireccion direccion;
    float superficie;
    int anioConstruccion;
    int codigo;
    TipoInmueble tipoInmueble;

public:

    dtinmueble();

    dtinmueble(string fechaInicio, dtdireccion direccion, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble);

    dtinmueble(dtdireccion direccion, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble);

    string getFechaInicio();
    dtdireccion getDireccion();
    float getSuperficie();
    int getAnioConstruccion();
    int getCodigo();
    TipoInmueble getTipoInmueble();
};