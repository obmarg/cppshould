//
// This class provides specializations of RangeTraits for known
// types.
//

// TODO: Probably want to detail all these types in the documentation
//       somewhere.

#ifndef CPPSHOULD_IMPL_RANGETRAITS_H_
#define CPPSHOULD_IMPL_RANGETRAITS_H_

namespace cppshould {

//
// Vector is a range
//
template< class ItemType >
struct RangeTraits< std::vector< ItemType > >
{
    static const bool IsRange = true;
    typedef ItemType ValueT;
};

}   // namespace cppshould

#endif  // CPPSHOULD_IMPL_RANGETRAITS_H_
