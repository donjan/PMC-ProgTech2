#ifndef COUNT_PROPERTY_HEADER
#define COUNT_PROPERTY_HEADER

#include "accum_property_generator.hpp"

#include <boost/cstdint.hpp>

#include <sstream>
#include <typeinfo>

//========+========+========+========+========+========+========+========+========+========+
//TYPE TRAIT
//========+========+========+========+========+========+========+========+========+========+
template <typename T = int>
struct count_type
{
    typedef boost::int64_t type;
};

IMPLEMENT_FUNCTION(count)

#endif //COUNT_PROPERTY_HEADER
