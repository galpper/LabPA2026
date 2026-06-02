#include "../h/dtpublicacion.h"

dtpublicacion::dtpublicacion() {
    this->codigo = 0;
    this->fecha = "";
    this->texto = "";
    this->precio = 0.0;
    this->nombreInmobiliaria = "";
}

dtpublicacion::dtpublicacion(int codigo, string fecha, string texto, float precio, string nombreInmobiliaria) {
    this->codigo = codigo;
    this->fecha = fecha;
    this->texto = texto;
    this->precio = precio;
    this->nombreInmobiliaria = nombreInmobiliaria;
}

int dtpublicacion::getCodigo() const {
    return codigo;
}

string dtpublicacion::getFecha() const {
    return fecha;
}

string dtpublicacion::getTexto() const {
    return texto;
}

float dtpublicacion::getPrecio() const {
    return precio;
}

string dtpublicacion::getNombreInmobiliaria() const {
    return nombreInmobiliaria;
}

bool dtpublicacion::operator<(const dtpublicacion& de) const {
    return this->codigo < de.codigo;
}
