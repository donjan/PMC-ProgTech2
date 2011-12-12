#ifndef ERROR_PROPERTY_HEADER
#define ERROR_PROPERTY_HEADER

#include "accum_property_generator.hpp"

#include <sstream>
#include <typeinfo>

//========+========+========+========+========+========+========+========+========+========+
//TYPE TRAIT
//========+========+========+========+========+========+========+========+========+========+
template <typename T>
struct error_type
{
    typedef T type;
};
template<>
struct error_type<int>
{
    typedef double type;
};

IMPLEMENT_FUNCTION(error)

#endif //ERROR_PROPERTY_HEADER
