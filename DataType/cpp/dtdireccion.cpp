#include "../h/dtdireccion.h"

dtdireccion::dtdireccion() {}

dtdireccion::dtdireccion(int numeroPuerta, string calle, string departamento) {
    this->numeroPuerta = numeroPuerta;
    this->calle = calle;
    this->departamento = departamento;
}

int dtdireccion::getNumeroPuerta() {
    return numeroPuerta;
}

string dtdireccion::getCalle() {
    return calle;
}

string dtdireccion::getDepartamento() {
    return departamento;
}