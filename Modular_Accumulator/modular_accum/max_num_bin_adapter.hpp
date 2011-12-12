#ifndef MAX_NUM_BIN_ADAPTER_HEADER
#define MAX_NUM_BIN_ADAPTER_HEADER

#include "modular_accum.hpp"

struct MaxNumberBinning {};

namespace detail
{
template<>
struct Dependencies<MaxNumberBinning> 
{
    typedef MakeList<Count, Mean, Error>::type type;
};
#include <vector>
template<typename T> 
class Adapter<MaxNumberBinning, T> : public T 
{
        
        typedef typename max_num_bin_type<typename T::value_type>::type num_bin_type;
        typedef typename std::vector<typename T::value_type>::size_type count_type;
    public:
        Adapter<MaxNumberBinning, T>(Adapter<MaxNumberBinning, T> const & arg): T(static_cast<T const &>(arg)), bin_(arg.bin_), partial_(arg.partial_), elements_in_bin_(arg.elements_in_bin_), pos_in_partial_(arg.pos_in_partial_), max_bin_number_(arg.max_bin_number_) {}

        template<typename ArgumentPack>
        Adapter<MaxNumberBinning, T>(ArgumentPack const & args): T(args), partial_(), elements_in_bin_(1), pos_in_partial_(0), max_bin_number_(args[_bin_number]) 
        {std::cout << "Max: " << args[_bin_number] << " " << std::endl;}
        
        num_bin_type max_num_bin() const { return max_bin_number_;};
        void operator <<(typename T::value_type val) 
        {
            T::operator <<(val);
            
            partial_ = partial_ + val;
            ++pos_in_partial_;
            
            if(pos_in_partial_ == elements_in_bin_)
            {
                if(bin_.size() >= max_bin_number_)
                {
                    if(max_bin_number_ % 2 == 1)
                    {
                        partial_ += bin_[max_bin_number_ - 1];
                        pos_in_partial_ += elements_in_bin_;
                    }
                    
                    for(unsigned int i = 0; i < max_bin_number_ / 2; ++i) //the rounding down here is intentional
                        bin_[i] = bin_[2*i] + bin_[2*i + 1];
                    
                    bin_.erase(bin_.begin() + max_bin_number_ / 2, bin_.end());
                    
                    elements_in_bin_ *= 2;
                }
                if(pos_in_partial_ == elements_in_bin_)
                {
                    bin_.push_back(partial_);
                    partial_ = typename T::value_type();
                    pos_in_partial_ = 0;
                }
            }
        }
        template<typename Stream> 
        void print(Stream & os) 
        {
            T::print(os);
            os << "MaxBinningNumber: " << max_num_bin() << std::endl;
            
            for (unsigned int i = 0; i < bin_.size(); ++i)
            {
                os << "bin[" << i << "] = " << bin_[i] << std::endl;
            }
        }
        private:
            std::vector<typename T::value_type> bin_;
            typename T::value_type partial_;
            count_type elements_in_bin_;
            count_type pos_in_partial_;
            count_type max_bin_number_;
};

} // end namespace detail

#endif // MAX_NUM_BIN_ADAPTER
