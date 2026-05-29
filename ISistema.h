#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include <set>
#include <string>
#include "Clases/h/TipoUsuario.h"
#include "Clases/h/TipoInmueble.h"
#include "Clases/h/TipoTecho.h"
#include "DataType/h/dtcuentabancaria.h"
#include "DataType/h/dtdireccion.h"
#include "DataType/h/dtpropietario.h"

using namespace std;

class ISistema {
    public:
        virtual ~ISistema();

        virtual bool existeUsuario(string nickname, string pass, string nombre, string email, TipoUsuario tipoUsuario) = 0;
        virtual void altaCliente(string apellido, int documento) = 0;
        virtual void altaPropietario(int telefono, dtcuentabancaria cuenta) = 0;
        virtual void altaInmobiliaria(dtdireccion direccion, int telefono, string url) = 0;

        virtual bool existeInmueble(int numPuerta, string calle, string departamento, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble) = 0;
        virtual void altaCasa(bool horizontal, TipoTecho tipoTecho) = 0;
        virtual void altaApartamento(int numeroPiso, bool ascensor, float gastosComunes) = 0;

        virtual set<dtpropietario> listarPropietarios() = 0;
        virtual void seleccionarPropietario(string nickname) = 0;
};
#endif