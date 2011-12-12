#ifndef MAX_NUM_BIN_PROPERTY_HEADER
#define MAX_NUM_BIN_PROPERTY_HEADER

#include "accum_property_generator.hpp"

#include <sstream>
#include <typeinfo>

//========+========+========+========+========+========+========+========+========+========+
//TYPE TRAIT
//========+========+========+========+========+========+========+========+========+========+
template <typename T>
struct max_num_bin_type
{
    typedef int type;    //double-dummy for now
};

IMPLEMENT_FUNCTION(max_num_bin)

#endif //MAX_NUM_BIN_PROPERTY_HEADER
