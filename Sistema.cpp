#include "Sistema.h"
#include <iostream>
#include "ISistema.h"
#include <string>
#include <set>
#include <ctime>
#include <cstdlib>
#include <iomanip>
using namespace std;

Sistema * Sistema::instance = NULL;

Sistema::~Sistema() {
}

Sistema * Sistema::getInstance() {
    if (instance == NULL)
        instance = new Sistema();
    return instance;
}

Sistema::Sistema(){
//    micliente = new OrderedDictionary();
//    miMesa = new OrderedDictionary();
//    miProducto = new OrderedDictionary();
//    miProductoSimple = new OrderedDictionary();
//    miMenu = new OrderedDictionary();
//    miMenuCompleto = new OrderedDictionary();
//    miVenta = new OrderedDictionary();
//    miVentaProducto = new OrderedDictionary();
//    miVentaMenu = new OrderedDictionary();
//    miMozo = new OrderedDictionary();
//    miRepartidor = new OrderedDictionary();
//    miFactura = new OrderedDictionary();
//    productoVenta = new OrderedDictionary;

}
