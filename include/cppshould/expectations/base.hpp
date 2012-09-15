//!
//! Expectations Base Classes
//! ==========================
//!
//! These classes define the base classes that should be overridden when
//! definining new expectations.
//!
//! .. namespace:: cppshoud::expectations

#ifndef CPPSHOULD_EXPECTATIONS_BASE_H_
#define CPPSHOULD_EXPECTATIONS_BASE_H_

#include <string>
#include <sstream>

namespace cppshould {
namespace expectations {

//!
//! .. class:: BaseExpectation
//!
//!     This is the absolute base class for expectatons, and defines all
//!     common expectation functionality that does not depend on the
//!     expectation type.
//!
//!     Users should not have to directly inherit from or interact with
//!     this class, but they may have to override some of it's functions
//!     if definining new expectations.
//!
//!     .. todo:: Either detail placeholders here or link to details
//!
//!     .. function:: std::string ErrorMessage( bool expected, bool fatal )
//!         
//!         This function will be called in the case of an expectation 
//!         failure.
//!
//!         The default implementation of this function will defer to 
//!         the func:`ToString` to get the expected text and will prepend
//!         should/must (not) on the front.
//!
//!         ``expected`` defines whether it was a SHOULD failure or a 
//!         SHOULD_NOT failure (true means SHOULD, false means SHOULD_NOT)
//!
//!         ``fatal`` defines whether it was a SHOULD or MUST failure
//!
//!         It should return a string containing a placeholder for the
//!         actual value used in checking the expectation. Currently this
//!         placeholder isn't defined, and the actual value will just
//!         be prepended.
//!
//!     .. function:: std::string ToString()
//!
//!         This function should be defined by any child classes that
//!         don't intend to provide their own implementation of 
//!         func:`ErrorMessage`.
//!
//!         It should return a string representation of the expectation
//!         which will be appended on the end of a failure description
//!         sentence.
//!
class BaseExpectation
{
public:
    virtual ~BaseExpectation() {};

    virtual std::string ErrorMessage( bool expected, bool fatal ) const
    {
        std::ostringstream oss;
        if ( fatal )
        {
            oss << "must ";
        }
        else
        {
            oss << "should ";
        }
        if( !expected )
        {
            oss << "not ";
        }
        oss << ToString();
        return oss.str();
    }

protected:
    virtual std::string ToString() const
    {
        throw std::logic_error( 
                "ToString was called on an expectation that has not provided " 
                "an implementation"
                );
    }

};

//!
//! .. class:: Expectation
//!
//!     This template class should be used as the base class for all
//!     expectations.
//!
template< class ExpectT >
class Expectation : public BaseExpectation
{
public:
    typedef ExpectT ExpectedT;
};

}   // namespace expectations
}   // namespace cppshould 

#endif  // CPPSHOULD_EXPECTATIONS_BASE_H_
