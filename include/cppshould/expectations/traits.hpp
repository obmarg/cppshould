//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_EXPECTATIONS_TRAITS_H
#define CPPSHOULD_EXPECTATIONS_TRAITS_H

#include <stdexcept>

namespace cppshould {
namespace expectations {

//!
//! .. class::  template<ActualT, ExpectationT> struct EquivalenceTraits
//!     
//!     EquivalenceTraits is a template struct that is used to define the
//!     how expectation checks are actually carried out.
//!
//!     Most users should not need to know anything about this class unless
//!     they are creating their own custom expectation types.
//!
//!     .. todo:: Provide some details and examples of specializing this class
//!
//!     .. todo:: Define the Check function in here also
//!
template< class ActualT, class ExpectationT >
struct ExpectationTraits
{
    bool Check( ActualT input, typename ExpectationT::ExpectedT actual )
    {
        // TODO: Figure out a way of including types in this static_assert
        
        // TODO: Re-implement this static assert.  At them moment it always fails
        //static_assert( false, "Expectation is not compatible with input type" );

        // This isn't the best error message...
        throw std::logic_error( "Undefined expectation traits" );
    }
};

}   // namespace expectations
}   // namespace cppshould

#endif  //  CPPSHOULD_EXPECTATIONS_TRAITS_H
