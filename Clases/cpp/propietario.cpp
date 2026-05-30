#include "../h/propietario.h"
#include "../../ICollection/collections/List.h"

propietario::propietario() {
    inmuebles = new List();
}
propietario::propietario(string nickname, string contrasena, string nombre, string email, int telefono, dtcuentabancaria cuenta)
    : usuario(nickname, contrasena, nombre, email, TipoUsuario::PROPIETARIO) {

    this->telefono = telefono;
    this->cuenta = cuenta;
    this->inmuebles = new List();
}

int propietario::getTelefono() {
    return telefono;
}

dtcuentabancaria propietario::getCuenta() {
    return cuenta;
}
ICollection* propietario::getInmuebles() {
    return inmuebles;
}
propietario::~propietario() {
    delete inmuebles;
}
