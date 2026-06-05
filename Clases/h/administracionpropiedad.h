#pragma once

#include <string>
#include <set>
#include "inmueble.h"
class inmobiliaria;
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "../../DataType/h/dtpublicacion.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"
#include "../../DataType/h/dtinmueble.h"
#include "../../DataType/h/DTFecha.h"

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

    dtinmueble armarDTInmueble();
    bool existePublicacion(TipoPublicacion tipo, DTFecha fecha);
    void crearPublicacion(TipoPublicacion tipo, string texto, float precio, DTFecha fecha, int idPublicacion);
    bool existeInmueble(int codigoInmueble);
    set<dtpublicacion> armarDTPublicacion(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm);

    virtual ~administracionpropiedad();
};