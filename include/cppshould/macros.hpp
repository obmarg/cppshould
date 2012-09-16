//!
//! CppShould Macros
//! =================
//!
//! These are the various macros that make up the CppShould DSL
//!
//! .. todo:: Break this file up into (at least) 2 sections with
//!           headers etc.
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
//!
#define SHOULD >> cppshould::ShouldInfo(__FILE__,__LINE__,true,false) <<

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
//!
#define SHOULD_NOT >> cppshould::ShouldInfo(__FILE__,__LINE__,false,false) <<

//! .. c:macro:: MUST
//!
//!     This macro is used to define an expectation that must be met.
//!     The value that should be checked against the expectation should
//!     be on the left hand side of the macro, and the expectation itself
//!     should be on the right.
//!
//!     If the expectation is not met, then a fatal error will occur.
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
//!         intList MUST Contain(2);  // Will Pass
//!         intList MUST Contain(1);  // Will Pass
//!         intList MUST Contain(4);  // Will Fail
#define MUST >> cppshould::ShouldInfo(__FILE__,__LINE__,true,true) <<

//! .. c:macro:: MUST_NOT
//!
//!     This macro is used to define an expectation that must not be met.
//!     The value that should be checked against the expectation should
//!     be on the left hand side of the macro, and the expectation itself
//!     should be on the right.
//!
//!     If the expectation is met, then a fatal error will occur.
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
//!         intList MUST_NOT Contain(4);  // Will Pass
//!         intList MUST_NOT Contain(5);  // Will Pass
//!         intList MUST_NOT Contain(1);  // Will Fail
//!
#define MUST_NOT >> cppshould::ShouldInfo(__FILE__,__LINE__,false,true) <<

//! .. c:macro:: SHOULD_BE
//!
//!     This macro is used to define a comparison expectation that
//!     should be met.  The value that should be checked should be
//!     on the left hand side of the macro, and the comparison itself
//!     should be on the right hand side.
//!
//!     If the comparison returns false, then a non-fatal error will occur.
//!     How this is handled depends on the current unit testing framework
//!     that is setup.
//!
//!     .. todo:: Details on this being shorthand for Be matchers etc.
//!               Also some information on the limitations would be good
//!
//!     .. todo:: Maybe document how some compilers don't neccesarily
//!               like not using the results of comparisons
//!
//!     For example::
//!
//!         3 SHOULD_BE == 3;  // Will Pass
//!         2 SHOULD_BE < 3;   // Will Pass
//!         4 SHOULD_BE > 3;   // Will Pass
//!         4 SHOULD_BE <= 3;  // Will Fail
//!         5 SHOULD_BE >= 3;  // Will Fail
//!
#define SHOULD_BE >> cppshould::ShouldBeInfo(__FILE__,__LINE__,true,false)

//! .. c:macro:: SHOULD_NOT_BE
//!
//!     This macro is used to define a comparison expectation that
//!     should not be met.  The value that should be checked should be
//!     on the left hand side of the macro, and the comparison itself
//!     should be on the right hand side.
//!
//!     If the comparison returns true, then a non-fatal error will occur.
//!     How this is handled depends on the current unit testing framework
//!     that is setup.
//!
//!     .. todo:: Details on this being shorthand for Be matchers etc.
//!               Also some information on the limitations would be good
//!
//!     .. todo:: Maybe document how some compilers don't neccesarily
//!               like not using the results of comparisons
//!
//!     For example::
//!
//!         3 SHOULD_NOT_BE == 3;  // Will Fail
//!         2 SHOULD_NOT_BE < 3;   // Will Fail
//!         4 SHOULD_NOT_BE > 3;   // Will Fail
//!         4 SHOULD_NOT_BE <= 3;  // Will Pass
//!         5 SHOULD_NOT_BE >= 3;  // Will Pass
//!
#define SHOULD_NOT_BE >> cppshould::ShouldBeInfo(__FILE__,__LINE__,false,false)

//! .. c:macro:: MUST_BE
//!
//!     This macro is used to define a comparison expectation that
//!     must be met.  The value that should be checked should be
//!     on the left hand side of the macro, and the comparison itself
//!     should be on the right hand side.
//!
//!     If the comparison returns false, then a fatal error will occur.
//!     How this is handled depends on the current unit testing framework
//!     that is setup.
//!
//!     .. todo:: Details on this being shorthand for Be matchers etc.
//!               Also some information on the limitations would be good
//!
//!     .. todo:: Maybe document how some compilers don't neccesarily
//!               like not using the results of comparisons
//!
//!     For example::
//!
//!         3 MUST_BE == 3;  // Will Pass
//!         2 MUST_BE < 3;   // Will Pass
//!         4 MUST_BE > 3;   // Will Pass
//!         4 MUST_BE <= 3;  // Will Fail
//!         5 MUST_BE >= 3;  // Will Fail
//!
#define MUST_BE >> cppshould::ShouldBeInfo(__FILE__,__LINE__,true,true)

//! .. c:macro:: MUST_NOT_BE
//!
//!     This macro is used to define a comparison expectation that
//!     must not be met.  The value that should be checked should be
//!     on the left hand side of the macro, and the comparison itself
//!     should be on the right hand side.
//!
//!     If the comparison returns true, then a fatal error will occur.
//!     How this is handled depends on the current unit testing framework
//!     that is setup.
//!
//!     .. todo:: Details on this being shorthand for Be matchers etc.
//!               Also some information on the limitations would be good
//!
//!     .. todo:: Maybe document how some compilers don't neccesarily
//!               like not using the results of comparisons
//!
//!     For example::
//!
//!         3 MUST_NOT_BE == 3;  // Will Fail
//!         2 MUST_NOT_BE < 3;   // Will Fail
//!         4 MUST_NOT_BE > 3;   // Will Fail
//!         4 MUST_NOT_BE <= 3;  // Will Pass
//!         5 MUST_NOT_BE >= 3;  // Will Pass
//!
#define MUST_NOT_BE >> cppshould::ShouldBeInfo(__FILE__,__LINE__,false,true)

#endif // CPPSHOULD_MACROS_H_
