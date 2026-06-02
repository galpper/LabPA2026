#include "../h/administracionpropiedad.h"
#include "../../ICollection/collections/List.h"
#include "../h/publicacion.h"

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
            dtpublicacion dt(p->getIdPublicacion(), p->getFecha(), p->getTexto(), p->getPrecio(), inmob->getNombre());
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