/*
#include "Factory.h"
#include "ISistema.h"

int main() {
    ISistema * s = Factory::getSistema();
    if (s == nullptr) {
        cout << "Error al obtener el sistema." << endl;
        return 1;
    }
}
*/
#include <iostream>

#include "Clases/h/cliente.h"
#include "Clases/h/propietario.h"
#include "Clases/h/inmobiliaria.h"

#include "Clases/h/casa.h"
#include "Clases/h/apartamento.h"

#include "Clases/h/publicacion.h"
#include "Clases/h/administracionpropiedad.h"

#include "DataType/h/dtcuentabancaria.h"

using namespace std;

int main() {

    cout << "=== PRUEBA DE CLASES ===" << endl;

    direccion dir1("18 de Julio", 1234, "Montevideo");

    dtcuentabancaria cuenta1(12345, "BROU");

    propietario* prop =
        new propietario(
            "juan123",
            "123456",
            "Juan",
            "juan@gmail.com",
            2,
            cuenta1
        );

    cout << "Propietario: "
         << prop->getNombre()
         << endl;

    casa* c1 =
        new casa(
            dir1,
            120,
            2010,
            1,
            true,
            TipoTecho::PLANO
        );

    cout << "Casa codigo: "
         << c1->getCodigo()
         << endl;

    inmobiliaria* inmob =
        new inmobiliaria(
            "inmo1",
            "abcdef",
            "Inmobiliaria Centro",
            "contacto@inmo.com",
            dir1,
            24001122,
            "www.inmo.com"
        );

    cout << "Inmobiliaria: "
         << inmob->getNombre()
         << endl;

    administracionpropiedad* admin =
        new administracionpropiedad(
            "01/06/2026",
            c1,
            inmob
        );

    cout << "Fecha admin: "
         << admin->getFechaInicio()
         << endl;

    publicacion* pub =
        new publicacion(
            "02/06/2026",
            TipoPublicacion::VENTA,
            "Hermosa casa",
            1,
            250000,
            true,
            c1,
            inmob
        );

    cout << "Publicacion: "
         << pub->getTexto()
         << endl;

    cout << "Precio: "
         << pub->getPrecio()
         << endl;

    cout << "Activa: "
         << pub->getActiva()
         << endl;

    delete prop;
    delete c1;
    delete inmob;
    delete admin;
    delete pub;

    cout << "=== FIN ===" << endl;

    return 0;
}