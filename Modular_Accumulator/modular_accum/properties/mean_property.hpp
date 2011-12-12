#ifndef MEAN_PROPERTY_HEADER
#define MEAN_PROPERTY_HEADER

#include "accum_property_generator.hpp"
#include <boost/static_assert.hpp>


#include <sstream>
#include <typeinfo>
#include <limits>


//========+========+========+========+========+========+========+========+========+========+
//TYPE TRAIT
//========+========+========+========+========+========+========+========+========+========+

namespace detail
{
    template<unsigned n> struct static_array
    {
        char type[n];
    };
    
    template <typename T, int>
    struct mean_type_impl
    {
        typedef T type;
    };
    template <typename T>
    struct mean_type_impl<T, 2>
    {
        typedef double type;
    };
    template <typename T>
    struct mean_type_impl<T, 3>
    {
        BOOST_STATIC_ASSERT_MSG("mean_type trait failed", false);
    };
}

template <typename value_type>
struct mean_type
{
    private:
        typedef value_type T;
        static T t;
        static detail::static_array<1> test(T);
        static detail::static_array<2> test(double);
        static detail::static_array<3> test(...);
    public:
        typedef typename detail::mean_type_impl<T, sizeof(test((t+t)/double(1)))/sizeof(char)>::type type;
};

template<>
struct mean_type<double>
{
	public:
		typedef double type;
};

#include <vector>
//========+========+========+========+========+========+========+========+========+========+
//CUSTOM ACCUMULATOR
//========+========+========+========+========+========+========+========+========+========+
//~ typedef std::vector<int> custom_accum;
//~ 
//~ template<>
//~ struct value_type<custom_accum>
//~ {
    //~ typedef int type;
//~ };
//~ 
//~ //template<><custom_accum>
//~ typename mean_type<typename value_type<custom_accum>::type>::type const mean(custom_accum const & arg)
//~ {
    //~ return arg.size();
//~ }

IMPLEMENT_FUNCTION(mean)


#endif //MEAN_PROPERTY_HEADER
