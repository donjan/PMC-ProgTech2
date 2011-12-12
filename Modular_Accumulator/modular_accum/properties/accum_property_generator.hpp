#ifndef ACCUM_WRAPPER_MACRO_HEADER
#define ACCUM_WRAPPER_MACRO_HEADER

//~ #include "../accum_exception.hpp"
#include "../accum_prewrapper.hpp"
#include "../value_type_trait.hpp"

#include <typeinfo>
#include <sstream>

//========+========+========+========+========+========+========+========+========+========+
//INFO TRAIT
//========+========+========+========+========+========+========+========+========+========+
#define IMPLEMENT_FUNCTION(FCT) \
    template<typename Accum> \
    struct has_ ## FCT \
    { \
        template<int i> struct helper { \
            typedef char type; \
        }; \
        template<typename U> static char check(typename helper<sizeof(&U::FCT)>::type); \
        template<typename U> static double check(...); \
        enum \
        { \
            value = (sizeof(char) == sizeof(check<Accum>(0))) \
        }; \
    };\
    \
    \
    \
template <typename Accum>\
typename FCT ## _type<typename value_type<Accum>::type>::type FCT(Accum const & arg)\
{\
    return arg.FCT();\
}\
namespace detail \
{ \
    template <typename base, bool> \
    class FCT ## _property_impl: public base \
    { \
    public:\
		FCT ## _property_impl() {}\
		FCT ## _property_impl(typename base::accum_type const & arg): base(arg) {}\
		\
        typename FCT ## _type<typename value_type<typename base::accum_type>::type >::type FCT() const \
        { \
            return ::FCT(base::accum_); \
        } \
    }; \
    template <typename base> \
    class FCT ## _property_impl<base, false>: public base \
    { \
    public:\
		FCT ## _property_impl() {}\
		FCT ## _property_impl(typename base::accum_type const & arg): base(arg) {}\
        \
        typename FCT ## _type<typename value_type<typename base::accum_type>::type >::type FCT() const \
        { \
            std::stringstream out; \
            out << typeid(typename base::accum_type).name(); \
            out << " has no ";\
            out << #FCT;\
            out << "-method"; \
            return typename FCT ## _type<typename value_type<typename base::accum_type>::type >::type(0); \
        } \
    };\
} \
template <typename base> \
class FCT ## _property: public detail::FCT ## _property_impl<base, has_ ## FCT<typename base::accum_type>::value> \
{\
public:\
	FCT ## _property() {}\
	FCT ## _property(typename base::accum_type const & acc): detail::FCT ## _property_impl<base, has_ ## FCT<typename base::accum_type>::value>(acc) {}\
};




#endif //ACCUM_WRAPPER_MACRO_HEADER
