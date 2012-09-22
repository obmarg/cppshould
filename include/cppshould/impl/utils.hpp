//
// This file defines some utilities used throughout cppshould
//

#ifndef CPPSHOULD_UTILS_H_
#define CPPSHOULD_UTILS_H_

#include <cppshould/traits.hpp>
#include <type_traits>

namespace cppshould {

//
// Shortcut to remove reference & const/volatile modifiers
//
template< class T >
struct remove_refcv
{
    typedef typename std::remove_reference< 
        typename std::remove_cv< T >::type 
        >::type type;
};

//
// Utility template to allow EquivaenceTraits to be used
// as a predicate easily
//
struct EquivalencePred
{
    template< class LhsT, class RhsT >
    bool operator()( const LhsT lhs, const RhsT rhs )
    {
        return EquivalenceTraits< LhsT, RhsT >::Equivalent( lhs, rhs );
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_UTILS_H_
