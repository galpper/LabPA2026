#pragma once

#include <string>
#include "../../Clases/h/TipoUsuario.h"
#include "dtcuentabancaria.h"

using namespace std;

class dtpropietario {
private:
    string nickname;
    string nombre;
    string email;
    int telefono;
    dtcuentabancaria cuenta;

public:
    dtpropietario();
    dtpropietario(string nickname, string nombre, string email, int telefono, dtcuentabancaria cuenta);

    string getNickname();
    string getNombre();
    string getEmail();
    int getTelefono();
    dtcuentabancaria getCuenta();
    bool operator<(const dtpropietario& other) const {
        return nickname < other.nickname;
    }
};
