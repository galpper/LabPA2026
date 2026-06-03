#include "../h/inmobiliaria.h"
#include "../../ICollection/collections/List.h"

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
inmobiliaria::~inmobiliaria() {
    delete propietariosRepresentados;
    delete administraciones;
}

bool inmobiliaria::crearPublicacion(int codigoInmueble, TipoPublicacion tipo, string texto, float precio, DTFecha fecha, int idPublicacion){
    IIterator* it = administraciones->getIterator();

    while(it->hasCurrent()){
        administracionpropiedad* ap = (administracionpropiedad*) it->getCurrent();
        
        if (ap->existeInmueble(codigoInmueble) && !ap->existePublicacion(tipo, fecha)) {
            ap->crearPublicacion(tipo, texto, precio, fecha, idPublicacion);
            delete it;
            return true;
        } 
        
        else if (ap->existeInmueble(codigoInmueble)) {
            delete it;
            return false;
        }

        it->next();
    }

    delete it;
    return false;
}