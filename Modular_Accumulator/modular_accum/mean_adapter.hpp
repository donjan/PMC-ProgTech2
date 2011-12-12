#ifndef MEAN_ADAPTER_HEADER
#define MEAN_ADAPTER_HEADER

#include "modular_accum.hpp"

#include <boost/utility.hpp>
#include <boost/type_traits.hpp>

struct Mean {};

namespace detail
{
    
    template<> 
    struct Dependencies<Mean> 
    {
        typedef MakeList<Count>::type type;
    };
    template<typename T> 
    class Adapter<Mean, T> : public T 
    {
            typedef typename mean_type<typename T::value_type>::type mean_type;
        public:
            Adapter<Mean, T>(Adapter<Mean, T> const & arg): T(static_cast<T const &>(arg)), mean_(arg.mean_) {}
            
            template<typename ArgumentPack>
            Adapter<Mean, T> (ArgumentPack const & args): T(args), mean_() {}
            
            mean_type mean() const { return mean_;};
            void operator <<(typename T::value_type val) 
            {
                T::operator <<(val);
                mean_ = ((T::count()-1) * mean_ + val)/T::count();
            }
            template<typename Stream> 
            void print(Stream & os) 
            {
                T::print(os);
                os << "Mean: " << mean() << " ";
            }
        private:
            mean_type mean_;
    };
} // end namespace detail

#endif // MEAN_ADAPTER
