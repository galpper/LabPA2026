#include "../h/administracionpropiedad.h"
#include "../../ICollection/collections/List.h"
#include "../h/publicacion.h"
#include "../h/inmobiliaria.h"

administracionpropiedad::administracionpropiedad() {
    this->fechaInicio = "";
    this->inm = nullptr;
    this->inmob = nullptr;
    this->publicaciones = new List();
}

administracionpropiedad::administracionpropiedad(string fechaInicio, inmueble* inm, inmobiliaria* inmob) {
    this->fechaInicio = fechaInicio;
    this->inm = inm;
    this->inmob = inmob;
    this->publicaciones = new List();
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

ICollection* administracionpropiedad::getPublicaciones() {
    return publicaciones;
}

dtinmueble administracionpropiedad::armarDTInmueble() {
    inmueble* inmVal = getInmueble();
    dtdireccion dtDir(
        inmVal->getDireccion().getNumero(),
        inmVal->getDireccion().getCalle(),
        inmVal->getDireccion().getDepartamento()
    );
    return dtinmueble(
        fechaInicio,
        dtDir,
        inmVal->getSuperficie(),
        inmVal->getAnioConstruccion(),
        inmVal->getCodigo(),
        inmVal->getTipoInmueble()
    );
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

set<dtpublicacion> administracionpropiedad::armarDTPublicacion(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm) {
    set<dtpublicacion> res;
    bool ok = (tipoInm == TipoInmueble::AMBOS) || (tipoInm == inm->getTipoInmueble());
    if (!ok) {
        return res;
    }
    IIterator* it = publicaciones->getIterator();
    while (it->hasCurrent()) {
        publicacion* p = (publicacion*) it->getCurrent();
        if (p->getActiva() && p->getTipo() == tipoPub && p->getPrecio() >= precioMin && p->getPrecio() <= precioMax) {
            DTFecha f = p->getFecha();
            string fStr = to_string(f.getDia()) + "/" + to_string(f.getMes()) + "/" + to_string(f.getAnio());
            dtpublicacion dt(p->getIdPublicacion(), fStr, p->getTexto(), p->getPrecio(), inmob->getNombre());
            res.insert(dt);
        }
        it->next();
    }
    delete it;
    return res;
}

administracionpropiedad::~administracionpropiedad() {
    IIterator* it = publicaciones->getIterator();
    while (it->hasCurrent()) {
        ICollectible* p = it->getCurrent();
        delete p;
        it->next();
    }
    delete it;
    delete publicaciones;
}
