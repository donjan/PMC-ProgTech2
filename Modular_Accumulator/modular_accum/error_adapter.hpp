#ifndef ERROR_ADAPTER_HEADER
#define ERROR_ADAPTER_HEADER

#include "modular_accum.hpp"

#include <cmath>

struct Error {};

namespace detail
{
template<> 
struct Dependencies<Error> 
{
    typedef MakeList<Count, Mean>::type type;
};

template<typename T> 
class Adapter<Error, T> : public T 
{
        typedef typename error_type<typename T::value_type>::type error_type;
    public:
        Adapter<Error, T>(Adapter<Error, T> const & arg): T(static_cast<T const &>(arg)), mean2_(arg.mean2_) {}
        
        template<typename ArgumentPack>
        Adapter<Error, T>(ArgumentPack const & args): T(args), mean2_() {}
        
        error_type error() const 
        { 
            return sqrt((mean2_ - T::mean()*T::mean()) / ((T::count() - 1)));
        }; 
        void operator <<(typename T::value_type val) 
        {
            T::operator <<(val);
            mean2_ = ((T::count()-1) * mean2_ + val*val)/T::count();
        }
        template<typename Stream> 
        void print(Stream & os) 
        {
            T::print(os);
            os << "Error: " << error() << " ";
        }
    private:
        error_type mean2_;
};

} // end namespace detail

#endif // ERROR_ADAPTER
