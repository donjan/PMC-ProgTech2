#ifndef FIX_SIZE_BIN_PROPERTY_HEADER
#define FIX_SIZE_BIN_PROPERTY_HEADER

#include "accum_property_generator.hpp"

#include <sstream>
#include <typeinfo>

//========+========+========+========+========+========+========+========+========+========+
//TYPE TRAIT
//========+========+========+========+========+========+========+========+========+========+
template <typename T>
struct fix_size_bin_type
{
    typedef int type;
};

IMPLEMENT_FUNCTION(fix_size_bin)

#endif //FIX_SIZE_BIN_PROPERTY_HEADER
