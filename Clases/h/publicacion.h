#pragma once

#include <iostream>
#include <string>
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "TipoPublicacion.h"
#include "inmueble.h"
#include "DataType/h/DTFecha.h"

using namespace std;
class inmobiliaria;
class publicacion : public ICollectible {
private:
    DTFecha fecha;
    TipoPublicacion tipo;
    string texto;
    int idPublicacion;
    float precio;
    bool activa;
    inmueble* inmueblePublicado;
    inmobiliaria* inmobiliariaPropietaria;
    ICollection* agendas;

public:
    publicacion();
    virtual ~publicacion();
    publicacion(DTFecha fecha, TipoPublicacion tipo, string texto, int idPublicacion, float precio, bool activa, inmueble* inmueblePublicado, inmobiliaria* inmobiliariaPropietaria);
    float getPrecio();
    string getTexto();
    bool getActiva();
    TipoPublicacion getTipo();
    DTFecha getFecha();
    int getIdPublicacion();
    inmueble* getInmueble();
    inmobiliaria* getInmobiliaria();
    ICollection* getAgendas();
    void setActiva(bool activa);
};