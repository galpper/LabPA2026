#pragma once

#include <iostream>
#include <string>
#include "../../ICollection/interfaces/ICollectible.h"

using namespace std;

class agenda : public ICollectible {
private:
    string fecha;
    string texto;

public:
    agenda();

    agenda(string fecha, string texto);

    string getFecha();
    string getTexto();
    virtual ~agenda();
};