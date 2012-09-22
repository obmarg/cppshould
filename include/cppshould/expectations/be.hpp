//!
//! Be Expectations
//! ================
//!
//! The be expectations should be used to determine whether a value meets
//! a certain equality or comparison expectation.
//!
//! Equality Expectations
//! ----------------------
//!
//! These expectations check that values are equal to expected values
//!
//! .. function:: Be( ExpectedT expected )
//!
//!     Creates a be expectation.  This expectation determines whether
//!     a value matches another value or not.
//!
//!     .. todo:: Instead of linking directly to SHOULD & SHOULD_NOT maybe just
//!               link to a macro section or something (so we don't miss out
//!               MUST etc.)
//!
//!     .. todo:: Mention that comparison is done with EquivalenceTraits
//!               (which falls back on ==)
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
//! .. function:: BeApprox( ExpectedT expected, ExpectedT factor )
//!
//!     Creates a be approximately expectation.  This expectation determines
//!     whether a value is close to another value or not.
//!
//!     Unlike func::`Be` this expectation does not rely on traits to do
//!     it's comparisons, instead relying on ``operator>=`` & ``operator<=``.
//!     This means that it is only suitable for use with types for which
//!     these operators are defined, such as integers and floats.  Types
//!     which define ``operator<`` will also work as the other operators
//!     can be emulated with this operator.
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
//! Comparison Expectations
//! -----------------------
//!
//! These expectations check that values compare correctly to expected values
//!
//! These expectations do not currently rely on traits to do
//! their comparisons, instead relying on the plain comparison operators.
//! This means that they are only suitable for use with types for which
//! these operators are defined, such as integers and floats.  Types
//! which define ``operator<`` & ``operator==`` will also work as the 
//! other operators can be emulated with this operator.
//!
//! .. function:: BeGreaterThan( ExpectedT expected )
//!
//!     Creates an expectation that checks a value is greater than the 
//!     expected value
//!
//! .. function:: BeGreaterThanOrEqual( ExpectedT expected )
//!
//!     Creates an expectation that checks a value is greater than or equal
//!     to the expected value
//!
//! .. function:: BeLessThan( ExpectedT expected )
//!
//!     Creates an expectation that checks a value is less than the 
//!     expected value
//!
//! .. function:: BeLessThanOrEqual( ExpectedT expected )
//!
//!     Creates an expectation that checks a value is less than or equal
//!     to the expected value
//!

#ifndef CPPSHOULD_EXPECTATIONS_BE_H_
#define CPPSHOULD_EXPECTATIONS_BE_H_

#include "cppshould/expectations/base.hpp"
#include "cppshould/traits.hpp"
#include "cppshould/impl/utils.hpp"
#include <sstream>
#include <utility>

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

//
// Class that implements BeApprox expectation
//
template< class ExpectedT >
class BeApproxExpectation : public Expectation< ExpectedT >
{
public:
    BeApproxExpectation( ExpectedT expect, ExpectedT factor ) :
    m_expect( expect ),
    m_factor( factor )
    {}

    // TODO: Might be nice to have some sort of Factor( int )
    //       function for setting the factor.

    ExpectedT m_expect;
    ExpectedT m_factor;

protected:
    virtual std::string ToString() const;
};

template< class ExpectedT >
std::string BeApproxExpectation< ExpectedT >::ToString() const
{
    std::ostringstream oss;
    oss << "be approximately equal to "
        << ToStringTraits< ExpectedT >::Convert( m_expect )
        << " (by a factor of "
        << ToStringTraits< ExpectedT >::Convert( m_factor )
        << ")";
    return oss.str();
}

//
// Class that implements comparison expectations (BeGreaterThan etc.)
//
template< class ExpectedT >
class ComparisonExpectation : public Expectation< ExpectedT >
{
public:
    // TODO: In the future I think I could use a functor template
    //       parameter to indicate the comparison type.
    //       Like std::less_than etc. but with more flexibility
    //       around arguments.
    //       This'll do for now though
    enum ComparisonType
    {
        GreaterThan,
        GreaterThanEqual,
        LessThan,
        LessThanEqual
    };

public:
    ComparisonExpectation( ExpectedT expected, ComparisonType type ) :
    m_expected( expected ),
    m_type( type )
    {}

    ExpectedT       m_expected;
    ComparisonType  m_type;

protected:
    virtual std::string ToString() const;
};

template< class ExpectedT >
std::string ComparisonExpectation< ExpectedT >::ToString() const
{
    std::ostringstream oss;
    oss << "be ";
    switch( m_type )
    {
    case GreaterThan:
        oss << "greater than ";
        break;
    case GreaterThanEqual:
        oss << "greater than or equal to ";
        break;
    case LessThan:
        oss << "less than ";
        break;
    case LessThanEqual:
        oss << "less than or equal to ";
        break;
    }
    oss << ToStringTraits< ExpectedT >::Convert( m_expected );
    return oss.str();
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

//
// Factory function for BeApprox expectations
//
template< class ExpectedT >
impl::BeApproxExpectation< ExpectedT > BeApprox(
        ExpectedT expect, ExpectedT factor
        )
{
    // TODO: would be nice to check if ExpectedT is valid for
    //       a be approx expectation here.
    return impl::BeApproxExpectation< ExpectedT >( expect, factor );
}

//
// Factory functions for comparison expectations
//
template< class ExpectedT >
impl::ComparisonExpectation< ExpectedT > BeGreaterThan(
        ExpectedT expect
        )
{
    return impl::ComparisonExpectation< ExpectedT >(
            expect,
            impl::ComparisonExpectation< ExpectedT >::GreaterThan
            );
}

template< class ExpectedT >
impl::ComparisonExpectation< ExpectedT > BeGreaterThanOrEqual(
        ExpectedT expect
        )
{
    return impl::ComparisonExpectation< ExpectedT >(
            expect,
            impl::ComparisonExpectation< ExpectedT >::GreaterThanEqual
            );
}

template< class ExpectedT >
impl::ComparisonExpectation< ExpectedT > BeLessThan(
        ExpectedT expect
        )
{
    return impl::ComparisonExpectation< ExpectedT >(
            expect,
            impl::ComparisonExpectation< ExpectedT >::LessThan
            );
}

template< class ExpectedT >
impl::ComparisonExpectation< ExpectedT > BeLessThanOrEqual(
        ExpectedT expect
        )
{
    return impl::ComparisonExpectation< ExpectedT >(
            expect,
            impl::ComparisonExpectation< ExpectedT >::LessThanEqual
            );
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

//
// Traits specialization for BeApprox expectation
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::BeApproxExpectation< ExpectedT >
    >
{
    static bool Matches(
            const ActualT& actual,
            const expectations::impl::BeApproxExpectation<
                ExpectedT
                >& expectation
            )
    {
        using namespace std::rel_ops;
        ExpectedT min = expectation.m_expect - expectation.m_factor;
        ExpectedT max = expectation.m_expect + expectation.m_factor;
        return actual >= min && actual <= max;
        // TODO:
        //
        // Could probably switch this to use something like
        // std::less_equal etc.
        // Would allow for specializations again
        // This'll do for now though.
    }
};

//
// Traits specialization for Comparison expectation
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits<
    ActualT,
    expectations::impl::ComparisonExpectation< ExpectedT >
    >
{
    typedef expectations::impl::ComparisonExpectation<
        ExpectedT
        > CompExpectation;

    static bool Matches(
            const ActualT& actual,
            const CompExpectation& expectation
            )
    {
        using namespace std::rel_ops;
        using namespace expectations::impl;

        switch( expectation.m_type )
        {
            case CompExpectation::GreaterThan:
                return actual > expectation.m_expected;
            case CompExpectation::GreaterThanEqual:
                return actual >= expectation.m_expected;
            case CompExpectation::LessThan:
                return actual < expectation.m_expected;
            case CompExpectation::LessThanEqual:
                return actual <= expectation.m_expected;
            default:
                // This should never happen
                throw std::logic_error(
                        "Undefined comparison type in "
                        "cppshould::expectations::ComparisonExpectation"
                        );
        }
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_EXPECTATIONS_BE_H_

