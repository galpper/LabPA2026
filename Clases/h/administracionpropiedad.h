#pragma once

#include <string>
#include "inmueble.h"
#include "inmobiliaria.h"
#include "../../ICollection/interfaces/ICollectible.h"

using namespace std;

class administracionpropiedad : public ICollectible {

private:
    string fechaInicio;
    inmueble* inm;
    inmobiliaria* inmob;

public:

    administracionpropiedad();

    administracionpropiedad(string fechaInicio, inmueble* inm, inmobiliaria* inmob);

    string getFechaInicio();

    inmueble* getInmueble();

    inmobiliaria* getInmobiliaria();

    virtual ~administracionpropiedad();
};