#pragma once

#include <iostream>
#include <string>
#include "../../ICollection/interfaces/ICollection.h"
#include "usuario.h"
#include "direccion.h"

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

    direccion getDireccion();
    int getTelefono();
    string getUrl();
    ICollection* getPropietariosRepresentados();
    ICollection* getAdministraciones();
};