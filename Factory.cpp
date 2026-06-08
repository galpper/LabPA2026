#include "Factory.h"

ISistema * Factory::getSistema() {
    return Sistema::getInstance();
}

void Factory::destroySistema() {
    Sistema::destroyInstance();
}
