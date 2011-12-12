#ifndef VALUE_TRAIT_HEADER
#define VALUE_TRAIT_HEADER

template <typename Accum>
struct value_type
{
    typedef typename Accum::value_type type;
};

#endif //VALUE_TRAIT_HEADER
