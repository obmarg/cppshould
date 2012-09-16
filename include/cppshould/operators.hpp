//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_OPERATORS_H_
#define CPPSHOULD_OPERATORS_H_

#include "cppshould/shouldinfo.hpp"
#include "cppshould/should.hpp"
#include "cppshould/shouldbe.hpp"

namespace cppshould {

//
// Initial operator >> that creates the Should
//
template< class ActualT >
Should<ActualT> operator>> (
        ActualT actual, ShouldInfo shouldInfo
        ) 
{
    return cppshould::Should<ActualT>(actual, shouldInfo);
}

//
// Initial operator >> that creates the Should
//
template< class ActualT >
ShouldBe<ActualT> operator>> (
        ActualT actual, ShouldBeInfo shouldInfo
        ) 
{
    return cppshould::ShouldBe<ActualT>(actual, shouldInfo);
}

}   // namespace cppshould

#endif  // CPPSHOULD_OPERATORS_H_
