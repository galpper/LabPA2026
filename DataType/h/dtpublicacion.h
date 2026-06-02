#pragma once

#include <string>

using namespace std;

class dtpublicacion {
private:
    int codigo;
    string fecha;
    string texto;
    float precio;
    string nombreInmobiliaria;

public:
    dtpublicacion();
    dtpublicacion(int codigo, string fecha, string texto, float precio, string nombreInmobiliaria);

    int getCodigo() const;
    string getFecha() const;
    string getTexto() const;
    float getPrecio() const;
    string getNombreInmobiliaria() const;
    
    // Comparador para poder meterlos en un std::set ordenado por codigo
    bool operator<(const dtpublicacion& de) const;
};
