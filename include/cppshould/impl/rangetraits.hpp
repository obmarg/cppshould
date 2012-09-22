//
// This class provides specializations of RangeTraits for known
// types.
//

// TODO: Probably want to detail all these types in the documentation
//       somewhere.

#ifndef CPPSHOULD_IMPL_RANGETRAITS_H_
#define CPPSHOULD_IMPL_RANGETRAITS_H_

#include <vector>
#include <deque>
#include <list>
#include <string>

namespace cppshould {

//
// Vector is a range
//
template< class ItemType, class Allocator >
struct RangeTraits< std::vector< ItemType, Allocator > >
{
    static const bool IsRange = true;
    typedef ItemType ValueT;
};

//
// Deque is a range
//
template< class ItemType, class Allocator >
struct RangeTraits< std::deque< ItemType, Allocator > >
{
    static const bool IsRange = true;
    typedef ItemType ValueT;
};

//
// List is a range
//
template< class ItemType, class Allocator >
struct RangeTraits< std::list< ItemType, Allocator > >
{
    static const bool IsRange = true;
    typedef ItemType ValueT;
};

//
// String is a range
//
template< class CharT, class Traits, class Allocator >
struct RangeTraits< std::basic_string< CharT, Traits, Allocator > >
{
    static const bool IsRange = true;
    typedef CharT ValueT;
};

}   // namespace cppshould

#endif  // CPPSHOULD_IMPL_RANGETRAITS_H_
