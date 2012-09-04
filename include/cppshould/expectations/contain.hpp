//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_EXPECTATIONS_CONTAIN_H_
#define CPPSHOULD_EXPECTATIONS_CONTAIN_H_

#include "traits.hpp"
#include "base.hpp"

namespace cppshould {
namespace expectations {
namespace impl {

//
// Class that implements Contain() expectations
//
template< class ExpectedT >
class ContainExpectation : public Expectation< ExpectedT >
{
public:
    // TODO: (R-Value) reference this?
    ContainExpectation( ExpectedT expect ) :
    m_expect( expect )
    {}

    ExpectedT m_expect;
};

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

//
// Traits specialization for expectations
//
template< class ActualT, class ExpectedT >
struct ExpectationTraits< ActualT, impl::ContainExpectation< ExpectedT > >
{
    // Does actual match our expectations?
    static bool Matches(
            ActualT actual, 
            impl::ContainExpectation< ExpectedT > expectation
            )
    {
        // TODO: Make this better
        for ( auto it = std::begin(actual); it != std::end(actual); ++it )
        {
            // TODO: Probably want to use traits for comparison rather than ==
            if ( *it == expectation.m_expect )
            {
                return true;
            }
        }
        return false;
    }
};
    
}   // namespace expectations
}   // namespace cppshould

#endif  // CPPSHOULD_EXPECTATIONS_CONTAIN_H_
