#ifndef FIX_SIZE_BIN_ADAPTER_HEADER
#define FIX_SIZE_BIN_ADAPTER_HEADER

#include "modular_accum.hpp"

struct FixSizeBinning {};

namespace detail
{
template<> 
struct Dependencies<FixSizeBinning> 
{
    typedef MakeList<Count, Mean, Error>::type type;
};

template<typename T> 
class Adapter<FixSizeBinning, T> : public T 
{
        typedef typename fix_size_bin_type<typename T::value_type>::type fix_bin_type;
        typedef typename std::vector<typename T::value_type>::size_type count_type;
    public:
        Adapter<FixSizeBinning, T>(Adapter<FixSizeBinning, T> const & arg): T(static_cast<T const &>(arg)), bin_(arg.bin_), partial_(arg.partial_), partial_count_(arg.partial_count_), bin_size_(arg.bin_size_) {}
        
        template<typename ArgumentPack>
        Adapter<FixSizeBinning, T>(ArgumentPack const & args): T(args), partial_(), partial_count_(0), bin_size_(args[_bin_size]) 
        {std::cout << "Fix: " << args[_bin_size] << " " << std::endl;}
        
        fix_bin_type fix_size_bin() const { return bin_size_; };
        void operator <<(typename T::value_type val) 
        {
            T::operator <<(val);
            
            partial_ += val;
            ++partial_count_;
            
            if(partial_count_ == bin_size_)
            {
                bin_.push_back(partial_);
                partial_count_ = 0;
                partial_ = typename T::value_type();
            }
        }
        template<typename Stream> 
        void print(Stream & os) 
        {
            T::print(os);
            os << "FixBinSize: " << fix_size_bin() << " " << "BinNumber: " << bin_.size() << " ";
        }
    private:
        std::vector<typename T::value_type> bin_;
        typename T::value_type partial_;
        count_type partial_count_;
        count_type bin_size_;
};

} // end namespace detail

#endif // FIX_SIZE_BIN_ADAPTER
