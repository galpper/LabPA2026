#include <iostream>
#include <set>
#include <string>

#include "Factory.h"
#include "ISistema.h"
#include "DataType/h/dtpublicacion.h"
#include "DataType/h/dtinmobiliaria.h"
#include "DataType/h/dtinmueblepropietario.h"
#include "Clases/h/TipoPublicacion.h"
#include "Clases/h/TipoInmueble.h"
#include <unistd.h>
#include <cstdlib>
#include <limits>

using namespace std;

// Leer un número entero de manera segura.
int leerEntero() {
    int valor;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Ingrese un número entero: ";
    }
    return valor;
}

// Leer un número decimal de manera segura.
float leerFloat() {
    float valor;
    while (!(cin >> valor)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Entrada inválida. Ingrese un número decimal: ";
    }
    return valor;
}

// Alta de usuario.
void menuAltaUsuario(ISistema* isistema, int &codigoInmueble) {
    cout << "\n=== ALTA DE USUARIO ===" << endl;
    string nickname, pass, nombre, email;
    cin.ignore();
    cout << "Ingrese nickname: ";
    getline(cin, nickname);

    do {
        cout << "Ingrese contraseña (mínimo 6 caracteres): ";
        getline(cin, pass);
        if (pass.length() < 6) {
            cout << "Contraseña muy corta. Poné una de al menos 6." << endl;
        }
    } while (pass.length() < 6);
    
    cout << "Ingrese nombre: ";
    getline(cin, nombre);
    cout << "Ingrese email: ";
    getline(cin, email);
    
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
    
    if (isistema->existeUsuario(nickname, pass, nombre, email, tipo)) {
        system("clear");
        cout << "Error: Ya existe un usuario con el nickname ingresado." << endl;
        sleep(3);
        system("clear");
        return;
    }
    
    if (tipo == TipoUsuario::CLIENTE) {
        string apellido;
        int documento;
        cin.ignore();
        cout << "Ingrese apellido: ";
        getline(cin, apellido);
        cout << "Ingrese documento: ";
        documento = leerEntero();
        
        isistema->altaCliente(apellido, documento);
        system("clear");
        cout << "Cliente dado de alta con éxito." << endl;
        sleep(3);
        system("clear");
        
    } else if (tipo == TipoUsuario::PROPIETARIO) {
        int telefono;
        int numCuenta;
        string banco;
        cout << "Ingrese teléfono de contacto: ";
        telefono = leerEntero();
        cout << "Ingrese número de cuenta bancaria: ";
        numCuenta = leerEntero();
        cin.ignore();
        cout << "Ingrese banco: ";
        getline(cin, banco);
        
        dtcuentabancaria cuenta(numCuenta, banco);
        isistema->altaPropietario(telefono, cuenta);
        cout << "Propietario dado de alta con éxito." << endl;
        
        string agregarInm;
        cout << "Desea ingresar un inmueble para el propietario (s/n): ";
        cin >> agregarInm;
        while (agregarInm == "s" || agregarInm == "S") {
            string calle, depto;
            int numPuerta, anio;
            float superficie;
            cin.ignore();
            cout << "Ingrese calle: ";
            getline(cin, calle);
            cout << "Ingrese número de puerta: ";
            numPuerta = leerEntero();
            cin.ignore();
            cout << "Ingrese departamento: ";
            getline(cin, depto);
            cout << "Ingrese superficie (m2): ";
            superficie = leerFloat();
            cout << "Ingrese año de construcción: ";
            anio = leerEntero();
            
            cout << "Tipo de inmueble (1- Casa, 2- Apartamento): ";
            int tipoInmInt;
            tipoInmInt = leerEntero();
            
            if (tipoInmInt == 1) {
                string phStr;
                bool ph = false;
                cout << "Es propiedad horizontal (s/n): ";
                cin >> phStr;
                if (phStr == "s" || phStr == "S") ph = true;
                
                cout << "Tipo de techo (1- Liviano, 2- Dos aguas, 3- Plano): ";
                int techoInt;
                techoInt = leerEntero();
                TipoTecho techo = TipoTecho::PLANO;
                if (techoInt == 1) techo = TipoTecho::LIVIANO;
                else if (techoInt == 2) techo = TipoTecho::DOS_AGUAS;
                
                isistema->existeInmueble(numPuerta, calle, depto, superficie, anio, codigoInmueble, TipoInmueble::CASA);
                isistema->altaCasa(ph, techo);
                cout << "Casa registrada con código: " << codigoInmueble << endl;
                codigoInmueble++;
                
            } else if (tipoInmInt == 2) {
                int piso;
                string ascStr;
                bool asc = false;
                float gastos;
                cout << "Ingrese número de piso: ";
                piso = leerEntero();
                cout << "Tiene ascensor (s/n): ";
                cin >> ascStr;
                if (ascStr == "s" || ascStr == "S") asc = true;
                cout << "Ingrese gastos comunes: ";
                gastos = leerFloat();
                
                isistema->existeInmueble(numPuerta, calle, depto, superficie, anio, codigoInmueble, TipoInmueble::APARTAMENTO);
                isistema->altaApartamento(piso, asc, gastos);
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
        tel = leerEntero();
        cin.ignore();
        cout << "Ingrese URL del sitio web: ";
        getline(cin, url);
        cout << "Dirección - Ingrese calle: ";
        getline(cin, calle);
        cout << "Dirección - Ingrese número de puerta: ";
        numPuerta = leerEntero();
        cin.ignore();
        cout << "Dirección - Ingrese departamento: ";
        getline(cin, depto);
        
        dtdireccion dir(numPuerta, calle, depto);
        isistema->altaInmobiliaria(dir, tel, url);
        cout << "Inmobiliaria dada de alta con éxito." << endl;
        
        string agregarRep;
        cout << "Desea registrar un propietario representado por la inmobiliaria (s/n): ";
        cin >> agregarRep;
        while (agregarRep == "s" || agregarRep == "S") {
            set<dtpropietario> conjuntoPropietarios = isistema->listarPropietarios();
            if (conjuntoPropietarios.empty()) {
                cout << "No hay propietarios registrados en el sistema." << endl;
                break;
            }
            cout << "\nPropietarios registrados:" << endl;
            for (dtpropietario propietarioActual : conjuntoPropietarios) {
                cout << "- Nickname: " << propietarioActual.getNickname() << ", Nombre: " << propietarioActual.getNombre() << endl;
            }
            
            string nickRep;
            cin.ignore();
            cout << "Ingrese nickname del propietario a representar: ";
            getline(cin, nickRep);
            isistema->seleccionarPropietario(nickRep);
            cout << "Relación de representación generada con éxito." << endl;
            
            cout << "Desea agregar otro propietario representado (s/n): ";
            cin >> agregarRep;
        }
    }
}

// Consulta de publicaciones.
void menuConsultaPublicaciones(ISistema* isistema) {
    cout << "\n=== CONSULTA DE PUBLICACIONES ===" << endl;
    cout << "Tipo de publicación (1- VENTA, 2- ALQUILER): ";
    int tipoSeleccionado;
    tipoSeleccionado = leerEntero();
    TipoPublicacion tipoDePublicacion = TipoPublicacion::VENTA;
    if (tipoSeleccionado == 2) tipoDePublicacion = TipoPublicacion::ALQUILER;
    
    float precioMinimo, precioMaximo;
    cout << "Ingrese precio mínimo: ";
    precioMinimo = leerFloat();
    cout << "Ingrese precio máximo: ";
    precioMaximo = leerFloat();
    
    cout << "Tipo de inmueble (1- Casa, 2- Apartamento, 3- Ambos): ";
    int tipoInmuebleSeleccionado;
    tipoInmuebleSeleccionado = leerEntero();
    TipoInmueble tipoDeInmueble = TipoInmueble::AMBOS;
    if (tipoInmuebleSeleccionado == 1) tipoDeInmueble = TipoInmueble::CASA;
    else if (tipoInmuebleSeleccionado == 2) tipoDeInmueble = TipoInmueble::APARTAMENTO;
    
    set<dtpublicacion> publicacionesEncontradas = isistema->listarPublicaciones(tipoDePublicacion, precioMinimo, precioMaximo, tipoDeInmueble);
    if (publicacionesEncontradas.empty()) {
        cout << "No hay publicaciones con los filtros especificados." << endl;
    } else {
        cout << "\nPublicaciones encontradas:" << endl;
        for (dtpublicacion publicacionActual : publicacionesEncontradas) {
            cout << "- Código: " << publicacionActual.getCodigo()
                 << " | Fecha: " << publicacionActual.getFecha()
                 << " | Inmobiliaria: " << publicacionActual.getNombreInmobiliaria()
                 << " | Precio: " << publicacionActual.getPrecio()
                 << "\n  Texto: " << publicacionActual.getTexto() << endl;
        }
        
        string deseaVerDetalle;
        cout << "\n¿Desea ver el detalle de algún inmueble? (s/n): ";
        cin >> deseaVerDetalle;
        if (deseaVerDetalle == "s" || deseaVerDetalle == "S") {
            int codigoDePublicacion;
            cout << "Ingrese el código de la publicación: ";
            codigoDePublicacion = leerEntero();
            
            dtinmueble inmuebleEncontrado = isistema->seleccionarPublicacion(codigoDePublicacion);
            if (inmuebleEncontrado.getCodigo() == 0) {
                cout << "No se encontró el inmueble o código inválido." << endl;
            } else {
                cout << "\n=== DETALLE DEL INMUEBLE ===" << endl;
                cout << "Código: " << inmuebleEncontrado.getCodigo() << endl;
                cout << "Fecha de inicio: " << inmuebleEncontrado.getFechaInicio() << endl;
                cout << "Superficie: " << inmuebleEncontrado.getSuperficie() << " m2" << endl;
                cout << "Año de construcción: " << inmuebleEncontrado.getAnioConstruccion() << endl;
                cout << "Dirección: " << inmuebleEncontrado.getDireccion().getCalle() << " " << inmuebleEncontrado.getDireccion().getNumeroPuerta() << ", " << inmuebleEncontrado.getDireccion().getDepartamento() << endl;
                cout << "Tipo de inmueble: " << (inmuebleEncontrado.getTipoInmueble() == TipoInmueble::CASA ? "Casa" : "Apartamento") << endl;
            }
        }
    }
    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
    system("clear");
}

// Alta de administracion de propiedad.
void menuAltaAdministracionPropiedad(ISistema* isistema) {
    cout << "\n=== ALTA DE ADMINISTRACIÓN DE PROPIEDAD ===" << endl;
    set<dtinmobiliaria> inmobiliariasRegistradas = isistema->listarInmobiliarias();
    if (inmobiliariasRegistradas.empty()) {
        cout << "No hay inmobiliarias registradas." << endl;
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
        system("clear");
        return;
    }

    cout << "\nInmobiliarias registradas:" << endl;
    for (dtinmobiliaria inmobiliariaActual : inmobiliariasRegistradas) {
        cout << "- Nickname: " << inmobiliariaActual.getNickname() << " | Nombre: " << inmobiliariaActual.getNombre() << endl;
    }

    string nicknameInmobiliariaSeleccionada;
    cout << "\nSeleccione el nickname de la inmobiliaria: ";
    cin >> nicknameInmobiliariaSeleccionada;

    set<dtinmueblepropietario> inmueblesDePropietarios = isistema->seleccionarInmobiliaria(nicknameInmobiliariaSeleccionada);
    if (inmueblesDePropietarios.empty()) {
        cout << "La inmobiliaria no representa propietarios con inmuebles." << endl;
        cout << "\nPresione Enter para continuar...";
        cin.ignore();
        cin.get();
        system("clear");
        return;
    }

    cout << "\nInmuebles de propietarios representados:" << endl;
    for (dtinmueblepropietario inmuebleActual : inmueblesDePropietarios) {
        cout << "- Código: " << inmuebleActual.getCodigo() 
             << " | Dirección: " << inmuebleActual.getDireccion().getCalle() << " " << inmuebleActual.getDireccion().getNumeroPuerta() << ", " << inmuebleActual.getDireccion().getDepartamento()
             << " | Propietario: " << inmuebleActual.getNombrePropietario() << endl;
    }

    int codigoInmuebleSeleccionado;
    cout << "\nIngrese el código del inmueble a comenzar a administrar: ";
    codigoInmuebleSeleccionado = leerEntero();

    isistema->altaAdministracionPropiedad(codigoInmuebleSeleccionado);
    cout << "Administración registrada con éxito." << endl;

    cout << "\nPresione Enter para continuar...";
    cin.ignore();
    cin.get();
    system("clear");
}

// Ejecutar pruebas.
void ejecutarPruebas(ISistema* isistema) {
    cout << "\n=== EJECUTANDO PRUEBAS PREDETERMINADAS ===" << endl;
    
    // 1. Alta de Usuarios
    cout << "\n--- 1. Alta de Usuarios ---" << endl;
    
    // Propietario 1
    if (!isistema->existeUsuario("prop1", "pass1", "Pedro", "pedro@gmail.com", TipoUsuario::PROPIETARIO)) {
        dtcuentabancaria cuenta1(11111, "BROU");
        isistema->altaPropietario(99111222, cuenta1);
        cout << "Propietario 'prop1' dado de alta." << endl;
    } else {
        cout << "Propietario 'prop1' ya existe." << endl;
    }

    // Propietario 2
    if (!isistema->existeUsuario("prop2", "pass2", "Maria", "maria@gmail.com", TipoUsuario::PROPIETARIO)) {
        dtcuentabancaria cuenta2(22222, "Santander");
        isistema->altaPropietario(99333444, cuenta2);
        cout << "Propietario 'prop2' dado de alta." << endl;
    } else {
        cout << "Propietario 'prop2' ya existe." << endl;
    }

    // Cliente 1
    if (!isistema->existeUsuario("cli1", "pass3", "Juan", "juan@gmail.com", TipoUsuario::CLIENTE)) {
        isistema->altaCliente("Perez", 12345678);
        cout << "Cliente 'cli1' dado de alta." << endl;
    } else {
        cout << "Cliente 'cli1' ya existe." << endl;
    }

    // Inmobiliaria 1
    if (!isistema->existeUsuario("inmo1", "pass4", "Inmobiliaria Montevideo", "contacto@inmomvd.com", TipoUsuario::INMOBILIARIA)) {
        dtdireccion dirInmo(1234, "18 de Julio", "Montevideo");
        isistema->altaInmobiliaria(dirInmo, 24001122, "www.inmomvd.com");
        cout << "Inmobiliaria 'inmo1' dada de alta." << endl;
    } else {
        cout << "Inmobiliaria 'inmo1' ya existe." << endl;
    }

    // 2. Registrar Inmuebles para prop1
    cout << "\n--- 2. Registrar Inmuebles para prop1 ---" << endl;
    
    // Seteamos prop1 como activo
    isistema->existeUsuario("prop1", "pass1", "Pedro", "pedro@gmail.com", TipoUsuario::PROPIETARIO);

    // Registrar Casa
    if (!isistema->existeInmueble(100, "Av. Italia", "Montevideo", 150.5, 2015, 101, TipoInmueble::CASA)) {
        isistema->altaCasa(true, TipoTecho::PLANO);
        cout << "Casa con codigo 101 registrada para prop1." << endl;
    } else {
        cout << "Inmueble 101 ya existe." << endl;
    }

    // Registrar Apartamento
    if (!isistema->existeInmueble(502, "Buxareo", "Montevideo", 75.0, 2020, 102, TipoInmueble::APARTAMENTO)) {
        isistema->altaApartamento(5, true, 8500.0);
        cout << "Apartamento con codigo 102 registrado para prop1." << endl;
    } else {
        cout << "Inmueble 102 ya existe." << endl;
    }

    // 3. Listar Propietarios y Seleccionar por Inmobiliaria
    cout << "\n--- 3. Listar Propietarios por Inmobiliaria ---" << endl;
    
    // Seteamos inmo1 como activa
    isistema->existeUsuario("inmo1", "pass4", "Inmobiliaria Montevideo", "contacto@inmomvd.com", TipoUsuario::INMOBILIARIA);

    set<dtpropietario> props = isistema->listarPropietarios();
    cout << "Lista de propietarios disponibles:" << endl;
    for (dtpropietario p : props) {
        cout << "- Nickname: " << p.getNickname() 
             << ", Nombre: " << p.getNombre() 
             << ", Tel: " << p.getTelefono() 
             << ", Banco: " << p.getCuenta().getBanco() << endl;
    }

    cout << "\nInmobiliaria selecciona prop1..." << endl;
    isistema->seleccionarPropietario("prop1");
    cout << "Prop1 seleccionado." << endl;

    // ---------------------------------------------------------------------------------------------------------

    // 4. Alta de Publicación
    cout << "\n--- 4. Alta de Publicacion ---" << endl;

    // La inmobiliaria debe administrar el inmueble previamente
    // (adaptar según cómo implementaron la administración)

    set<dtinmueble> inmuebles = isistema->seleccionarInmueble("inmo1");

    cout << "Inmuebles administrados por inmo1:" << endl;
    for(auto dt : inmuebles){
        cout << "Codigo: " << dt.getCodigo() << endl;
    }

    bool ok = isistema->altaPublicacion(
        101,
        TipoPublicacion::VENTA,
        "Hermosa casa en excelente estado",
        250000
    );

    if(ok){
        cout << "Publicacion creada correctamente." << endl;
    }else{
        cout << "No fue posible crear la publicacion." << endl;
    }
        cout << "\n=== PRUEBAS FINALIZADAS ===" << endl;
}

    void menuAltaPublicacion(ISistema* sys){

        set<dtinmobiliaria> inmobiliarias =
            sys->listarInmobiliarias();

        if(inmobiliarias.empty()){
            cout << "No existen inmobiliarias registradas." << endl;
            return;
        }

        cout << "\n=== INMOBILIARIAS ===" << endl;

        for(auto dt : inmobiliarias){
            cout << dt.getNickname() << " - " << dt.getNombre() << endl;
        }

        string nickname;

        cout << "\nIngrese nickname de la inmobiliaria: ";
        cin >> nickname;

        set<dtinmueble> inmuebles =
            sys->seleccionarInmueble(nickname);

        if(inmuebles.empty()){
            cout << "La inmobiliaria no administra inmuebles." << endl;
            return;
        }

        cout << "\n=== INMUEBLES ===" << endl;

        for(auto dt : inmuebles){
            cout << "Codigo: " << dt.getCodigo() << endl;
        }

        int codigo;
        int tipoInt;
        string texto;
        float precio;

        cout << "\nCodigo inmueble: ";
        cin >> codigo;

        cout << "Tipo (1-Venta, 2-Alquiler): ";
        cin >> tipoInt;

        TipoPublicacion tipo;

        if(tipoInt == 1)
            tipo = TipoPublicacion::VENTA;
        else
            tipo = TipoPublicacion::ALQUILER;

        cin.ignore();

        cout << "Texto: ";
        getline(cin, texto);

        cout << "Precio: ";
        cin >> precio;

        bool ok =
            sys->altaPublicacion(
                codigo,
                tipo,
                texto,
                precio
            );

        if(ok)
            cout << "Publicacion creada correctamente." << endl;
        else
            cout << "Ya existe una publicacion para ese tipo y fecha." << endl;
    }

#include "DataType/h/dtcliente.h"
#include "DataType/h/dtadministra.h"

// Listar datos.
void menuListarDatos(ISistema* isistema) {
    int opcionListar;
    do {
        cout << "\n========== LISTAR DATOS ==========" << endl;
        cout << "1- Listar propietarios" << endl;
        cout << "2- Listar clientes" << endl;
        cout << "3- Listar inmobiliarias" << endl;
        cout << "4- Listar administra" << endl;
        cout << "5- Listar publicaciones" << endl;
        cout << "6- Listar inmuebles" << endl;
        cout << "0- Volver" << endl;
        cout << "==================================" << endl;
        cout << "Seleccione una opción: ";
        opcionListar = leerEntero();

        switch (opcionListar) {
            case 1: {
                set<dtpropietario> conjuntoPropietarios = isistema->listarPropietarios();
                if (conjuntoPropietarios.empty()) {
                    cout << "No hay propietarios registrados." << endl;
                } else {
                    cout << "\n--- LISTADO DE PROPIETARIOS ---" << endl;
                    for (dtpropietario propietarioActual : conjuntoPropietarios) {
                        cout << "Nickname: " << propietarioActual.getNickname() 
                             << " | Nombre: " << propietarioActual.getNombre() 
                             << " | Email: " << propietarioActual.getEmail() 
                             << " | Teléfono: " << propietarioActual.getTelefono() 
                             << " | Cuenta: " << propietarioActual.getCuenta().getBanco() << " Nro: " << propietarioActual.getCuenta().getNumero() << endl;
                    }
                }
                break;
            }
            case 2: {
                set<dtcliente> conjuntoClientes = isistema->listarClientes();
                if (conjuntoClientes.empty()) {
                    cout << "No hay clientes registrados." << endl;
                } else {
                    cout << "\n--- LISTADO DE CLIENTES ---" << endl;
                    for (dtcliente clienteActual : conjuntoClientes) {
                        cout << "Nickname: " << clienteActual.getNickname() 
                             << " | Nombre: " << clienteActual.getNombre() 
                             << " | Email: " << clienteActual.getEmail() 
                             << " | Apellido: " << clienteActual.getApellido() 
                             << " | Documento: " << clienteActual.getDocumento() << endl;
                    }
                }
                break;
            }
            case 3: {
                set<dtinmobiliaria> conjuntoInmobiliarias = isistema->listarInmobiliarias();
                if (conjuntoInmobiliarias.empty()) {
                    cout << "No hay inmobiliarias registradas." << endl;
                } else {
                    cout << "\n--- LISTADO DE INMOBILIARIAS ---" << endl;
                    for (dtinmobiliaria inmobiliariaActual : conjuntoInmobiliarias) {
                        cout << "Nickname: " << inmobiliariaActual.getNickname() 
                             << " | Nombre: " << inmobiliariaActual.getNombre() 
                             << " | Email: " << inmobiliariaActual.getEmail() 
                             << " | Teléfono: " << inmobiliariaActual.getTelefono() 
                             << " | URL: " << inmobiliariaActual.getUrl() 
                             << " | Dirección: " << inmobiliariaActual.getDireccion().getCalle() << " " << inmobiliariaActual.getDireccion().getNumeroPuerta() << ", " << inmobiliariaActual.getDireccion().getDepartamento() << endl;
                    }
                }
                break;
            }
            case 4: {
                set<dtadministra> conjuntoAdministraciones = isistema->listarAdministraciones();
                if (conjuntoAdministraciones.empty()) {
                    cout << "No hay administraciones registradas." << endl;
                } else {
                    cout << "\n--- LISTADO DE ADMINISTRACIONES ---" << endl;
                    for (dtadministra administracionActual : conjuntoAdministraciones) {
                        cout << "Inmobiliaria: " << administracionActual.getNicknameInmobiliaria() 
                             << " | Código Inmueble: " << administracionActual.getCodigoInmueble() 
                             << " | Fecha Inicio: " << administracionActual.getFechaInicio() << endl;
                    }
                }
                break;
            }
            case 5: {
                set<dtpublicacion> conjuntoPublicaciones = isistema->listarTodasPublicaciones();
                if (conjuntoPublicaciones.empty()) {
                    cout << "No hay publicaciones registradas." << endl;
                } else {
                    cout << "\n--- LISTADO DE PUBLICACIONES ---" << endl;
                    for (dtpublicacion publicacionActual : conjuntoPublicaciones) {
                        cout << "Código: " << publicacionActual.getCodigo() 
                             << " | Fecha: " << publicacionActual.getFecha() 
                             << " | Precio: " << publicacionActual.getPrecio() 
                             << " | Inmobiliaria: " << publicacionActual.getNombreInmobiliaria() 
                             << " | Texto: " << publicacionActual.getTexto() << endl;
                    }
                }
                break;
            }
            case 6: {
                set<dtinmueble> conjuntoInmuebles = isistema->listarTodosInmuebles();
                if (conjuntoInmuebles.empty()) {
                    cout << "No hay inmuebles registrados." << endl;
                } else {
                    cout << "\n--- LISTADO DE INMUEBLES ---" << endl;
                    for (dtinmueble inmuebleActual : conjuntoInmuebles) {
                        cout << "Código: " << inmuebleActual.getCodigo() 
                             << " | Superficie: " << inmuebleActual.getSuperficie() << " m2"
                             << " | Año: " << inmuebleActual.getAnioConstruccion() 
                             << " | Tipo: " << (inmuebleActual.getTipoInmueble() == TipoInmueble::CASA ? "Casa" : "Apartamento") 
                             << " | Dirección: " << inmuebleActual.getDireccion().getCalle() << " " << inmuebleActual.getDireccion().getNumeroPuerta() << ", " << inmuebleActual.getDireccion().getDepartamento() << endl;
                    }
                }
                break;
            }
            case 0:
                break;
            default:
                cout << "Opción no válida." << endl;
                break;
        }
        if (opcionListar != 0) {
            cout << "\nPresione Enter para continuar...";
            cin.ignore();
            cin.get();
            system("clear");
        }
    } while (opcionListar != 0);
}

// Menu principal.
int main() {
    ISistema* isistema = Factory::getSistema();
    int codigoInmueble = 200; 
    int opcion;
    
    do {
        cout << "\n========== MENÚ PRINCIPAL ==========" << endl;
        cout << "1- Alta usuario" << endl;
        cout << "2- Alta publicacion" << endl;
        cout << "3- Consulta publicaciones" << endl;
        cout << "4- Eliminar inmueble" << endl;
        cout << "5- Alta administracion de propiedad" << endl;
        cout << "6- Cargar datos" << endl;
        cout << "7- Listar datos" << endl;
        cout << "0- Salir" << endl;
        cout << "====================================" << endl;
        cout << "Seleccione una opción: ";
        opcion = leerEntero();
        
        switch (opcion) {
            case 1:
                menuAltaUsuario(isistema, codigoInmueble);
                break;
            case 2:
                menuAltaPublicacion(isistema);
                break;
            case 3:
                menuConsultaPublicaciones(isistema);
                break;
            case 4:
                cout << "Opción 'Eliminar inmueble' no implementada aún." << endl;
                break;
            case 5:
                menuAltaAdministracionPropiedad(isistema);
                break;
            case 6:
                isistema->cargarDatos();
                cout << "Datos cargados con éxito." << endl;
                cout << "\nPresione Enter para continuar...";
                cin.ignore();
                cin.get();
                system("clear");
                break;
            case 7:
                menuListarDatos(isistema);
                break;
            case 0:
                cout << "Saliendo del sistema..." << endl;
                break;
            default:
                cout << "Opción no válida. Intente nuevamente." << endl;
                break;
        }
    } while (opcion != 0);
    
    delete isistema;
    return 0;
}