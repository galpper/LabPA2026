#include "../h/administracionpropiedad.h"

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

administracionpropiedad::~administracionpropiedad() {}