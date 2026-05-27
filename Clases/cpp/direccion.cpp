#include "../h/direccion.h"

direccion::direccion() {}

direccion::direccion(string calle, int numero, string departamento) {
    this->calle = calle;
    this->numero = numero;
    this->departamento = departamento;
}

string direccion::getCalle() {
    return calle;
}

int direccion::getNumero() {
    return numero;
}

string direccion::getDepartamento() {
    return departamento;
}