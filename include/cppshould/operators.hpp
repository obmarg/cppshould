//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_OPERATORS_H_
#define CPPSHOULD_OPERATORS_H_

#include "shouldinfo.hpp"
#include "should.hpp"

// TODO: Ideally i'd like to namespace these.
//       However, i'm not sure if they'd actually work if I did.
//       Figure that out at some point

//
// Initial operator << that creates the Should
//
template< class ActualT >
cppshould::Should<ActualT> operator>> (
        ActualT actual, cppshould::ShouldInfo shouldInfo
        ) 
{
    return cppshould::Should<ActualT>(actual, shouldInfo);
}

#endif  // CPPSHOULD_OPERATORS_H_
