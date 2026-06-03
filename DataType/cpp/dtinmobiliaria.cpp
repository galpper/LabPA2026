#include "../h/dtinmobiliaria.h"

dtinmobiliaria::dtinmobiliaria() {}

dtinmobiliaria::dtinmobiliaria(string nickname, string contrasena, string nombre, string email, TipoUsuario tipoUsuario, dtdireccion direccion, int telefono, string url) {
    this->nickname = nickname;
    this->contrasena = contrasena;
    this->nombre = nombre;
    this->email = email;
    this->tipoUsuario = tipoUsuario;
    this->direccion = direccion;
    this->telefono = telefono;
    this->url = url;
}

dtinmobiliaria::dtinmobiliaria(string nickname, string nombre){
    this->nickname = nickname;
    this->nombre = nombre;
}

string dtinmobiliaria::getNickname() {
    return nickname;
}

string dtinmobiliaria::getContrasena() {
    return contrasena;
}

string dtinmobiliaria::getNombre() {
    return nombre;
}

string dtinmobiliaria::getEmail() {
    return email;
}

TipoUsuario dtinmobiliaria::getTipoUsuario() {
    return tipoUsuario;
}

dtdireccion dtinmobiliaria::getDireccion() {
    return direccion;
}

int dtinmobiliaria::getTelefono() {
    return telefono;
}

string dtinmobiliaria::getUrl() {
    return url;
}

bool dtinmobiliaria::operator<(const dtinmobiliaria& otro) const {
    return this->nickname < otro.nickname; 
}