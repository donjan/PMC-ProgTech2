#ifndef AUTOCORR_PROPERTY_HEADER
#define AUTOCORR_PROPERTY_HEADER

#include "accum_property_generator.hpp"

#include <sstream>
#include <typeinfo>

//========+========+========+========+========+========+========+========+========+========+
//TYPE TRAIT
//========+========+========+========+========+========+========+========+========+========+
template <typename T>
struct autocorr_type
{
    typedef int type;
};

IMPLEMENT_FUNCTION(autocorr)

#endif //AUTOCORR_PROPERTY_HEADER
