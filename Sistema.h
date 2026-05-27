#ifndef SISTEMA_H
#define SISTEMA_H
#include <iostream>
#include "ISistema.h"

class Sistema : public ISistema {
  private:
    Sistema();
    static Sistema * instance;
  public:
    ~Sistema();
    static Sistema * getInstance();
};
#endif