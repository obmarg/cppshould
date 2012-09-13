//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_MACROS_H_
#define CPPSHOULD_MACROS_H_

#include "shouldinfo.hpp"

#define SHOULD >> cppshould::ShouldInfo(__FILE__,__LINE__) <<
#define SHOULD_NOT >> cppshould::ShouldInfo(__FILE__,__LINE__,false) <<

// TODO: define the other macros as well

#endif // CPPSHOULD_MACROS_H_