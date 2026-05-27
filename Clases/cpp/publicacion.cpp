#include "../h/publicacion.h"
#include "../../ICollection/collections/List.h"

publicacion::publicacion() {
    agendas = new List();
}
publicacion::publicacion(string fecha, TipoPublicacion tipo, string texto, int idPublicacion, float precio, bool activa, inmueble* inmueblePublicado, inmobiliaria* inmobiliariaPropietaria) {
    this->fecha = fecha;
    this->tipo = tipo;
    this->texto = texto;
    this->idPublicacion = idPublicacion;
    this->precio = precio;
    this->activa = activa;
    this->inmueblePublicado = inmueblePublicado;
    this->inmobiliariaPropietaria = inmobiliariaPropietaria;
    agendas = new List();
}

int publicacion::getIdPublicacion() {
    return idPublicacion;
}

publicacion::~publicacion() {
    delete agendas;
}

float publicacion::getPrecio() {
    return precio;
}

string publicacion::getTexto() {
    return texto;
}

bool publicacion::getActiva() {
    return activa;
}

TipoPublicacion publicacion::getTipo() {
    return tipo;
}

string publicacion::getFecha() {
    return fecha;
}

inmueble* publicacion::getInmueble() {
    return inmueblePublicado;
}
inmobiliaria* publicacion::getInmobiliaria() {
    return inmobiliariaPropietaria;
}
ICollection* publicacion::getAgendas() {
    return agendas;
}
void publicacion::setActiva(bool activa) {
    this->activa = activa;
}
