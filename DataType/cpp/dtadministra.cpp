#include "../h/dtadministra.h"

dtadministra::dtadministra() {
    this->fechaInicio = "";
    this->codigoInmueble = 0;
    this->nicknameInmobiliaria = "";
}

dtadministra::dtadministra(string fechaInicio, int codigoInmueble, string nicknameInmobiliaria) {
    this->fechaInicio = fechaInicio;
    this->codigoInmueble = codigoInmueble;
    this->nicknameInmobiliaria = nicknameInmobiliaria;
}

string dtadministra::getFechaInicio() {
    return this->fechaInicio;
}

int dtadministra::getCodigoInmueble() {
    return this->codigoInmueble;
}

string dtadministra::getNicknameInmobiliaria() {
    return this->nicknameInmobiliaria;
}
