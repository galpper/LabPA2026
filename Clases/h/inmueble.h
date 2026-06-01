#pragma once

#include <iostream>
#include <string>
#include "../../ICollection/interfaces/ICollectible.h"
#include "direccion.h"
#include "TipoInmueble.h"
#include "DataType/h/dtinmueble.h"

class inmueble : public ICollectible {
protected:
    direccion dir;
    float superficie;
    int anioConstruccion;
    int codigo;
    TipoInmueble tipoInmueble;

public:
    inmueble();

    inmueble(direccion dir, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble);

    int getCodigo();
    float getSuperficie();
    direccion getDireccion();
    int getAnioConstruccion();
    TipoInmueble getTipoInmueble();
    dtinmueble crearDTInmueble();
    virtual ~inmueble();
};