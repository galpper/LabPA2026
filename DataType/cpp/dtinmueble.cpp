#include "../h/dtinmueble.h"

dtinmueble::dtinmueble() {}

dtinmueble::dtinmueble(string fechaInicio, dtdireccion direccion, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble) {
    this->fechaInicio = fechaInicio;
    this->direccion = direccion;
    this->superficie = superficie;
    this->anioConstruccion = anioConstruccion;
    this->codigo = codigo;
    this->tipoInmueble = tipoInmueble;
}

dtinmueble::dtinmueble(dtdireccion direccion, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble) {
    this->direccion = direccion;
    this->superficie = superficie;
    this->anioConstruccion = anioConstruccion;
    this->codigo = codigo;
    this->tipoInmueble = tipoInmueble;
}

string dtinmueble::getFechaInicio() {
    return fechaInicio;
}

dtdireccion dtinmueble::getDireccion() {
    return direccion;
}

float dtinmueble::getSuperficie() {
    return superficie;
}

int dtinmueble::getAnioConstruccion() {
    return anioConstruccion;
}

int dtinmueble::getCodigo() {
    return codigo;
}

TipoInmueble dtinmueble::getTipoInmueble() {
    return tipoInmueble;
}

bool dtinmueble::operator<(const dtinmueble& otro) const {
    return this->codigo < otro.codigo;
}