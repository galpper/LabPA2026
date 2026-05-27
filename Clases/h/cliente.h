#pragma once

#include <string>
#include "usuario.h"

using namespace std;

class cliente : public usuario {

private:
    string apellido;
    int documento;

public:
    cliente();
    cliente(string nickname, string contrasena, string nombre, string email, string apellido, int documento);
    string getApellido();
    int getDocumento();
};