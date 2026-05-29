#ifndef SISTEMA_H
#define SISTEMA_H

#include <iostream>
#include <set>
#include <string>
#include "ISistema.h"
#include "ICollection/interfaces/IDictionary.h"

class Sistema : public ISistema {
  private:
    Sistema();
    static Sistema * instance;

    IDictionary * usuarios;
    IDictionary * inmuebles;

    // aca nos guardamos de forma temporal los datos del nuevo usuario.
    // los precisamos en la clase porque el alta se ejecuta en dos pasos
    // y no podemos perder la informacion que ya validaste en el primero.
    string temp_nickname;
    string temp_pass;
    string temp_nombre;
    string temp_email;
    TipoUsuario temp_tipoUsuario;

    // aca dejamos guardados temporalmente los datos del inmueble.
    // nos sirve para cuando el usuario decida si es casa o apartamento,
    // asi podemos construir la instancia con la clase que corresponde.
    int temp_numPuerta;
    string temp_calle;
    string temp_departamento;
    float temp_superficie;
    int temp_anioConstruccion;
    int temp_codigo;
    TipoInmueble temp_tipoInmueble;

    // aca recordamos al propietario o la inmobiliaria que estan activos.
    // los guardamos asi los tenes a mano para asociarles nuevos inmuebles
    // directamente, sin tener que buscarlos en el diccionario cada vez.
    class propietario * propietarioActual;
    class inmobiliaria * inmobiliariaActual;

  public:
    ~Sistema();
    static Sistema * getInstance();

    bool existeUsuario(string nickname, string pass, string nombre, string email, TipoUsuario tipoUsuario) override;
    void altaCliente(string apellido, int documento) override;
    void altaPropietario(int telefono, dtcuentabancaria cuenta) override;
    void altaInmobiliaria(dtdireccion direccion, int telefono, string url) override;

    bool existeInmueble(int numPuerta, string calle, string departamento, float superficie, int anioConstruccion, int codigo, TipoInmueble tipoInmueble) override;
    void altaCasa(bool horizontal, TipoTecho tipoTecho) override;
    void altaApartamento(int numeroPiso, bool ascensor, float gastosComunes) override;

    set<dtpropietario> listarPropietarios() override;
    void seleccionarPropietario(string nickname) override;
};
#endif