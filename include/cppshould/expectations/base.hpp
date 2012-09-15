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
//!     .. function:: std::string MessageIfExpected()
//!         
//!         This function will be called in the case that an expectation
//!         was not met but was expected to be met.
//!
//!         It should return a string containing a placeholder for the
//!         actual value used in checking the expectation.
//!
//!     .. function:: std::string MessageIfUnexpected()
//!         
//!         This function will be called in the case that an expectation
//!         was met but was not expected to be met.
//!
//!         It should return a string containing a placeholder for the
//!         actual value used in checking the expectation.
//!
class BaseExpectation
{
public:
    virtual ~BaseExpectation() {};

    virtual std::string MessageIfExpected() const=0;
    virtual std::string MessageIfUnexpected() const=0;
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
