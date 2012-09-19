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
#include <sstream>

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
//!               Be sure to mention somewhere that references & cv
//!               should be stripped before calling it?
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
//!               Be sure to mention somewhere that references & cv
//!               should be stripped before calling it?
//!
//!     .. function:: static bool Check( const ActualT& actual, const ExpectationT& expectation )
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

    static bool Check( const ActualT& actual, const ExpectationT& expectation );
};

//!
//! .. class::  ToStringTraits
//!
//!     ToStringTraits is a template struct that is used to convert objects
//!     into a string before output.
//!
//!     By default it makes use the ostringstream ``operator<<`` and most 
//!     users should be able to just override that operator to perform 
//!     the conversions they want.
//!
//!     However in some cases the compiler might not be able to locate
//!     the correct operator<< (for example if providing it for a stdlib
//!     container and not defining it before this file is included) in
//!     which case providing a specialization of this class would be the
//!     best option.
//!
//!     .. todo:: Provide some examples
//!
//!     .. function:: static std::string Convert( TypeT input )
//!
//!         This function converts the input data into a string and returns it
//!
template< class TypeT >
struct ToStringTraits
{
    static std::string Convert( const TypeT& input )
    {
        std::ostringstream oss;
        oss << input;
        return oss.str();
    }
};

}   // namespace cppshould

// Include some specializations of ToStringTraits
#include "cppshould/impl/tostring.hpp"
// Include some specializations of EquivalenceTraits
#include "cppshould/impl/equivtraits.hpp"

#endif  // CPPSHOULD_TRAITS_H_
