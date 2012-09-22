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
    return impl::ContainExpectation< ExpectedT >( expect );
}

//
// Factory function for char* Contain expectation
//
static impl::ContainExpectation< std::string > Contain( const char* expect )
{
    return impl::ContainExpectation< std::string >( expect );
}

}   // namespace expectations

//
// Traits specialization for contains with non-ranges
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::ContainExpectation< ExpectedT >,
    typename std::enable_if< !RangeTraits< ExpectedT >::IsRange >::type
    >
{
    static_assert(
            RangeTraits< ActualT >::IsRange,
            "The Contain expectation must be used against a range"
            );

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
// Traits specialization for Contains(range)
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::ContainExpectation< ExpectedT >,
    typename std::enable_if< RangeTraits< ExpectedT >::IsRange >::type
    >
{
    static_assert(
            RangeTraits< ActualT >::IsRange,
            "The Contain expectation must be used against a range"
            );

    typedef EquivalenceTraits<
        typename RangeTraits< ActualT >::ValueT,
        typename RangeTraits< ExpectedT >::ValueT
        > EquivTraits;

    static bool Matches(
            const ActualT& actual,
            const expectations::impl::ContainExpectation< ExpectedT >& expectation
            )
    {
        auto result = std::find_end(
                std::begin( actual ), std::end( actual ),
                std::begin( expectation.m_expect ),
                std::end( expectation.m_expect ),
                EquivalencePred()
                );
        return result != std::end( actual );
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_EXPECTATIONS_CONTAIN_H_
