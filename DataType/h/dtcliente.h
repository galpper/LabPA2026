#pragma once

#include <string>
#include "../../Clases/h/TipoUsuario.h"

using namespace std;

class dtcliente {
private:
    string nickname;
    string nombre;
    string email;
    string apellido;
    int documento;

public:
    dtcliente();
    dtcliente(string nickname, string nombre, string email, string apellido, int documento);

    string getNickname();
    string getNombre();
    string getEmail();
    string getApellido();
    int getDocumento();
    bool operator<(const dtcliente& other) const {
        return nickname < other.nickname;
    }
};
