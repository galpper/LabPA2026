#include "../h/dtpropietario.h"

dtpropietario::dtpropietario() {}

dtpropietario::dtpropietario(string nickname, string nombre, string email, int telefono, dtcuentabancaria cuenta) {
    this->nickname = nickname;
    this->nombre = nombre;
    this->email = email;
    this->telefono = telefono;
    this->cuenta = cuenta;
}

string dtpropietario::getNickname() {
    return nickname;
}

string dtpropietario::getNombre() {
    return nombre;
}

string dtpropietario::getEmail() {
    return email;
}

int dtpropietario::getTelefono() {
    return telefono;
}

dtcuentabancaria dtpropietario::getCuenta() {
    return cuenta;
}
