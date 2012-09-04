//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_EXPECTATIONS_TRAITS_H
#define CPPSHOULD_EXPECTATIONS_TRAITS_H

namespace cppshould {
namespace expectations {

//
// Traits class for expectations
//
template< class ActualT, class ExpectationT >
struct ExpectationTraits
{
    bool Check( ActualT input, typename ExpectationT::ExpectedT actual )
    {
        // TODO: Figure out a way of including types in this static_assert
        
        // TODO: Re-implement this static assert.  At them moment it always fails
        //static_assert( false, "Expectation is not compatible with input type" );
    }
};

}   // namespace expectations
}   // namespace cppshould

#endif  //  CPPSHOULD_EXPECTATIONS_TRAITS_H
