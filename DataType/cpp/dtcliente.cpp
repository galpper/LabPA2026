#include "../h/dtcliente.h"

dtcliente::dtcliente() {
    this->nickname = "";
    this->nombre = "";
    this->email = "";
    this->apellido = "";
    this->documento = 0;
}

dtcliente::dtcliente(string nickname, string nombre, string email, string apellido, int documento) {
    this->nickname = nickname;
    this->nombre = nombre;
    this->email = email;
    this->apellido = apellido;
    this->documento = documento;
}

string dtcliente::getNickname() {
    return this->nickname;
}

string dtcliente::getNombre() {
    return this->nombre;
}

string dtcliente::getEmail() {
    return this->email;
}

string dtcliente::getApellido() {
    return this->apellido;
}

int dtcliente::getDocumento() {
    return this->documento;
}
