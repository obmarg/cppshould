
#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include "mocks/callbacks.hpp"
#include <gtest/gtest.h>

using cppshould::expectations::Contain;
using cppshould::testing::MockCallbacks;
using cppshould::testing::SetupCallbacks;

//
// A fake expectation class for use by these tests
//
struct FakeExpectation : cppshould::expectations::Expectation< bool >
{
    FakeExpectation( bool succeed ) :
    succeed( succeed )
    {}

    bool succeed;
};

namespace cppshould {

template<>
struct ExpectationTraits< int, FakeExpectation >
{
    static bool Matches( int actual, FakeExpectation expectation )
    {
        return expectation.succeed;
    }
};

}   // namespace cppshould

TEST( Should, ShouldCallPassCallback )
{
    // Create test data
    std::vector< int > intList;
    intList.push_back( 1 );
    intList.push_back( 2 );

    // Create & setup mock
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    EXPECT_CALL(callbacks, Pass() )
        .Times(5);

    // Trigger successes
    intList SHOULD Contain(1);
    intList SHOULD Contain(2);
    intList SHOULD_NOT Contain(100);
    intList SHOULD_NOT Contain(-1);
    intList SHOULD_NOT Contain(1024);
}

TEST( Should, ShouldCallFailCallbackOnFatal )
{
    // Create test data
    std::vector< int > intList;
    intList.push_back( 1 );
    intList.push_back( 2 );

    // Create & setup mock
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    EXPECT_CALL(callbacks, Fail("FAIL", true) )
        .Times(5);

    intList MUST Contain(100);
    intList MUST Contain(200);
    intList MUST Contain(1024);
    intList MUST_NOT Contain(1);
    intList MUST_NOT Contain(2);
}

TEST( Should, ShouldCallFailCallbackOnNonFatal )
{
    // Create test data
    std::vector< int > intList;
    intList.push_back( 1 );
    intList.push_back( 2 );

    // Create & setup mock
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    EXPECT_CALL(callbacks, Fail("FAIL", false) )
        .Times(5);

    intList SHOULD Contain(100);
    intList SHOULD Contain(200);
    intList SHOULD Contain(1024);
    intList SHOULD_NOT Contain(1);
    intList SHOULD_NOT Contain(2);
}
