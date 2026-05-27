#include "../h/casa.h"

casa::casa() {}

casa::casa(direccion dir, float superficie, int anioConstruccion, int codigo, bool horizontal, TipoTecho tipoTecho)
: inmueble(dir, superficie, anioConstruccion, codigo, TipoInmueble::CASA) {

    this->horizontal = horizontal;
    this->tipoTecho = tipoTecho;
}

bool casa::getHorizontal() {
    return horizontal;
}

TipoTecho casa::getTipoTecho() {
    return tipoTecho;
}