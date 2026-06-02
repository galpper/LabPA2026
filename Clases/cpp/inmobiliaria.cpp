#include "../h/inmobiliaria.h"
#include "../../ICollection/collections/List.h"
#include "../h/administracionpropiedad.h"

inmobiliaria::inmobiliaria() {
    propietariosRepresentados = new List();
    administraciones = new List();
}
inmobiliaria::inmobiliaria(string nickname, string contrasena, string nombre, string email, direccion dir, int telefono, string url)
: usuario(nickname, contrasena, nombre, email, TipoUsuario::INMOBILIARIA) {

    this->dir = dir;
    this->telefono = telefono;
    this->url = url;
    this->propietariosRepresentados = new List();
    this->administraciones = new List();
}

direccion inmobiliaria::getDireccion() {
    return dir;
}

int inmobiliaria::getTelefono() {
    return telefono;
}

string inmobiliaria::getUrl() {
    return url;
}

ICollection* inmobiliaria::getPropietariosRepresentados() {
    return propietariosRepresentados;
}

ICollection* inmobiliaria::getAdministraciones() {
    return administraciones;
}

set<dtpublicacion> inmobiliaria::listarPublicaciones(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm) {
    set<dtpublicacion> res;
    IIterator* it = administraciones->getIterator();
    while (it->hasCurrent()) {
        administracionpropiedad* admin = (administracionpropiedad*) it->getCurrent();
        set<dtpublicacion> matching = admin->armarDTPublicacion(tipoPub, precioMin, precioMax, tipoInm);
        res.insert(matching.begin(), matching.end());
        it->next();
    }
    delete it;
    return res;
}

inmobiliaria::~inmobiliaria() {
    delete propietariosRepresentados;
    delete administraciones;
}
