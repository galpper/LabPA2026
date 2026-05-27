#include <stddef.h>
#include <string.h>    // <<— incluye strlen, strcpy, strcmp, etc. en ::
#include <stdexcept>   // <<— para std::invalid_argument
#include "String.h"
#include <cstring>

String::String(const char* str) {
    if (str == nullptr)
        throw std::invalid_argument("str es NULL");
        
    int strSize = strlen(str);               // función C definida en <string.h>
    s = strcpy(new char[strSize + 1], str);   // función C definida en <string.h>
}
bool String::equals(IKey* other) const {
    String* o = dynamic_cast<String*>(other);
    return o && strcmp(this->s, o->s) == 0;
}
OrderedKey* String::clone() const {
    return new String(this->s);
}
ComparisonRes String::compare(OrderedKey* k) const {
    String* str = dynamic_cast<String*>(k);
    if (str == nullptr) 
        throw std::invalid_argument("Invalid key k");
    
    int cmp = strcmp(s, str->s);  // strcmp de <string.h>
    if (cmp == 0)
        return EQUAL;
    else if (cmp > 0)
        return GREATER;
    else
        return LESSER;
}

const char* String::getValue() const {
    return s;
}

String::~String() {
    delete[] s;
}
