#pragma once

#include <iostream>
#include <string>
#include "../../DataType/h/dtcuentabancaria.h"
#include "../../ICollection/interfaces/ICollection.h"
#include "usuario.h"

using namespace std;

class propietario : public usuario {
private:
    int telefono;
    dtcuentabancaria cuenta;
    ICollection* inmuebles;

public:
    propietario();

    propietario(string nickname, string contrasena, string nombre, string email, int telefono, dtcuentabancaria cuenta);

    int getTelefono();
    dtcuentabancaria getCuenta();
    ICollection* getInmuebles();
};