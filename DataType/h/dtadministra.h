#pragma once

#include <string>

using namespace std;

class dtadministra {
private:
    string fechaInicio;
    int codigoInmueble;
    string nicknameInmobiliaria;

public:
    dtadministra();
    dtadministra(string fechaInicio, int codigoInmueble, string nicknameInmobiliaria);

    string getFechaInicio();
    int getCodigoInmueble();
    string getNicknameInmobiliaria();
    bool operator<(const dtadministra& other) const {
        if (fechaInicio != other.fechaInicio) return fechaInicio < other.fechaInicio;
        if (codigoInmueble != other.codigoInmueble) return codigoInmueble < other.codigoInmueble;
        return nicknameInmobiliaria < other.nicknameInmobiliaria;
    }
};
