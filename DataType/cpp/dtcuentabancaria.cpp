#include "../h/dtcuentabancaria.h"

dtcuentabancaria::dtcuentabancaria() {}

dtcuentabancaria::dtcuentabancaria(int numero, string banco) {
    this->numero = numero;
    this->banco = banco;
}

int dtcuentabancaria::getNumero() {
    return numero;
}

string dtcuentabancaria::getBanco() {
    return banco;
}