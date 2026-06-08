#include "Sistema.h"
#include <iostream>
#include <string>
#include <set>
#include "ISistema.h"
#include <ctime>

// Clases
#include "Clases/h/cliente.h"
#include "Clases/h/propietario.h"
#include "Clases/h/inmobiliaria.h"
#include "Clases/h/casa.h"
#include "Clases/h/apartamento.h"
#include "Clases/h/administracionpropiedad.h"
#include "Clases/h/publicacion.h"
#include "Clases/h/agenda.h"

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

// Listar inmobiliarias registradas.
set<dtinmobiliaria> Sistema::listarInmobiliarias() {
    set<dtinmobiliaria> listadoInmobiliarias;
    IIterator * iteradorUsuarios = usuarios->getIterator();
    while (iteradorUsuarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorUsuarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * inmobiliariaActual = (inmobiliaria*) usuarioActual;
            dtdireccion direccionDT(inmobiliariaActual->getDireccion().getNumero(), inmobiliariaActual->getDireccion().getCalle(), inmobiliariaActual->getDireccion().getDepartamento());
            dtinmobiliaria inmobiliariaDT(inmobiliariaActual->getNickname(), inmobiliariaActual->getContrasena(), inmobiliariaActual->getNombre(), inmobiliariaActual->getEmail(), inmobiliariaActual->getTipoUsuario(), direccionDT, inmobiliariaActual->getTelefono(), inmobiliariaActual->getUrl());
            listadoInmobiliarias.insert(inmobiliariaDT);
        }
        iteradorUsuarios->next();
    }
    delete iteradorUsuarios;
    return listadoInmobiliarias;
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

set<dtinmueble> Sistema::seleccionarInmueble(string nickname){
    set<dtinmueble> res;
    String k(nickname.c_str());
    usuario * u = (usuario*) usuarios->find(&k);

    if (u != nullptr && u->getTipoUsuario() == TipoUsuario::INMOBILIARIA){
        inmobiliariaActual = (inmobiliaria*) u;
        IIterator * it = inmobiliariaActual->getAdministraciones()->getIterator();

        while(it->hasCurrent()){
            administracionpropiedad * ap = (administracionpropiedad*) it->getCurrent();
            res.insert(ap->armarDTInmueble());
            it->next();
        }

        delete it;
    }
    return res;
}

bool Sistema::altaPublicacion(int codigoInmueble, TipoPublicacion tipo, string texto, float precio){
    time_t tiempoActual = time(0);
    tm* fechaLocal = localtime(&tiempoActual);
    int dia = fechaLocal->tm_mday;
    int mes = fechaLocal->tm_mon + 1;
    int anio = fechaLocal->tm_year + 1900;
    int idPublicacion = ++ultimoIdPublicacion;

    return inmobiliariaActual->crearPublicacion(
        codigoInmueble,
        tipo,
        texto,
        precio,
        fechaActual = DTFecha(dia,mes,anio),
        idPublicacion
    );
}

int Sistema::generarIdPublicacion() {
    return ++ultimoIdPublicacion;
}

void Sistema::ingresarDatosPublicacion(TipoPublicacion tipo, string texto, float precio) {
    (void)tipo; (void)texto; (void)precio;
}

DTFecha Sistema::obtenerFecha() {
    // Retorna la fecha del sistema o actual
    return fechaActual;
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
    cliente* c3 = new cliente("cli3", "pass6", "Carlos Ruiz", "carlos@gmail.com", "Ruiz", 11223344);
    cliente* c4 = new cliente("cli4", "pass7", "Laura Sosa", "laura@gmail.com", "Sosa", 55667788);
    usuarios->add(new String("cli1"), c1);
    usuarios->add(new String("cli2"), c2);
    usuarios->add(new String("cli3"), c3);
    usuarios->add(new String("cli4"), c4);

    // 2. Propietarios
    dtcuentabancaria cuenta1(11111, "BROU");
    propietario* p1 = new propietario("prop1", "pass3", "Pedro Rodriguez", "pedro@gmail.com", 99111222, cuenta1);
    dtcuentabancaria cuenta2(22222, "Santander");
    propietario* p2 = new propietario("prop2", "pass4", "Maria Lopez", "maria@gmail.com", 99333444, cuenta2);
    dtcuentabancaria cuenta3(33333, "BBVA");
    propietario* p3 = new propietario("prop3", "pass8", "Julio Dutra", "julio@gmail.com", 99555666, cuenta3);
    dtcuentabancaria cuenta4(44444, "Itaú");
    propietario* p4 = new propietario("prop4", "pass9", "Elena Fernandez", "elena@gmail.com", 99777888, cuenta4);
    usuarios->add(new String("prop1"), p1);
    usuarios->add(new String("prop2"), p2);
    usuarios->add(new String("prop3"), p3);
    usuarios->add(new String("prop4"), p4);

    // 3. Inmobiliarias
    direccion dirInmo1("18 de Julio", 1234, "Montevideo");
    inmobiliaria* inmo1 = new inmobiliaria("inmo1", "pass5", "Inmobiliaria Montevideo", "contacto@inmomvd.com", dirInmo1, 24001122, "www.inmomvd.com");
    direccion dirInmo2("Sarmiento", 850, "Montevideo");
    inmobiliaria* inmo2 = new inmobiliaria("inmo2", "pass10", "Inmobiliaria Pocitos", "contacto@inmopocitos.com", dirInmo2, 27003344, "www.inmopocitos.com");
    direccion dirInmo3("Arazati", 120, "San Jose");
    inmobiliaria* inmo3 = new inmobiliaria("inmo3", "pass11", "Inmobiliaria San Jose", "contacto@inmosanjose.com", dirInmo3, 43425566, "www.inmosanjose.com");
    usuarios->add(new String("inmo1"), inmo1);
    usuarios->add(new String("inmo2"), inmo2);
    usuarios->add(new String("inmo3"), inmo3);

    // 4. Inmuebles
    direccion dirCasa1("Av. Italia", 100, "Montevideo");
    casa* casa1 = new casa(dirCasa1, 150.5, 2015, 101, true, TipoTecho::PLANO);
    p1->getInmuebles()->add(casa1);
    inmuebles->add(new Integer(101), casa1);

    direccion dirApto1("Buxareo", 502, "Montevideo");
    apartamento* apto1 = new apartamento(dirApto1, 75.0, 2020, 102, 5, true, 8500.0);
    p1->getInmuebles()->add(apto1);
    inmuebles->add(new Integer(102), apto1);

    direccion dirCasa2("Agraciada", 3400, "Montevideo");
    casa* casa2 = new casa(dirCasa2, 200.0, 2010, 103, false, TipoTecho::DOS_AGUAS);
    p3->getInmuebles()->add(casa2);
    inmuebles->add(new Integer(103), casa2);

    direccion dirApto2("Ellauri", 1120, "Montevideo");
    apartamento* apto2 = new apartamento(dirApto2, 90.0, 2018, 104, 3, true, 12000.0);
    p4->getInmuebles()->add(apto2);
    inmuebles->add(new Integer(104), apto2);

    // 5. Administraciones y representaciones
    inmo1->getPropietariosRepresentados()->add(p1);
    inmo2->getPropietariosRepresentados()->add(p3);
    inmo3->getPropietariosRepresentados()->add(p4);

    administracionpropiedad* admin1 = new administracionpropiedad("2/6/2026", casa1, inmo1);
    administracionpropiedad* admin2 = new administracionpropiedad("2/6/2026", apto1, inmo1);
    administracionpropiedad* admin3 = new administracionpropiedad("2/6/2026", casa2, inmo2);
    administracionpropiedad* admin4 = new administracionpropiedad("2/6/2026", apto2, inmo3);
    inmo1->getAdministraciones()->add(admin1);
    inmo1->getAdministraciones()->add(admin2);
    inmo2->getAdministraciones()->add(admin3);
    inmo3->getAdministraciones()->add(admin4);

    // 6. Publicaciones
    publicacion* pub1 = new publicacion("2/6/2026", TipoPublicacion::VENTA, "Hermosa casa en Av. Italia", 301, 150000.0, true, casa1, inmo1);
    publicacion* pub2 = new publicacion("2/6/2026", TipoPublicacion::ALQUILER, "Lindo apto en Buxareo", 302, 25000.0, true, apto1, inmo1);
    publicacion* pub3 = new publicacion("2/6/2026", TipoPublicacion::ALQUILER, "Casa espaciosa para alquilar", 303, 120000.0, true, casa1, inmo1);
    publicacion* pub4 = new publicacion("2/6/2026", TipoPublicacion::VENTA, "Apartamento economico venta", 304, 35000.0, true, apto1, inmo1);
    publicacion* pub5 = new publicacion("2/6/2026", TipoPublicacion::VENTA, "Espectacular propiedad Agraciada", 305, 280000.0, true, casa2, inmo2);
    publicacion* pub6 = new publicacion("2/6/2026", TipoPublicacion::ALQUILER, "Apartamento luminoso Ellauri", 306, 45000.0, true, apto2, inmo3);
    
    admin1->getPublicaciones()->add(pub1);
    admin1->getPublicaciones()->add(pub3);
    admin2->getPublicaciones()->add(pub2);
    admin2->getPublicaciones()->add(pub4);
    admin3->getPublicaciones()->add(pub5);
    admin4->getPublicaciones()->add(pub6);
}


// Seleccionar inmobiliaria por nickname.
set<dtinmueblepropietario> Sistema::seleccionarInmobiliaria(string nickname) {
    set<dtinmueblepropietario> inmueblesDePropietarios;
    temp_selectedInmoNickname = nickname;
    
    String claveInmobiliaria(nickname.c_str());
    usuario * usuarioEncontrado = (usuario*) usuarios->find(&claveInmobiliaria);
    if (usuarioEncontrado != nullptr && usuarioEncontrado->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
        inmobiliaria * inmobiliariaSeleccionada = (inmobiliaria*) usuarioEncontrado;
        IIterator * iteradorPropietarios = inmobiliariaSeleccionada->getPropietariosRepresentados()->getIterator();
        while (iteradorPropietarios->hasCurrent()) {
            propietario * propietarioRepresentado = (propietario*) iteradorPropietarios->getCurrent();
            IIterator * iteradorInmuebles = propietarioRepresentado->getInmuebles()->getIterator();
            while (iteradorInmuebles->hasCurrent()) {
                inmueble * inmuebleDelPropietario = (inmueble*) iteradorInmuebles->getCurrent();
                dtdireccion direccionDT(inmuebleDelPropietario->getDireccion().getNumero(), inmuebleDelPropietario->getDireccion().getCalle(), inmuebleDelPropietario->getDireccion().getDepartamento());
                dtinmueblepropietario inmueblePropietarioDT(inmuebleDelPropietario->getCodigo(), direccionDT, propietarioRepresentado->getNombre());
                inmueblesDePropietarios.insert(inmueblePropietarioDT);
                iteradorInmuebles->next();
            }
            delete iteradorInmuebles;
            iteradorPropietarios->next();
        }
        delete iteradorPropietarios;
    }
    return inmueblesDePropietarios;
}

// Registrar administracion de propiedad.
void Sistema::altaAdministracionPropiedad(int codigoInmueble) {
    String claveInmobiliaria(temp_selectedInmoNickname.c_str());
    usuario * usuarioEncontrado = (usuario*) usuarios->find(&claveInmobiliaria);
    if (usuarioEncontrado != nullptr && usuarioEncontrado->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
        inmobiliaria * inmobiliariaActual = (inmobiliaria*) usuarioEncontrado;
        
        IIterator * iteradorAdministraciones = inmobiliariaActual->getAdministraciones()->getIterator();
        while (iteradorAdministraciones->hasCurrent()) {
            administracionpropiedad * administracionActual = (administracionpropiedad*) iteradorAdministraciones->getCurrent();
            if (administracionActual->getInmueble()->getCodigo() == codigoInmueble) {
                delete iteradorAdministraciones;
                return;
            }
            iteradorAdministraciones->next();
        }
        delete iteradorAdministraciones;

        Integer claveInmueble(codigoInmueble);
        inmueble * inmuebleEncontrado = (inmueble*) inmuebles->find(&claveInmueble);
        if (inmuebleEncontrado != nullptr) {
            time_t tiempoActual = time(0);
            tm* fechaLocal = localtime(&tiempoActual);
            string fechaDeInicio = to_string(fechaLocal->tm_mday) + "/" + to_string(fechaLocal->tm_mon + 1) + "/" + to_string(fechaLocal->tm_year + 1900);
            
            administracionpropiedad * nuevaAdministracion = new administracionpropiedad(fechaDeInicio, inmuebleEncontrado, inmobiliariaActual);
            inmobiliariaActual->getAdministraciones()->add(nuevaAdministracion);
        }
    }
}

// Listar clientes.
set<dtcliente> Sistema::listarClientes() {
    set<dtcliente> conjuntoClientes;
    IIterator * iteradorUsuarios = usuarios->getIterator();
    while (iteradorUsuarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorUsuarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::CLIENTE) {
            cliente * clienteActual = (cliente*) usuarioActual;
            dtcliente datosCliente(clienteActual->getNickname(), clienteActual->getNombre(), clienteActual->getEmail(), clienteActual->getApellido(), clienteActual->getDocumento());
            conjuntoClientes.insert(datosCliente);
        }
        iteradorUsuarios->next();
    }
    delete iteradorUsuarios;
    return conjuntoClientes;
}

// Listar administraciones.
set<dtadministra> Sistema::listarAdministraciones() {
    set<dtadministra> conjuntoAdministraciones;
    IIterator * iteradorUsuarios = usuarios->getIterator();
    while (iteradorUsuarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorUsuarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * inmobiliariaActual = (inmobiliaria*) usuarioActual;
            IIterator * iteradorAdministraciones = inmobiliariaActual->getAdministraciones()->getIterator();
            while (iteradorAdministraciones->hasCurrent()) {
                administracionpropiedad * administracionActual = (administracionpropiedad*) iteradorAdministraciones->getCurrent();
                dtadministra datosAdministracion(administracionActual->getFechaInicio(), administracionActual->getInmueble()->getCodigo(), inmobiliariaActual->getNickname());
                conjuntoAdministraciones.insert(datosAdministracion);
                iteradorAdministraciones->next();
            }
            delete iteradorAdministraciones;
        }
        iteradorUsuarios->next();
    }
    delete iteradorUsuarios;
    return conjuntoAdministraciones;
}

// Listar todas las publicaciones.
set<dtpublicacion> Sistema::listarTodasPublicaciones() {
    set<dtpublicacion> conjuntoPublicaciones;
    IIterator * iteradorUsuarios = usuarios->getIterator();
    while (iteradorUsuarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorUsuarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * inmobiliariaActual = (inmobiliaria*) usuarioActual;
            IIterator * iteradorAdministraciones = inmobiliariaActual->getAdministraciones()->getIterator();
            while (iteradorAdministraciones->hasCurrent()) {
                administracionpropiedad * administracionActual = (administracionpropiedad*) iteradorAdministraciones->getCurrent();
                IIterator * iteradorPublicaciones = administracionActual->getPublicaciones()->getIterator();
                while (iteradorPublicaciones->hasCurrent()) {
                    publicacion * publicacionActual = (publicacion*) iteradorPublicaciones->getCurrent();
                    DTFecha f = publicacionActual->getFecha();
                    string fStr = to_string(f.getDia()) + "/" + to_string(f.getMes()) + "/" + to_string(f.getAnio());
                    dtpublicacion datosPublicacion(publicacionActual->getIdPublicacion(), fStr, publicacionActual->getTexto(), publicacionActual->getPrecio(), inmobiliariaActual->getNickname());
                    conjuntoPublicaciones.insert(datosPublicacion);
                    iteradorPublicaciones->next();
                }
                delete iteradorPublicaciones;
                iteradorAdministraciones->next();
            }
            delete iteradorAdministraciones;
        }
        iteradorUsuarios->next();
    }
    delete iteradorUsuarios;
    return conjuntoPublicaciones;
}

// Listar todos los inmuebles.
set<dtinmueble> Sistema::listarTodosInmuebles() {
    set<dtinmueble> conjuntoInmuebles;
    IIterator * iteradorInmuebles = inmuebles->getIterator();
    while (iteradorInmuebles->hasCurrent()) {
        inmueble * inmuebleActual = (inmueble*) iteradorInmuebles->getCurrent();
        dtdireccion direccionDT(inmuebleActual->getDireccion().getNumero(), inmuebleActual->getDireccion().getCalle(), inmuebleActual->getDireccion().getDepartamento());
        dtinmueble datosInmueble("", direccionDT, inmuebleActual->getSuperficie(), inmuebleActual->getAnioConstruccion(), inmuebleActual->getCodigo(), inmuebleActual->getTipoInmueble());
        conjuntoInmuebles.insert(datosInmueble);
        iteradorInmuebles->next();
    }
    delete iteradorInmuebles;
    return conjuntoInmuebles;
}
set<dtinmueble> Sistema::listarTodosInmueblesConPropietario() {
    set<dtinmueble> conjuntoInmuebles;
    
    IIterator * iteradorPropietarios = usuarios->getIterator();
    while (iteradorPropietarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorPropietarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::PROPIETARIO) {
            propietario * propietarioActual = (propietario*) usuarioActual;
            IIterator * iteradorInmuebles = propietarioActual->getInmuebles()->getIterator();
            while (iteradorInmuebles->hasCurrent()) {
                inmueble * inmuebleActual = (inmueble*) iteradorInmuebles->getCurrent();
                dtdireccion direccionDT(inmuebleActual->getDireccion().getNumero(), inmuebleActual->getDireccion().getCalle(), inmuebleActual->getDireccion().getDepartamento());
                dtinmueble datosInmueble("", direccionDT, inmuebleActual->getSuperficie(), inmuebleActual->getAnioConstruccion(), inmuebleActual->getCodigo(), inmuebleActual->getTipoInmueble());
                conjuntoInmuebles.insert(datosInmueble);
                iteradorInmuebles->next();
            }
            delete iteradorInmuebles;
        }
        iteradorPropietarios->next();
    }
    delete iteradorPropietarios;
    return conjuntoInmuebles;
}


// Eliminar inmueble.
void Sistema::eliminarInmueble(int codigoInmueble) {
    Integer claveInmueble(codigoInmueble);
    inmueble * inmuebleAEliminar = (inmueble*) inmuebles->find(&claveInmueble);
    
    if (inmuebleAEliminar == nullptr) {
        return;
    }
    
    IIterator * iteradorUsuarios = usuarios->getIterator();
    administracionpropiedad * administracionAEliminar = nullptr;
    inmobiliaria * inmobiliariaConAdmin = nullptr;
    
    while (iteradorUsuarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorUsuarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::INMOBILIARIA) {
            inmobiliaria * inmobiliariaActual = (inmobiliaria*) usuarioActual;
            IIterator * iteradorAdministraciones = inmobiliariaActual->getAdministraciones()->getIterator();
            while (iteradorAdministraciones->hasCurrent()) {
                administracionpropiedad * administracionActual = (administracionpropiedad*) iteradorAdministraciones->getCurrent();
                if (administracionActual->getInmueble()->getCodigo() == codigoInmueble) {
                    administracionAEliminar = administracionActual;
                    inmobiliariaConAdmin = inmobiliariaActual;
                    break;
                }
                iteradorAdministraciones->next();
            }
            delete iteradorAdministraciones;
            if (administracionAEliminar != nullptr) break;
        }
        iteradorUsuarios->next();
    }
    delete iteradorUsuarios;
    
    if (administracionAEliminar != nullptr) {
        if (inmobiliariaConAdmin != nullptr) {
            inmobiliariaConAdmin->getAdministraciones()->remove((ICollectible*)administracionAEliminar);
        }
        delete administracionAEliminar;
    }
    
    inmuebles->remove(&claveInmueble);
    
    IIterator * iteradorPropietarios = usuarios->getIterator();
    while (iteradorPropietarios->hasCurrent()) {
        usuario * usuarioActual = (usuario*) iteradorPropietarios->getCurrent();
        if (usuarioActual->getTipoUsuario() == TipoUsuario::PROPIETARIO) {
            propietario * propietarioActual = (propietario*) usuarioActual;
            propietarioActual->getInmuebles()->remove((ICollectible*)inmuebleAEliminar);
        }
        iteradorPropietarios->next();
    }
    delete iteradorPropietarios;
    
    delete inmuebleAEliminar;
}
