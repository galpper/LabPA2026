#pragma once

#include <string>
#include <set>
#include "inmueble.h"
#include "inmobiliaria.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "../../DataType/h/dtpublicacion.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"

using namespace std;

class administracionpropiedad : public ICollectible {

private:
    string fechaInicio;
    inmueble* inm;
    inmobiliaria* inmob;
    ICollection* publicaciones;

public:

    administracionpropiedad();

    administracionpropiedad(string fechaInicio, inmueble* inm, inmobiliaria* inmob);

    string getFechaInicio();

    inmueble* getInmueble();

    inmobiliaria* getInmobiliaria();

    ICollection* getPublicaciones();

    set<dtpublicacion> armarDTPublicacion(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm);

    virtual ~administracionpropiedad();
};