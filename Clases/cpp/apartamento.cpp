#include "../h/apartamento.h"

apartamento::apartamento() {}

apartamento::apartamento(direccion dir, float superficie, int anioConstruccion, int codigo, int numeroPiso, bool ascensor, float gastosComunes)
    : inmueble(dir, superficie, anioConstruccion, codigo, TipoInmueble::APARTAMENTO) {

    this->numeroPiso = numeroPiso;
    this->ascensor = ascensor;
    this->gastosComunes = gastosComunes;
}

int apartamento::getNumeroPiso() {
    return numeroPiso;
}

bool apartamento::getAscensor() {
    return ascensor;
}

float apartamento::getGastosComunes() {
    return gastosComunes;
}
