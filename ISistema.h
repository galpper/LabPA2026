#ifndef ISISTEMA_H
#define ISISTEMA_H

#include <iostream>
#include <set>
#include <string>
#include "Clases/h/TipoUsuario.h"
#include "Clases/h/TipoInmueble.h"
#include "Clases/h/TipoTecho.h"
#include "Clases/h/TipoPublicacion.h"
#include "Clases/h/administracionpropiedad.h"
#include "DataType/h/dtcuentabancaria.h"
#include "DataType/h/dtdireccion.h"
#include "DataType/h/dtpropietario.h"
#include "DataType/h/dtinmobiliaria.h"
#include "DataType/h/dtinmueble.h"
#include "DataType/h/dtpublicacion.h"
#include "DataType/h/dtinmueblepropietario.h"
#include "DataType/h/dtcliente.h"
#include "DataType/h/dtadministra.h"

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

        virtual set<dtinmobiliaria> listarInmobiliarias() = 0;
        virtual set<dtinmueble> seleccionarInmueble(string nickname) = 0;
        virtual bool altaPublicacion(int codigoInmueble, TipoPublicacion tipo, string texto, float precio) = 0;
        virtual void ingresarDatosPublicacion(TipoPublicacion tipo, string texto, float precio) = 0;
        virtual int generarIdPublicacion() = 0;
        virtual DTFecha obtenerFecha() = 0;
        
        virtual set<dtpublicacion> listarPublicaciones(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm) = 0;
        virtual dtinmueble seleccionarPublicacion(int codigo) = 0;
        virtual void cargarDatos() = 0;

        virtual set<dtinmueblepropietario> seleccionarInmobiliaria(string nickname) = 0;
        virtual void altaAdministracionPropiedad(int codigoInmueble) = 0;

        virtual set<dtcliente> listarClientes() = 0;
        virtual set<dtadministra> listarAdministraciones() = 0;

        virtual set<dtpublicacion> listarTodasPublicaciones() = 0;
        virtual set<dtinmueble> listarTodosInmuebles() = 0;
};
#endif