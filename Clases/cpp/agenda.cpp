#include "../h/agenda.h"

agenda::agenda() {}

agenda::agenda(string fecha, string texto) {
    this->fecha = fecha;
    this->texto = texto;
}

string agenda::getFecha() {
    return fecha;
}

string agenda::getTexto() {
    return texto;
}
agenda::~agenda() {}