//! 
//! CppShould Macros
//! =================
//! 
//! These are the various macros that make up the CppShould DSL
//!

#ifndef CPPSHOULD_MACROS_H_
#define CPPSHOULD_MACROS_H_

#include "shouldinfo.hpp"

//! .. c:macro:: SHOULD
//!
//!     This macro is used to define an expectation that should be met.  
//!     The value that should be checked against the expectation should
//!     be on the left hand side of the macro, and the expectation itself
//!     should be on the right.
//!
//!     If the expectation is not met, then a non-fatal error will occur.
//!     How this is handled depends on the current unit testing framework
//!     that is setup.
//!
//!     See the :doc:`/expectations` for information on the 
//!     different expectations that can be used
//!
//!     For example::
//!
//!         std::vector< int > intList = { 1, 2, 3 };
//!
//!         intList SHOULD Contain(2);  // Will Pass
//!         intList SHOULD Contain(1);  // Will Pass
//!         intList SHOULD Contain(4);  // Will Fail
#define SHOULD >> cppshould::ShouldInfo(__FILE__,__LINE__) <<

//! .. c:macro:: SHOULD_NOT
//!
//!     This macro is used to define an expectation that should not be met.  
//!     The value that should be checked against the expectation should
//!     be on the left hand side of the macro, and the expectation itself
//!     should be on the right.
//!
//!     If the expectation is met, then a non-fatal error will occur.
//!     How this is handled depends on the current unit testing framework
//!     that is setup.
//!
//!     See the :doc:`/expectations` for information on the 
//!     different expectations that can be used
//!
//!     For example::
//!
//!         std::vector< int > intList = { 1, 2, 3 };
//!
//!         intList SHOULD_NOT Contain(4);  // Will Pass
//!         intList SHOULD_NOT Contain(5);  // Will Pass
//!         intList SHOULD_NOT Contain(1);  // Will Fail
#define SHOULD_NOT >> cppshould::ShouldInfo(__FILE__,__LINE__,false) <<

// TODO: define the other macros as well

#endif // CPPSHOULD_MACROS_H_
