#include "Clases/h/administracionpropiedad.h"

administracionpropiedad::administracionpropiedad() {}

administracionpropiedad::administracionpropiedad(string fechaInicio, inmueble* inm, inmobiliaria* inmob) {
    this->fechaInicio = fechaInicio;
    this->inm = inm;
    this->inmob = inmob;
}

string administracionpropiedad::getFechaInicio() {
    return fechaInicio;
}

inmueble* administracionpropiedad::getInmueble() {
    return inm;
}

inmobiliaria* administracionpropiedad::getInmobiliaria() {
    return inmob;
}

dtinmueble administracionpropiedad::armarDTInmueble() {

    inmueble* inm = getInmueble();

    dtdireccion dtDir(
        inm->getDireccion().getNumero(),
        inm->getDireccion().getCalle(),
        inm->getDireccion().getDepartamento()
    );

    return dtinmueble(
        fechaInicio,
        dtDir,
        inm->getSuperficie(),
        inm->getAnioConstruccion(),
        inm->getCodigo(),
        inm->getTipoInmueble()
    );
}

administracionpropiedad::~administracionpropiedad() {}
