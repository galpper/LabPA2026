#pragma once
#include <string>
#include "dtdireccion.h"

using namespace std;

class dtinmueblepropietario {
private:
    int codigo;
    dtdireccion direccion;
    string nombrePropietario;
public:
    dtinmueblepropietario();
    dtinmueblepropietario(int codigo, dtdireccion direccion, string nombrePropietario);
    int getCodigo() const;
    dtdireccion getDireccion() const;
    string getNombrePropietario() const;
    bool operator<(const dtinmueblepropietario& other) const;
};
