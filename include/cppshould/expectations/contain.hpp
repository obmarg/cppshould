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
//!     Meant to be used with :c:macro:`SHOULD` and :c:macro:`SHOULD_NOT` For example::
//!
//!         intList SHOULD Contain(1);      // Will pass
//!         intList SHOULD Contain(4);      // Will fail
//!         intList SHOULD_NOT Contain(4);  // Will pass
//!         intList SHOULD_NOT Contain(1);  // Will fail
//!
//!     Contain should also work with initializer lists, or other range-like containers::
//!
//!         std::vector<int> intList = { 1, 2, 3 }
//!         intList SHOULD Contain({ 1, 2 });   // Will pass
//!         intList SHOULD Contain({ 1, 3 });   // Will fail
//!         
//!         std::string str = "Hello!";
//!         str SHOULD Contain("Hello");        // Will pass
//!         str SHOULD_NOT Contain("World");    // Will pass
//!
//!     .. todo:: Once the ContainsAll, ContainsAny etc. are defined, link to them

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
