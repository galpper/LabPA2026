#pragma once

#include <iostream>
#include <string>
#include "../../ICollection/interfaces/ICollection.h"
#include "usuario.h"
#include "direccion.h"
#include "Clases/h/TipoPublicacion.h"
#include "Clases/h/administracionpropiedad.h"
#include "../../DataType/h/DTFecha.h"

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
    bool crearPublicacion(int codigoInmueble, TipoPublicacion tipo, string texto, float precio, DTFecha fechaActual, int idPublicacion);
};