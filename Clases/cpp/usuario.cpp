#include "../h/usuario.h"

usuario::usuario() {}

usuario::usuario(string nickname, string contrasena, string nombre, string email, TipoUsuario tipoUsuario) {
    this->nickname = nickname;
    this->contrasena = contrasena;
    this->nombre = nombre;
    this->email = email;
    this->tipoUsuario = tipoUsuario;
}

string usuario::getNickname() {
    return nickname;
}

string usuario::getNombre() {
    return nombre;
}

string usuario::getEmail() {
    return email;
}

TipoUsuario usuario::getTipoUsuario() {
    return tipoUsuario;
}

string usuario::getContrasena() {
    return contrasena;
}

usuario::~usuario() {}