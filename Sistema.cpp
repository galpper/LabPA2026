#include "Sistema.h"
#include <iostream>
#include <string>
#include <set>
#include "ISistema.h"

// Clases
#include "Clases/h/cliente.h"
#include "Clases/h/propietario.h"
#include "Clases/h/inmobiliaria.h"
#include "Clases/h/casa.h"
#include "Clases/h/apartamento.h"

// ICollection
#include "ICollection/collections/OrderedDictionary.h"
#include "ICollection/String.h"
#include "ICollection/Integer.h"

using namespace std;

Sistema * Sistema::instance = NULL;

Sistema::Sistema() {
    usuarios = new OrderedDictionary();
    inmuebles = new OrderedDictionary();
    propietarioActual = nullptr;
    inmobiliariaActual = nullptr;
}

Sistema::~Sistema() {
    IIterator * it = usuarios->getIterator();
    while (it->hasCurrent()) {
        usuario * u = (usuario*) it->getCurrent();
        delete u;
        it->next();
    }
    delete it;
    delete usuarios;

    it = inmuebles->getIterator();
    while (it->hasCurrent()) {
        inmueble * inm = (inmueble*) it->getCurrent();
        delete inm;
        it->next();
    }
    delete it;
    delete inmuebles;
}

Sistema * Sistema::getInstance() {
    if (instance == NULL)
        instance = new Sistema();
    return instance;
}

bool Sistema::existeUsuario(string nickname, string pass, string nombre, string email, TipoUsuario tipoUsuario) {
    String k(nickname.c_str());
    if (usuarios->member(&k)) {
        // aca guardamos al propietario o a la inmobiliaria en la sesion.
        // los dejamos activos en el sistema porque el caso de uso de alta
        // de inmueble te va a pedir saber quien es el usuario de este momento.
        usuario * u = (usuario*) usuarios->find(&k);
        if (u->getTipoUsuario() == TipoUsuario::PROPIETARIO) {
            propietarioActual = (propietario*) u;
        } else if (u->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliariaActual = (inmobiliaria*) u;
        }
        return true;
    }
    temp_nickname = nickname;
    temp_pass = pass;
    temp_nombre = nombre;
    temp_email = email;
    temp_tipoUsuario = tipoUsuario;
    return false;
}

void Sistema::altaCliente(string apellido, int documento) {
    cliente * c = new cliente(temp_nickname, temp_pass, temp_nombre, temp_email, apellido, documento);
    usuarios->add(new String(temp_nickname.c_str()), c);
}

void Sistema::altaPropietario(int telefono, dtcuentabancaria cuenta) {
    propietario * p = new propietario(temp_nickname, temp_pass, temp_nombre, temp_email, telefono, cuenta);
    usuarios->add(new String(temp_nickname.c_str()), p);
    propietarioActual = p;
}

void Sistema::altaInmobiliaria(dtdireccion direccion, int telefono, string url) {
    class direccion d(direccion.getCalle(), direccion.getNumeroPuerta(), direccion.getDepartamento());
    inmobiliaria * inmo = new inmobiliaria(temp_nickname, temp_pass, temp_nombre, temp_email, d, telefono, url);
    usuarios->add(new String(temp_nickname.c_str()), inmo);
    inmobiliariaActual = inmo;
}

bool Sistema::existeInmueble(int numPuerta, string calle, string departamento, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble) {
    Integer k(codigo);
    if (inmuebles->member(&k)) {
        return true;
    }
    temp_numPuerta = numPuerta;
    temp_calle = calle;
    temp_departamento = departamento;
    temp_superficie = superficie;
    temp_anioConstruccion = anioConstruccion;
    temp_codigo = codigo;
    temp_tipoInmueble = tipoInmueble;
    return false;
}

void Sistema::altaCasa(bool horizontal, TipoTecho tipoTecho) {
    class direccion dir(temp_calle, temp_numPuerta, temp_departamento);
    casa * c = new casa(dir, temp_superficie, temp_anioConstruccion, temp_codigo, horizontal, tipoTecho);
    inmuebles->add(new Integer(temp_codigo), c);
    if (propietarioActual != nullptr) {
        propietarioActual->getInmuebles()->add(c);
    }
}

void Sistema::altaApartamento(int numeroPiso, bool ascensor, float gastosComunes) {
    class direccion dir(temp_calle, temp_numPuerta, temp_departamento);
    apartamento * a = new apartamento(dir, temp_superficie, temp_anioConstruccion, temp_codigo, numeroPiso, ascensor, gastosComunes);
    inmuebles->add(new Integer(temp_codigo), a);
    if (propietarioActual != nullptr) {
        propietarioActual->getInmuebles()->add(a);
    }
}

set<dtpropietario> Sistema::listarPropietarios() {
    set<dtpropietario> res;
    IIterator * it = usuarios->getIterator();
    while (it->hasCurrent()) {
        usuario * u = (usuario*) it->getCurrent();
        if (u->getTipoUsuario() == TipoUsuario::PROPIETARIO) {
            propietario * p = (propietario*) u;
            dtpropietario dt(p->getNickname(), p->getNombre(), p->getEmail(), p->getTelefono(), p->getCuenta());
            res.insert(dt);
        }
        it->next();
    }
    delete it;
    return res;
}

void Sistema::seleccionarPropietario(string nickname) {
    String k(nickname.c_str());
    usuario * u = (usuario*) usuarios->find(&k);
    if (u != nullptr && u->getTipoUsuario() == TipoUsuario::PROPIETARIO) {
        propietario * p = (propietario*) u;
        if (inmobiliariaActual != nullptr) {
            inmobiliariaActual->getPropietariosRepresentados()->add(p);
        }
    }
}


set<dtinmobiliaria> Sistema::listarInmobiliarias(){
    set<dtinmobiliaria> res;
    IIterator * it = usuarios->getIterator();
    while (it->hasCurrent()) {
        usuario * u = (usuario*) it->getCurrent();
        if (u->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * i = (inmobiliaria*) u;
            dtinmobiliaria dt(i->getNickname(), i->getNombre());
            res.insert(dt);
        }
        it->next();
    }
    delete it;
    return res;
}

set<dtinmueble> Sistema::seleccionarInmueble(string nickname){
    set<dtinmueble> res;
    String k(nickname.c_str());
    usuario * u = (usuario*) usuarios->find(&k);
    if (u != nullptr && u->getTipoUsuario() == TipoUsuario::INMOBILIARIA){
        inmobiliaria* i = (inmobiliaria*) u;
        IIterator * it = i->getAdministraciones()->getIterator();
        while(it->hasCurrent()){
            administracionpropiedad * ap = (administracionpropiedad*) it->getCurrent();
            res.insert(ap->armarDTInmueble());
            it->next();
        }

        delete it;
    }
    return res;
}