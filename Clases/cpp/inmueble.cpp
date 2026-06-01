#include "../h/inmueble.h"

inmueble::inmueble() {}

inmueble::inmueble(direccion dir, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble) {
    this->dir = dir;
    this->superficie = superficie;
    this->anioConstruccion = anioConstruccion;
    this->codigo = codigo;
    this->tipoInmueble = tipoInmueble;
}

int inmueble::getCodigo() {
    return codigo;
}

float inmueble::getSuperficie() {
    return superficie;
}

direccion inmueble::getDireccion() {
    return dir;
}

int inmueble::getAnioConstruccion() {
    return anioConstruccion;
}

TipoInmueble inmueble::getTipoInmueble() {
    return tipoInmueble;
}

dtinmueble inmueble::crearDTInmueble() {
    dtdireccion dtDir(
        dir.getNumero(),
        dir.getCalle(),
        dir.getDepartamento()
    );

    return dtinmueble(
        dtDir,
        superficie,
        anioConstruccion,
        codigo,
        tipoInmueble
    );
}

inmueble::~inmueble() {}