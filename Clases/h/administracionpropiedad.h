#pragma once

#include <string>
#include "inmueble.h"
#include "publicacion.h"
#include "../../ICollection/interfaces/ICollectible.h"
#include "DataType/h/dtinmueble.h"
#include "../../ICollection/collections/List.h"
#include "DataType/h/DTFecha.h"

using namespace std;
class inmobiliaria;
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


    virtual ~administracionpropiedad();
};