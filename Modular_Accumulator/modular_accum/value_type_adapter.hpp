#ifndef VALUE_TYPE_ADAPTER_HEADER
#define VALUE_TYPE_ADAPTER_HEADER

#include "modular_accum.hpp"

#include <typeinfo>

namespace detail
{
template<typename T, typename U> 
class Adapter<ValueType<T>, U>
{
    public:
        typedef T value_type;
        
        Adapter<ValueType<T>, U>(Adapter<ValueType<T>, U> const & arg) {}
        
        template <typename ArgumentPack>
        Adapter<ValueType<T>, U>(ArgumentPack const & args) {}
        
        void operator <<(value_type val) 
        {
        }
        template<typename Stream> void print(Stream & os) {
            os << "ValueType: " << typeid(value_type).name() << " ";
        }

};

} // end namespace detail

#endif // VALUE_TYPE_ADAPTER
