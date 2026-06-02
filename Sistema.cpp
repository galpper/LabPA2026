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
#include "Clases/h/administracionpropiedad.h"
#include "Clases/h/publicacion.h"

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

// Obtener instancia del sistema.
Sistema * Sistema::getInstance() {
    if (instance == NULL)
        instance = new Sistema();
    return instance;
}

// Verificar existencia de usuario.
bool Sistema::existeUsuario(string nickname, string pass, string nombre, string email, TipoUsuario tipoUsuario) {
    String k(nickname.c_str());
    if (usuarios->member(&k)) {
        // Guardar usuario activo en sesion.
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

// Registrar cliente.
void Sistema::altaCliente(string apellido, int documento) {
    cliente * c = new cliente(temp_nickname, temp_pass, temp_nombre, temp_email, apellido, documento);
    usuarios->add(new String(temp_nickname.c_str()), c);
}

// Registrar propietario.
void Sistema::altaPropietario(int telefono, dtcuentabancaria cuenta) {
    propietario * p = new propietario(temp_nickname, temp_pass, temp_nombre, temp_email, telefono, cuenta);
    usuarios->add(new String(temp_nickname.c_str()), p);
    propietarioActual = p;
}

// Registrar inmobiliaria.
void Sistema::altaInmobiliaria(dtdireccion direccion, int telefono, string url) {
    class direccion d(direccion.getCalle(), direccion.getNumeroPuerta(), direccion.getDepartamento());
    inmobiliaria * inmo = new inmobiliaria(temp_nickname, temp_pass, temp_nombre, temp_email, d, telefono, url);
    usuarios->add(new String(temp_nickname.c_str()), inmo);
    inmobiliariaActual = inmo;
}

// Verificar existencia de inmueble.
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

// Registrar casa.
void Sistema::altaCasa(bool horizontal, TipoTecho tipoTecho) {
    class direccion dir(temp_calle, temp_numPuerta, temp_departamento);
    casa * c = new casa(dir, temp_superficie, temp_anioConstruccion, temp_codigo, horizontal, tipoTecho);
    inmuebles->add(new Integer(temp_codigo), c);
    if (propietarioActual != nullptr) {
        propietarioActual->getInmuebles()->add(c);
    }
}

// Registrar apartamento.
void Sistema::altaApartamento(int numeroPiso, bool ascensor, float gastosComunes) {
    class direccion dir(temp_calle, temp_numPuerta, temp_departamento);
    apartamento * a = new apartamento(dir, temp_superficie, temp_anioConstruccion, temp_codigo, numeroPiso, ascensor, gastosComunes);
    inmuebles->add(new Integer(temp_codigo), a);
    if (propietarioActual != nullptr) {
        propietarioActual->getInmuebles()->add(a);
    }
}

// Listar propietarios.
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

// Seleccionar propietario para representar.
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

// Listar publicaciones filtradas.
set<dtpublicacion> Sistema::listarPublicaciones(TipoPublicacion tipoPub, float precioMin, float precioMax, TipoInmueble tipoInm) {
    set<dtpublicacion> res;
    IIterator * it = usuarios->getIterator();
    while (it->hasCurrent()) {
        usuario * u = (usuario*) it->getCurrent();
        if (u->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * inmo = (inmobiliaria*) u;
            set<dtpublicacion> matching = inmo->listarPublicaciones(tipoPub, precioMin, precioMax, tipoInm);
            res.insert(matching.begin(), matching.end());
        }
        it->next();
    }
    delete it;
    return res;
}

// Seleccionar publicacion y retornar su inmueble.
dtinmueble Sistema::seleccionarPublicacion(int codigo) {
    IIterator * it = usuarios->getIterator();
    while (it->hasCurrent()) {
        usuario * u = (usuario*) it->getCurrent();
        if (u->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * inmo = (inmobiliaria*) u;
            IIterator * itAdmin = inmo->getAdministraciones()->getIterator();
            while (itAdmin->hasCurrent()) {
                administracionpropiedad * admin = (administracionpropiedad*) itAdmin->getCurrent();
                IIterator * itPub = admin->getPublicaciones()->getIterator();
                while (itPub->hasCurrent()) {
                    publicacion * p = (publicacion*) itPub->getCurrent();
                    if (p->getIdPublicacion() == codigo) {
                        dtdireccion dirDT(admin->getInmueble()->getDireccion().getNumero(), 
                                          admin->getInmueble()->getDireccion().getCalle(), 
                                          admin->getInmueble()->getDireccion().getDepartamento());
                        dtinmueble dt(admin->getFechaInicio(), dirDT, 
                                      admin->getInmueble()->getSuperficie(), 
                                      admin->getInmueble()->getAnioConstruccion(), 
                                      admin->getInmueble()->getCodigo(), 
                                      admin->getInmueble()->getTipoInmueble());
                        delete itPub;
                        delete itAdmin;
                        delete it;
                        return dt;
                    }
                    itPub->next();
                }
                delete itPub;
                itAdmin->next();
            }
            delete itAdmin;
        }
        it->next();
    }
    delete it;
    return dtinmueble();
}

// Cargar datos predeterminados en el sistema.
void Sistema::cargarDatos() {
    String check("cli1");
    if (usuarios->member(&check)) {
        return;
    }
    // 1. Clientes
    cliente* c1 = new cliente("cli1", "pass1", "Juan Perez", "juan@gmail.com", "Perez", 12345678);
    cliente* c2 = new cliente("cli2", "pass2", "Ana Gomez", "ana@gmail.com", "Gomez", 87654321);
    usuarios->add(new String("cli1"), c1);
    usuarios->add(new String("cli2"), c2);

    // 2. Propietarios
    dtcuentabancaria cuenta1(11111, "BROU");
    propietario* p1 = new propietario("prop1", "pass3", "Pedro Rodriguez", "pedro@gmail.com", 99111222, cuenta1);
    dtcuentabancaria cuenta2(22222, "Santander");
    propietario* p2 = new propietario("prop2", "pass4", "Maria Lopez", "maria@gmail.com", 99333444, cuenta2);
    usuarios->add(new String("prop1"), p1);
    usuarios->add(new String("prop2"), p2);

    // 3. Inmobiliarias
    direccion dirInmo("18 de Julio", 1234, "Montevideo");
    inmobiliaria* inmo1 = new inmobiliaria("inmo1", "pass5", "Inmobiliaria Montevideo", "contacto@inmomvd.com", dirInmo, 24001122, "www.inmomvd.com");
    usuarios->add(new String("inmo1"), inmo1);

    // 4. Inmuebles
    direccion dirCasa("Av. Italia", 100, "Montevideo");
    casa* casa1 = new casa(dirCasa, 150.5, 2015, 101, true, TipoTecho::PLANO);
    p1->getInmuebles()->add(casa1);
    inmuebles->add(new Integer(101), casa1);

    direccion dirApto("Buxareo", 502, "Montevideo");
    apartamento* apto1 = new apartamento(dirApto, 75.0, 2020, 102, 5, true, 8500.0);
    p1->getInmuebles()->add(apto1);
    inmuebles->add(new Integer(102), apto1);

    // 5. Administraciones y representaciones
    inmo1->getPropietariosRepresentados()->add(p1);

    administracionpropiedad* admin1 = new administracionpropiedad("02/06/2026", casa1, inmo1);
    administracionpropiedad* admin2 = new administracionpropiedad("02/06/2026", apto1, inmo1);
    inmo1->getAdministraciones()->add(admin1);
    inmo1->getAdministraciones()->add(admin2);

    // 6. Publicaciones
    publicacion* pub1 = new publicacion("02/06/2026", TipoPublicacion::VENTA, "Hermosa casa en Av. Italia", 301, 150000.0, true, casa1, inmo1);
    publicacion* pub2 = new publicacion("02/06/2026", TipoPublicacion::ALQUILER, "Lindo apto en Buxareo", 302, 25000.0, true, apto1, inmo1);
    publicacion* pub3 = new publicacion("02/06/2026", TipoPublicacion::ALQUILER, "Casa espaciosa para alquilar", 303, 120000.0, true, casa1, inmo1);
    publicacion* pub4 = new publicacion("02/06/2026", TipoPublicacion::VENTA, "Apartamento economico venta", 304, 35000.0, true, apto1, inmo1);
    admin1->getPublicaciones()->add(pub1);
    admin1->getPublicaciones()->add(pub3);
    admin2->getPublicaciones()->add(pub2);
    admin2->getPublicaciones()->add(pub4);
}


