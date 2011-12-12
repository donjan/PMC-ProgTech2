#ifndef MODULAR_ACCUM_HEADER
#define MODULAR_ACCUM_HEADER


#define FLAG(x) std::cout << "FLAG: " << #x << std::endl;

#include "../../properties.hpp"

#include <boost/static_assert.hpp>
#include <boost/parameter.hpp>

#include <iostream>


template<typename T> 
struct ValueType {};

namespace detail
{
// Copyright (C) 2010 Lukas Gamper <gamperl -at- gmail.com>
// Define list
template<typename T, typename N> 
struct ListItem 
{
    typedef T type;
    typedef N next;
};
struct ListEnd {};

// Remove void
template<typename T> 
struct RemoveVoid 
{
    typedef T type;
};
template<typename T, typename N> 
struct RemoveVoid<ListItem<T, N> > 
{
    typedef ListItem<T, typename RemoveVoid<N>::type> type;
};
template<typename N> 
struct RemoveVoid<ListItem<void, N> > 
{
    typedef typename RemoveVoid<N>::type type;
};

// Make list operator
template<
      typename _0  = void
    , typename _1  = void
    , typename _2  = void
    , typename _3  = void
    , typename _4  = void
    , typename _5  = void
    , typename _6  = void
    , typename _7  = void
    , typename _8  = void
    , typename _9  = void
> struct MakeList 
{
    typedef typename RemoveVoid<
            ListItem<_0, ListItem<_1, ListItem<_2, ListItem<_3, ListItem<_4, 
            ListItem<_5, ListItem<_6, ListItem<_7, ListItem<_8, ListItem<_9, ListEnd
            > > > > > > > > > > >::type type;
};

// Concat tow lists
template <typename T, typename U> 
struct ConcatinateLists 
{
    typedef ListItem<typename T::type, typename ConcatinateLists<typename T::next, U>::type > type;
};
template <typename U> 
struct ConcatinateLists<ListEnd, U> 
{
    typedef U type;
};

// Make list unique
template <typename T, typename N> 
struct UniqueListWalker 
{
    typedef ListItem< 
        typename N::type, 
        typename UniqueListWalker<T, typename N::next>::type 
    > type;
};
template <typename T, typename N> 
struct UniqueListWalker<T, ListItem<T, N> > 
{
    typedef typename UniqueListWalker<T, N>::type type;
};
template <typename T> 
struct UniqueListWalker<T, ListEnd> 
{
    typedef ListEnd type;
};
template <typename T> struct UniqueList 
{
    typedef ListItem<
        typename T::type, 
        typename UniqueList<
        typename UniqueListWalker<typename T::type, typename T::next>::type
        >::type
    > type;
};
template <> 
struct UniqueList<ListEnd> 
{
    typedef ListEnd type;
};

template<typename T> 
struct FindValueType 
{
    typedef typename FindValueType<typename T::next>::type type;
};
template<typename T, typename N> 
struct FindValueType<ListItem<ValueType<T>, N> > 
{
    typedef ValueType<T> type;
};
template<> 
struct FindValueType<ListEnd> {
    BOOST_STATIC_ASSERT_MSG(true, "No ValueType added!");
};
template<typename T> 
struct ValueTypeFirst 
{
    typedef ListItem<typename FindValueType<T>::type, T> type;
};


// Dependencies
template<typename T> struct Dependencies 
{
    typedef MakeList<>::type type;
};

// Resolve dependancies
template <typename T> 
struct ResolveDependencies 
{
    typedef typename ConcatinateLists<
        typename ResolveDependencies<typename Dependencies<typename T::type>::type>::type, 
        ListItem<
            typename T::type, 
            typename ResolveDependencies<typename T::next>::type
        >
    >::type type;
};
template <> 
struct ResolveDependencies<ListEnd> 
{
    typedef ListEnd type;
};

// Adapter Type
template<typename T, typename U> 
struct Adapter {};

// Derive from adapter classes
template<typename T, typename U> 
struct DeriveProperties 
{
    typedef typename DeriveProperties<
        typename T::next, 
        Adapter<typename T::type, U>
    >::type type;
};
template<typename T> 
struct DeriveProperties<ListEnd, T> 
{
    typedef T type;
};

// Accumulator
struct UselessBase {};
template<
      typename _0  = void
    , typename _1  = void
    , typename _2  = void
    , typename _3  = void
    , typename _4  = void
    , typename _5  = void
    , typename _6  = void
    , typename _7  = void
    , typename _8  = void
    , typename _9  = void
> 
struct Accumulator : public DeriveProperties<
    typename UniqueList<
        typename ResolveDependencies<
            typename ValueTypeFirst<
                typename MakeList<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>::type
            >::type
        >::type
    >::type,
    UselessBase
>::type {
    typedef typename DeriveProperties<typename UniqueList<typename ResolveDependencies<typename ValueTypeFirst<typename MakeList<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>::type>::type>::type>::type,UselessBase>::type base;
    
    template <typename ArgumentPack>
    Accumulator(ArgumentPack const & args): base(args) {}
    
    Accumulator(Accumulator const & arg): base(static_cast<base const &>(arg)) {}
    
};
template<
      typename _0
    , typename _1
    , typename _2
    , typename _3
    , typename _4
    , typename _5
    , typename _6
    , typename _7
    , typename _8
    , typename _9
> 
std::ostream & operator <<(std::ostream & os, Accumulator<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9> & a)
{
    a.print(os);
    return os;
}
} // end namespace detail
// = = = = N A M E D   P A R A M E T E R   C T O R   D E F I N I T I O N = = = =

BOOST_PARAMETER_NAME(bin_size)
BOOST_PARAMETER_NAME(bin_number)
BOOST_PARAMETER_NAME(bin_auto)

template<
      typename _0  = void
    , typename _1  = void
    , typename _2  = void
    , typename _3  = void
    , typename _4  = void
    , typename _5  = void
    , typename _6  = void
    , typename _7  = void
    , typename _8  = void
    , typename _9  = void
> 
class modular_accum: public detail::Accumulator<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9>
{
        typedef detail::Accumulator<_0, _1, _2, _3, _4, _5, _6, _7, _8, _9> base;
    public:
        modular_accum(modular_accum const & arg): base(static_cast<base const &>(arg)) {}
        BOOST_PARAMETER_CONSTRUCTOR(
        modular_accum, 
        (base),
        tag,
        (optional 
            (bin_size, *)
            (bin_number, *)
            (bin_auto, *)
        )
        )
};


// = = = = = = = = = = P R O P E R T Y   D E F I N I T I O N = = = = = = = = = =
struct Count;
struct Mean;
struct Error;
struct FixSizeBinning;
struct MaxNumberBinning;
struct Autocorrelation;

#endif // MODULAR_ACCUM_HEADER
