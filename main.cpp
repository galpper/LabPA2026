#include <iostream>
#include <set>
#include <string>

#include "Factory.h"
#include "ISistema.h"

using namespace std;

int main() {
    cout << "=== PRUEBAS ===" << endl;

    ISistema* sys = Factory::getSistema();

    // 1. Alta de Usuarios
    cout << "\n--- 1. Alta de Usuarios ---" << endl;
    
    // Propietario 1
    if (!sys->existeUsuario("prop1", "pass1", "Pedro", "pedro@gmail.com", TipoUsuario::PROPIETARIO)) {
        dtcuentabancaria cuenta1(11111, "BROU");
        sys->altaPropietario(99111222, cuenta1);
        cout << "Propietario 'prop1' dado de alta." << endl;
    } else {
        cout << "Propietario 'prop1' ya existe." << endl;
    }

    // Propietario 2
    if (!sys->existeUsuario("prop2", "pass2", "Maria", "maria@gmail.com", TipoUsuario::PROPIETARIO)) {
        dtcuentabancaria cuenta2(22222, "Santander");
        sys->altaPropietario(99333444, cuenta2);
        cout << "Propietario 'prop2' dado de alta." << endl;
    } else {
        cout << "Propietario 'prop2' ya existe." << endl;
    }

    // Cliente 1
    if (!sys->existeUsuario("cli1", "pass3", "Juan", "juan@gmail.com", TipoUsuario::CLIENTE)) {
        sys->altaCliente("Perez", 12345678);
        cout << "Cliente 'cli1' dado de alta." << endl;
    } else {
        cout << "Cliente 'cli1' ya existe." << endl;
    }

    // Inmobiliaria 1
    if (!sys->existeUsuario("inmo1", "pass4", "Inmobiliaria Montevideo", "contacto@inmomvd.com", TipoUsuario::INMOBILIARIA)) {
        dtdireccion dirInmo(1234, "18 de Julio", "Montevideo");
        sys->altaInmobiliaria(dirInmo, 24001122, "www.inmomvd.com");
        cout << "Inmobiliaria 'inmo1' dada de alta." << endl;
    } else {
        cout << "Inmobiliaria 'inmo1' ya existe." << endl;
    }

    // 2. Registrar Inmuebles para prop1
    cout << "\n--- 2. Registrar Inmuebles para prop1 ---" << endl;
    
    // Seteamos prop1 como activo
    sys->existeUsuario("prop1", "pass1", "Pedro", "pedro@gmail.com", TipoUsuario::PROPIETARIO);

    // Registrar Casa
    if (!sys->existeInmueble(100, "Av. Italia", "Montevideo", 150.5, 2015, 101, TipoInmueble::CASA)) {
        sys->altaCasa(true, TipoTecho::PLANO);
        cout << "Casa con codigo 101 registrada para prop1." << endl;
    } else {
        cout << "Inmueble 101 ya existe." << endl;
    }

    // Registrar Apartamento
    if (!sys->existeInmueble(502, "Buxareo", "Montevideo", 75.0, 2020, 102, TipoInmueble::APARTAMENTO)) {
        sys->altaApartamento(5, true, 8500.0);
        cout << "Apartamento con codigo 102 registrado para prop1." << endl;
    } else {
        cout << "Inmueble 102 ya existe." << endl;
    }

    // 3. Listar Propietarios y Seleccionar por Inmobiliaria
    cout << "\n--- 3. Listar Propietarios por Inmobiliaria ---" << endl;
    
    // Seteamos inmo1 como activa
    sys->existeUsuario("inmo1", "pass4", "Inmobiliaria Montevideo", "contacto@inmomvd.com", TipoUsuario::INMOBILIARIA);

    set<dtpropietario> props = sys->listarPropietarios();
    cout << "Lista de propietarios disponibles:" << endl;
    for (dtpropietario p : props) {
        cout << "- Nickname: " << p.getNickname() 
             << ", Nombre: " << p.getNombre() 
             << ", Tel: " << p.getTelefono() 
             << ", Banco: " << p.getCuenta().getBanco() << endl;
    }

    cout << "\nInmobiliaria selecciona prop1..." << endl;
    sys->seleccionarPropietario("prop1");
    cout << "Prop1 seleccionado." << endl;

    cout << "\n=== FIN ===" << endl;
    
    delete sys;
    return 0;
}