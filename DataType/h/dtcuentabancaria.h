#pragma once

#include <string>

using namespace std;

class dtcuentabancaria {

private:
    int numero;
    string banco;

public:
    dtcuentabancaria();

    dtcuentabancaria(int numero, string banco);

    int getNumero();
    string getBanco();
};