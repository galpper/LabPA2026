#include <stddef.h>
#include <stdexcept>
#include "Integer.h"

Integer::Integer(int i):
        val(i)
{
}

int Integer::getValue() const
{
    return val;
}
OrderedKey* Integer::clone() const {
    return new Integer(this->getValue());
}
ComparisonRes Integer::compare(OrderedKey* k) const
{
    Integer *i = dynamic_cast<Integer *>(k);
    if(i == NULL) // no se puede comparar si no es entero
        throw std::invalid_argument("Invalid key k");
    if(i->val == val)
        return EQUAL;
    else if(i->val > val)
        return GREATER;
    else
        return LESSER;
}
