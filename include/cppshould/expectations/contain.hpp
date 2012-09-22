//!
//! Contain
//! =======
//!
//! The contain expectation should be used to determine whether a range contains
//! a specific value or range of values.
//!
//! .. function:: Contain( ExpectedT )
//!
//!     Creates a contain expectation
//!
//!     .. todo:: Instead of linking directly to SHOULD & SHOULD_NOT maybe just
//!               link to a macro section or something (so we don't miss out
//!               MUST etc.)
//!
//!     Meant to be used with :c:macro:`SHOULD` and :c:macro:`SHOULD_NOT` 
//!     For example::
//!
//!         intList SHOULD Contain(1);      // Will pass
//!         intList SHOULD Contain(4);      // Will fail
//!         intList SHOULD_NOT Contain(4);  // Will pass
//!         intList SHOULD_NOT Contain(1);  // Will fail
//!
//!     .. todo:: Once the ContainsAll, ContainsAny etc. are defined, link to them

#ifndef CPPSHOULD_EXPECTATIONS_CONTAIN_H_
#define CPPSHOULD_EXPECTATIONS_CONTAIN_H_

#include "cppshould/impl/utils.hpp"
#include "cppshould/expectations/base.hpp"
#include "cppshould/traits.hpp"
#include <type_traits>

namespace cppshould {
namespace expectations {
namespace impl {

//
// Class that implements Contain expectations
//
template< class ExpectedT >
class ContainExpectation : public Expectation< ExpectedT >
{
public:
    ContainExpectation( ExpectedT expect ) :
    m_expect( expect )
    {}

    ExpectedT m_expect;

protected:
    virtual std::string ToString() const;
};

//
// Returns the expectation expressed as a string
//
template< class ExpectedT >
std::string ContainExpectation< ExpectedT >::ToString() const
{
    return "contain " + ToStringTraits< ExpectedT >::Convert( m_expect );
}

}   // namespace impl

//
// Factory function for Contain expectation
//
template< class ExpectedT >
impl::ContainExpectation< ExpectedT > Contain( ExpectedT expect )
{
    // TODO: Maybe want to check if ExpectedT makes sense?
    //       Though in this case I think it always would - most things
    //       could be in a range, more depends on the type of range
    return impl::ContainExpectation< ExpectedT >( expect );
}

}   // namespace expectations

//
// Traits specialization of contains for non-ranges
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::ContainExpectation< ExpectedT >,
    typename std::enable_if< !RangeTraits< ExpectedT >::IsRange >::type
    >
{
    typedef EquivalenceTraits<
        typename ActualT::value_type, typename remove_refcv< ExpectedT >::type
        > EquivTraits;

    static bool Matches(
            const ActualT& actual,
            const expectations::impl::ContainExpectation< ExpectedT >& expectation
            )
    {
        // TODO: Maybe this to a foreach at some point?
        //       Or just a std::find_if
        for ( auto it = std::begin(actual); it != std::end(actual); ++it )
        {
            if ( EquivTraits::Equivalent( *it, expectation.m_expect ) )
            {
                return true;
            }
        }
        return false;
    }
};

//
// Traits specialization of contains for ranges
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::ContainExpectation< ExpectedT >,
    typename std::enable_if< RangeTraits< ExpectedT >::IsRange >::type
    >
{
    typedef EquivalenceTraits<
        typename ActualT::value_type, typename RangeTraits< ExpectedT >::ValueT
        > EquivTraits;

    static bool Matches(
            const ActualT& actual,
            const expectations::impl::ContainExpectation< ExpectedT >& expectation
            )
    {
        // TODO: Finish implementing this
        return true;
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_EXPECTATIONS_CONTAIN_H_
