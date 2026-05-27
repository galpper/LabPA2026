#pragma once

#include <string>
#include "../../ICollection/interfaces/ICollectible.h"
#include "TipoUsuario.h"

using namespace std;

class usuario : public ICollectible {
protected:
    string nickname;
    string contrasena;
    string nombre;
    string email;
    TipoUsuario tipoUsuario;

public:
    usuario();

    usuario(string nickname, string contrasena, string nombre, string email, TipoUsuario tipoUsuario);
    string getNickname();
    string getNombre();
    string getEmail();
    TipoUsuario getTipoUsuario();
    string getContrasena();
    virtual ~usuario();
};