#ifndef  STRING_H
#define	 STRING_H

#include "interfaces/ICollectible.h"
#include "interfaces/OrderedKey.h"

/**
 *  Implementación simple del datatype String que hereda tanto de ICollectible
 *  como de HashedKey
 */
#include <string.h>      // <<— tiene strlen(), strcpy(), strcmp() en ::
#include <stdexcept> 

class String: public ICollectible, public OrderedKey
{
private:
    char *s;
public:
    // construye el Datatype a partir de un puntero a caracter
    String(const char *s = "");
    virtual bool equals(IKey* other) const;
    // da el valor del string
    const char *getValue() const;
    virtual OrderedKey* clone() const;
    ComparisonRes compare(OrderedKey *k) const;
    
    virtual ~String();
    
};

#endif	/*_STRING_H */

