#ifndef accumulator_HEADER
#define accumulator_HEADER

#include <boost/lambda/lambda.hpp>

#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

class accumulator
{
        typedef double mean_type;
        typedef double error_type;
        typedef int count_type;
    public:
        
		typedef double value_type;
        
        accumulator(count_type bin_size): partial_counter_(0), bin_size_(bin_size) {}
        accumulator(const accumulator& arg): bin_(arg.bin_), partial_(arg.partial_), partial_counter_(arg.partial_counter_), bin_size_(arg.bin_size_) {}
        ~accumulator() {}
        
        mean_type mean()
        {
            return accumulate(bin_.begin(), bin_.end(), .0)/value_type(bin_.size());
        }
        
        error_type error()
        {
            using namespace boost::lambda;
            mean_type mean_ = mean();
            
            value_type sum2 = 0;
            for_each(bin_.begin(), bin_.end(), sum2 += _1*_1);
            return sqrt((sum2 / double(bin_.size()) - mean_ * mean_) / (bin_.size() - 1));
        }
        
        accumulator & operator<<(value_type value)
        {
            partial_ += value;
            ++partial_counter_;
            
            if(partial_counter_ == bin_size_)
            {
                bin_.push_back(partial_/bin_size_);
                partial_counter_ = 0;
                partial_ = 0;
            }
            return *this;
        }
        
        void print(std::ostream& out) const
        {
            out << " bin_size: ";
            out << bin_size_;
            out << " current full bins: ";
            out << bin_.size();
        }
        count_type count() const
        {
            return bin_.size();
        }
    private:
        std::vector<value_type> bin_;
        value_type partial_;
        count_type partial_counter_;
        count_type bin_size_;
};

std::ostream& operator<<(std::ostream& out, accumulator & d)
{
    out << "accumulator: ";
    out << "mean: ";
    out << d.mean();
    out << " error: ";
    out << d.error();
    d.print(out);
    return out;
}

#endif //accumulator_HEADER
