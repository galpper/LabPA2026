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

    // Guardar datos temporales del usuario.
    string temp_nickname;
    string temp_pass;
    string temp_nombre;
    string temp_email;
    TipoUsuario temp_tipoUsuario;

    // Guardar datos temporales del inmueble.
    int temp_numPuerta;
    string temp_calle;
    string temp_departamento;
    float temp_superficie;
    int temp_anioConstruccion;
    int temp_codigo;
    TipoInmueble temp_tipoInmueble;

    // Guardar usuarios activos en sesion.
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