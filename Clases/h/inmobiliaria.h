#pragma once

#include <iostream>
#include <string>
#include <set>
#include "../../ICollection/interfaces/ICollection.h"
#include "usuario.h"
#include "direccion.h"
#include "../../DataType/h/dtpublicacion.h"
#include "TipoPublicacion.h"
#include "TipoInmueble.h"

class inmobiliaria : public usuario {
private:
    direccion dir;
    int telefono;
    string url;
    ICollection* propietariosRepresentados;
    ICollection* administraciones;

public:
    inmobiliaria();

    inmobiliaria(string nickname, string contrasena, string nombre, string email, direccion dir, int telefono,string url);
    virtual ~inmobiliaria();
    direccion getDireccion();
    int getTelefono();
    string getUrl();
    ICollection* getPropietariosRepresentados();
    ICollection* getAdministraciones();
    
    set<dtpublicacion> listarPublicaciones(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm);
};