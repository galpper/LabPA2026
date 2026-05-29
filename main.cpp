#include <iostream>
#include <set>
#include <string>

#include "Factory.h"
#include "ISistema.h"
#include <chrono>
#include <thread>
#include <cstdlib>

using namespace std;

// aca meti todo el codigo para meter un usuario nuevo.
// lo separe aca para no entreverar el programa principal
// y que sea mas facil de leer cuando lo revise despues.
void menuAltaUsuario(ISistema* sys, int &codigoInmueble) {
    cout << "\n=== ALTA DE USUARIO ===" << endl;
    string nickname, pass, nombre, email;
    cout << "Ingrese nickname: ";
    cin >> nickname;
    
    // me fije que la clave tenga por lo menos seis letras
    // para cumplir con lo que pide la letra del obligatorio.
    do {
        cout << "Ingrese contraseña (mínimo 6 caracteres): ";
        cin >> pass;
        if (pass.length() < 6) {
            cout << "Contraseña muy corta. Poné una de al menos 6." << endl;
        }
    } while (pass.length() < 6);
    
    cout << "Ingrese nombre: ";
    cin.ignore();
    getline(cin, nombre);
    cout << "Ingrese email: ";
    cin >> email;
    
    cout << "Seleccione tipo de usuario (1- Cliente, 2- Propietario, 3- Inmobiliaria): ";
    int tipoInt;
    cin >> tipoInt;
    TipoUsuario tipo;
    if (tipoInt == 1) tipo = TipoUsuario::CLIENTE;
    else if (tipoInt == 2) tipo = TipoUsuario::PROPIETARIO;
    else if (tipoInt == 3) tipo = TipoUsuario::INMOBILIARIA;
    else {
        cout << "Opción inválida." << endl;
        return;
    }
    
    // me fije si el nombre de usuario ya existia antes.
    // si ya estaba registrado, corto aca para no pisar a nadie.
    if (sys->existeUsuario(nickname, pass, nombre, email, tipo)) {
        // limpie la pantalla y mande a dormir el programa tres segundos
        // asi te da el tiempo justo de leer el aviso antes de borrar.
        system("clear");
        cout << "Error: Ya existe un usuario con el nickname ingresado." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        system("clear");
        return;
    }
    
    if (tipo == TipoUsuario::CLIENTE) {
        string apellido;
        int documento;
        cout << "Ingrese apellido: ";
        cin.ignore();
        getline(cin, apellido);
        cout << "Ingrese documento: ";
        cin >> documento;
        
        sys->altaCliente(apellido, documento);
        // limpie la pantalla y mande a dormir el programa tres segundos
        // asi te da el tiempo justo de leer el aviso antes de borrar.
        system("clear");
        cout << "Cliente dado de alta con éxito." << endl;
        this_thread::sleep_for(chrono::seconds(3));
        system("clear");
        
    } else if (tipo == TipoUsuario::PROPIETARIO) {
        int telefono;
        int numCuenta;
        string banco;
        cout << "Ingrese teléfono de contacto: ";
        cin >> telefono;
        cout << "Ingrese número de cuenta bancaria: ";
        cin >> numCuenta;
        cout << "Ingrese banco: ";
        cin.ignore();
        getline(cin, banco);
        
        dtcuentabancaria cuenta(numCuenta, banco);
        sys->altaPropietario(telefono, cuenta);
        cout << "Propietario dado de alta con éxito." << endl;
        
        // si el usuario es dueño, deje la opcion de cargar
        // sus casas de una para no tener que dar vueltas despues.
        string agregarInm;
        cout << "Desea ingresar un inmueble para el propietario (s/n): ";
        cin >> agregarInm;
        while (agregarInm == "s" || agregarInm == "S") {
            string calle, depto;
            int numPuerta, anio;
            float superficie;
            cout << "Ingrese calle: ";
            cin.ignore();
            getline(cin, calle);
            cout << "Ingrese número de puerta: ";
            cin >> numPuerta;
            cout << "Ingrese departamento: ";
            cin.ignore();
            getline(cin, depto);
            cout << "Ingrese superficie (m2): ";
            cin >> superficie;
            cout << "Ingrese año de construcción: ";
            cin >> anio;
            
            cout << "Tipo de inmueble (1- Casa, 2- Apartamento): ";
            int tipoInmInt;
            cin >> tipoInmInt;
            
            if (tipoInmInt == 1) {
                string phStr;
                bool ph = false;
                cout << "Es propiedad horizontal (s/n): ";
                cin >> phStr;
                if (phStr == "s" || phStr == "S") ph = true;
                
                cout << "Tipo de techo (1- Liviano, 2- Dos aguas, 3- Plano): ";
                int techoInt;
                cin >> techoInt;
                TipoTecho techo = TipoTecho::PLANO;
                if (techoInt == 1) techo = TipoTecho::LIVIANO;
                else if (techoInt == 2) techo = TipoTecho::DOS_AGUAS;
                
                sys->existeInmueble(numPuerta, calle, depto, superficie, anio, codigoInmueble, TipoInmueble::CASA);
                sys->altaCasa(ph, techo);
                cout << "Casa registrada con código incremental: " << codigoInmueble << endl;
                codigoInmueble++;
                
            } else if (tipoInmInt == 2) {
                int piso;
                string ascStr;
                bool asc = false;
                float gastos;
                cout << "Ingrese número de piso: ";
                cin >> piso;
                cout << "Tiene ascensor (s/n): ";
                cin >> ascStr;
                if (ascStr == "s" || ascStr == "S") asc = true;
                cout << "Ingrese gastos comunes: ";
                cin >> gastos;
                
                sys->existeInmueble(numPuerta, calle, depto, superficie, anio, codigoInmueble, TipoInmueble::APARTAMENTO);
                sys->altaApartamento(piso, asc, gastos);
                cout << "Apartamento registrado con código incremental: " << codigoInmueble << endl;
                codigoInmueble++;
            } else {
                cout << "Opción de inmueble inválida." << endl;
            }
            
            cout << "Desea ingresar otro inmueble para el propietario (s/n): ";
            cin >> agregarInm;
        }
        
    } else if (tipo == TipoUsuario::INMOBILIARIA) {
        int tel;
        string url, calle, depto;
        int numPuerta;
        cout << "Ingrese teléfono: ";
        cin >> tel;
        cout << "Ingrese URL del sitio web: ";
        cin >> url;
        cout << "Dirección - Ingrese calle: ";
        cin.ignore();
        getline(cin, calle);
        cout << "Dirección - Ingrese número de puerta: ";
        cin >> numPuerta;
        cout << "Dirección - Ingrese departamento: ";
        cin.ignore();
        getline(cin, depto);
        
        dtdireccion dir(numPuerta, calle, depto);
        sys->altaInmobiliaria(dir, tel, url);
        cout << "Inmobiliaria dada de alta con éxito." << endl;
        
        // aca deje que elijas que dueños va a representar
        // la inmobiliaria que acabas de guardar en el programa.
        string agregarRep;
        cout << "Desea registrar un propietario representado por la inmobiliaria (s/n): ";
        cin >> agregarRep;
        while (agregarRep == "s" || agregarRep == "S") {
            set<dtpropietario> props = sys->listarPropietarios();
            if (props.empty()) {
                cout << "No hay propietarios registrados en el sistema." << endl;
                break;
            }
            cout << "\nPropietarios registrados:" << endl;
            for (dtpropietario p : props) {
                cout << "- Nickname: " << p.getNickname() << ", Nombre: " << p.getNombre() << endl;
            }
            
            string nickRep;
            cout << "Ingrese nickname del propietario a representar: ";
            cin >> nickRep;
            sys->seleccionarPropietario(nickRep);
            cout << "Relación de representación generada con éxito." << endl;
            
            cout << "Desea agregar otro propietario representado (s/n): ";
            cin >> agregarRep;
        }
    }
}

// aca guarde los datos de prueba que ya tenias armados.
// los deje quietos aca para poder usarlos cuando precises.
void ejecutarPruebas(ISistema* sys) {
    cout << "\n=== EJECUTANDO PRUEBAS PREDETERMINADAS ===" << endl;
    
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

    cout << "\n=== PRUEBAS FINALIZADAS ===" << endl;
}

// aca arme la lista de opciones para la pantalla.
// use opciones numericas para que decidas que queres hacer.
int main() {
    ISistema* sys = Factory::getSistema();
    int codigoInmueble = 200; 
    int opcion;
    
    do {
        cout << "\n========== MENÚ PRINCIPAL ==========" << endl;
        cout << "1- Alta usuario" << endl;
        cout << "2- Alta publicacion" << endl;
        cout << "3- Consulta publicaciones" << endl;
        cout << "4- Eliminar inmueble" << endl;
        cout << "5- Cargar datos" << endl;
        cout << "6- Ejecutar pruebas" << endl;
        cout << "0- Salir" << endl;
        cout << "====================================" << endl;
        cout << "Seleccione una opción: ";
        cin >> opcion;
        
        switch (opcion) {
            case 1:
                menuAltaUsuario(sys, codigoInmueble);
                break;
            case 2:
                cout << "Opción 'Alta publicacion' no implementada aún." << endl;
                break;
            case 3:
                cout << "Opción 'Consulta publicaciones' no implementada aún." << endl;
                break;
            case 4:
                cout << "Opción 'Eliminar inmueble' no implementada aún." << endl;
                break;
            case 5:
                cout << "Opción 'Cargar datos' no implementada aún." << endl;
                break;
            case 6:
                ejecutarPruebas(sys);
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 0);
    
    delete sys;
    return 0;
}