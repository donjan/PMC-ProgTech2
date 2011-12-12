#ifndef AUTOCORR_ADAPTER_HEADER
#define AUTOCORR_ADAPTER_HEADER

#include <boost/cstdint.hpp>

#include "modular_accum.hpp"

struct Autocorrelation {};

namespace detail
{
template<> 
struct Dependencies<Autocorrelation> 
{
    typedef MakeList<Count, Mean, Error>::type type;
};
template<typename T> 
class Adapter<Autocorrelation, T> : public T 
{
        typedef typename autocorr_type<typename T::value_type>::type auto_bin_type;
        typedef typename std::vector<typename T::value_type>::size_type count_type;
    public:    
        Adapter<Autocorrelation, T>(Autocorrelation const & arg): T(arg) {}
    
        template<typename ArgumentPack>
        Adapter<Autocorrelation, T>(ArgumentPack const & args): T(args) {std::cout << "Auto: " << args[_bin_auto] << " " << std::endl;}
        
        auto_bin_type autocorr() const { return 0; };
        void operator <<(typename T::value_type val) 
        {
            T::operator <<(val);
        }
        template<typename Stream> 
        void print(Stream & os) 
        {
            T::print(os);
            os << "Autocorrelation ";
        }
        private:
            std::vector<typename T::value_type> bin_;
            typename T::value_type partial_;
            count_type elements_in_bin_;
            count_type pos_in_partial_;
            count_type max_bin_number_;
};

} // end namespace detail

#endif // AUTOCORR_ADAPTER
