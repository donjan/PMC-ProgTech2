#ifndef COUNT_ADAPTER_HEADER
#define COUNT_ADAPTER_HEADER

#include "modular_accum.hpp"

struct Count {};

namespace detail
{
template<typename T> 
class Adapter<Count, T> : public T 
{
    public:
        Adapter<Count, T>(Adapter<Count, T> const & arg): T(static_cast<T const &>(arg)), count_(arg.count_) {}

        template<typename ArgumentPack>
        Adapter<Count, T>(ArgumentPack const & args): T(args), count_() {}
        
        typename count_type<typename T::value_type>::type count() const 
        { 
            return count_; 
        }
        void operator <<(typename T::value_type val) 
        {
            T::operator <<(val);
            ++count_;
        }
        template<typename Stream> void print(Stream & os) 
        {
            T::print(os);
            os << "Count: " << count() << " ";
        }
    private:
        typename count_type<typename T::value_type>::type count_;
};

} // end namespace detail

#endif // COUNT_ADAPTER
