#include "../h/administracionpropiedad.h"

administracionpropiedad::administracionpropiedad() {}

administracionpropiedad::administracionpropiedad(string fechaInicio, inmueble* inm, inmobiliaria* inmob) {
    this->fechaInicio = fechaInicio;
    this->inm = inm;
    this->inmob = inmob;

    publicaciones = new List();
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

ICollection* administracionpropiedad::getPublicaciones(){
    return publicaciones;
}

bool administracionpropiedad::existeInmueble(int codigoInmueble){
    return inm->getCodigo() == codigoInmueble;
}

bool administracionpropiedad::existePublicacion(TipoPublicacion tipo, DTFecha fecha){
    IIterator* it = publicaciones->getIterator();

    while(it->hasCurrent()){
        publicacion* p = (publicacion*) it->getCurrent();

        if(p->getTipo() == tipo && p->getFecha() == fecha){
            delete it;
            return true;
        }
        it->next();
    }

    delete it;
    return false;
}

void administracionpropiedad::crearPublicacion(TipoPublicacion tipo, string texto, float precio, DTFecha fecha, int idPublicacion){
    publicacion* p = new publicacion(
        fecha,
        tipo,
        texto,
        idPublicacion,
        precio,
        true,
        inm,
        inmob
    );

    publicaciones->add(p);
}

administracionpropiedad::~administracionpropiedad() {}
