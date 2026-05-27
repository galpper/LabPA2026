#pragma once

#include <iostream>
#include <string>
#include "../../ICollection/interfaces/ICollectible.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "TipoPublicacion.h"
#include "inmueble.h"
#include "inmobiliaria.h"

using namespace std;

class publicacion : public ICollectible {
private:
    string fecha;
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
    publicacion(string fecha, TipoPublicacion tipo, string texto, int idPublicacion, float precio, bool activa, inmueble* inmueblePublicado, inmobiliaria* inmobiliariaPropietaria);
    float getPrecio();
    string getTexto();
    bool getActiva();
    TipoPublicacion getTipo();
    string getFecha();
    int getIdPublicacion();
    inmueble* getInmueble();
    inmobiliaria* getInmobiliaria();
    ICollection* getAgendas();
    void setActiva(bool activa);
};