//!
//! Be Expectations
//! ================
//!
//! The be expectations should be used to determine whether a value meets
//! a certain equality or comparison expectation.
//! 
//! .. function:: Be( ExpectedT )
//!
//!     Creates a be expectation.  This expectation determines whether
//!     a value matches another value or not.
//!
//!     .. todo:: Instead of linking directly to SHOULD & SHOULD_NOT maybe just
//!               link to a macro section or something (so we don't miss out
//!               MUST etc.)
//!
//!     Meant to be used with :c:macro:`SHOULD` and :c:macro:`SHOULD_NOT` 
//!     For example::
//!
//!         intList SHOULD Be(1);      // Will pass
//!         intList SHOULD Be(4);      // Will fail
//!         intList SHOULD_NOT Be(4);  // Will pass
//!         intList SHOULD_NOT Be(1);  // Will fail
//!
//!     .. todo:: Link to information on SHOULD_BE & SHOULD_NOT_BE etc.
//!

#ifndef CPPSHOULD_EXPECTATIONS_BE_H_
#define CPPSHOULD_EXPECTATIONS_BE_H_

#include "cppshould/expectations/base.hpp"
#include "cppshould/traits.hpp"
#include "cppshould/utils.hpp"

namespace cppshould {
namespace expectations {
namespace impl {

//
// Class that implements Be expectations
//
template< class ExpectedT >
class BeExpectation : public Expectation< ExpectedT >
{
public:
    BeExpectation( ExpectedT expect ) :
    m_expect( expect )
    {}

    ExpectedT m_expect;

protected:
    virtual std::string ToString() const;
};

template< class ExpectedT >
std::string BeExpectation< ExpectedT >::ToString() const
{
    return "be equal to " + ToStringTraits< ExpectedT >::Convert( m_expect );
}

}   // namespace impl

//
// Factory function for be expectations
//
template< class ExpectedT >
impl::BeExpectation< ExpectedT > Be( ExpectedT expect )
{
    return impl::BeExpectation< ExpectedT >(expect);
}

}   // namespace expectations

//
// Traits specialization for be expectation
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::BeExpectation< ExpectedT >
    >
{
    typedef EquivalenceTraits< 
        typename remove_refcv< ActualT >::type, 
        typename remove_refcv< ExpectedT >::type
        > EquivTraits;

    static bool Matches(
            const ActualT& actual,
            const expectations::impl::BeExpectation< ExpectedT >& expectation
            )
    {
        return EquivTraits::Equivalent( actual, expectation.m_expect );
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_EXPECTATIONS_BE_H_

