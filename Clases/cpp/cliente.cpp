#include "../h/cliente.h"

cliente::cliente() {}

cliente::cliente(string nickname, string contrasena, string nombre, string email, string apellido, int documento)
: usuario(nickname, contrasena, nombre, email, TipoUsuario::CLIENTE) {
    this->apellido = apellido;
    this->documento = documento;
}

string cliente::getApellido() {
    return apellido;
}

int cliente::getDocumento() {
    return documento;
}