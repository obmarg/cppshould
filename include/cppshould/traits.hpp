//!
//! Customising Behaviour With Traits
//! ==================================
//!
//! CppShould contains several different traits templates to allow users to customise
//! the behaviour of CppShould and it's expectations, or to provide entirely new
//! expectations.
//!
//! This file details the various traits templates provided by CppShould along
//! with details on how to override them.
//!
//! .. todo: A bit more info might be good here
//!
//! .. namespace:: cppshould
//!

#ifndef CPPSHOULD_TRAITS_H_
#define CPPSHOULD_TRAITS_H_

#include <stdexcept>

namespace cppshould {

//!
//! .. class::  EquivalenceTraits
//!
//!     EquivalenceTraits is a template struct that is used throughout CppShould
//!     in place of ``operator==``.
//!
//!     Users should specialise this class if they wish to provide custom
//!     comparisons between types without having to override ``operator==``
//!     globally or provide class member operators.
//!
//!     .. todo:: Provide some examples of overriding this function?
//!
//!     .. function:: static bool Equivalent( const LeftT& lhs, const RightT& rhs )
//!
//!         This function actually performs the comparisons, and should be provided
//!         by any specializations of EquivalenceTraits.
//!
//!         By default it just uses ``operator==``
//!
template< class LeftT, class RightT >
struct EquivalenceTraits
{
    static bool Equivalent( const LeftT& lhs, const RightT& rhs )
    {
        return lhs == rhs;
    }
};

//!
//! .. class::  EquivalenceTraits
//!
//!     EquivalenceTraits is a template struct that is used to define the
//!     how expectation checks are actually carried out.
//!
//!     Most users should not need to know anything about this class unless
//!     they are creating their own custom expectation types.
//!
//!     .. todo:: Provide some details and examples of specializing this class
//!
//!     .. function:: static bool Check( ActualT actual, ExpectationT expectation )
//!
//!         This function is used to actually check expectations.  It should
//!         return true if ``actual`` meets ``expectation``
//!
template< class ActualT, class ExpectationT, class Enable=void >
struct ExpectationTraits
{
    // This static assert should always fail.
    // It's only purpose is to ensure this generalised version is never
    // used
    static_assert(
            std::is_same<ActualT, ExpectationT>::value,
            "This Expectation does not support checking against this data type"
            );

    static bool Check( ActualT actual, ExpectationT expectation );
};

}   // namespace cppshould

#endif  // CPPSHOULD_TRAITS_H_
