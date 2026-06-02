#pragma once

#include <string>
#include "../../Clases/h/TipoUsuario.h"
#include "dtdireccion.h"

using namespace std;

class dtinmobiliaria {

private:
    string nickname;
    string contrasena;
    string nombre;
    string email;
    TipoUsuario tipoUsuario;
    dtdireccion direccion;
    int telefono;
    string url;

public:
    dtinmobiliaria();

    dtinmobiliaria(string nickname, string contrasena, string nombre, string email, TipoUsuario tipoUsuario, dtdireccion direccion, int telefono, string url);
    string getNickname();
    string getContrasena();
    string getNombre();
    string getEmail();
    TipoUsuario getTipoUsuario();
    dtdireccion getDireccion();
    int getTelefono();
    string getUrl();
    bool operator<(const dtinmobiliaria& other) const;
};