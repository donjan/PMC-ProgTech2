#ifndef ACCUM_PREWRAPPER_HEADER
#define ACCUM_PREWRAPPER_HEADER

//========+========+========+========+========+========+========+========+========+========+
//PREWRAPPER ACCUMULATOR
//========+========+========+========+========+========+========+========+========+========+
template <typename Accum, typename result_type_base> 
class accumulator_prewrapper: public result_type_base
{
    public:
        typedef Accum accum_type;

        accumulator_prewrapper() {}
        accumulator_prewrapper(Accum const & acc): accum_(acc) {}
    protected:
        Accum accum_;
};

#endif //ACCUM_PREWRAPPER_HEADER
