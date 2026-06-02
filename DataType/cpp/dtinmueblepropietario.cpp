#include "../h/dtinmueblepropietario.h"

dtinmueblepropietario::dtinmueblepropietario() {
    this->codigo = 0;
    this->direccion = dtdireccion();
    this->nombrePropietario = "";
}

dtinmueblepropietario::dtinmueblepropietario(int codigo, dtdireccion direccion, string nombrePropietario) {
    this->codigo = codigo;
    this->direccion = direccion;
    this->nombrePropietario = nombrePropietario;
}

int dtinmueblepropietario::getCodigo() const {
    return codigo;
}

dtdireccion dtinmueblepropietario::getDireccion() const {
    return direccion;
}

string dtinmueblepropietario::getNombrePropietario() const {
    return nombrePropietario;
}

bool dtinmueblepropietario::operator<(const dtinmueblepropietario& other) const {
    return this->codigo < other.codigo;
}
