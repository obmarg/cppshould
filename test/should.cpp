#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include "mocks/callbacks.hpp"
#include <gtest/gtest.h>

using ::testing::InSequence;

using cppshould::expectations::Contain;
using cppshould::testing::MockCallbacks;
using cppshould::testing::SetupCallbacks;

//
// A fake expectation class for use by these tests
//
class FakeExpectation : public cppshould::expectations::Expectation< bool >
{
public:
    FakeExpectation( bool succeed ) :
    succeed( succeed )
    {}

    std::string MessageIfExpected() const
    {
        return " SHOULD-FAIL";
    }

    std::string MessageIfUnexpected() const
    {
        return " SHOULD_NOT-FAIL";
    }

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
    // Create & setup mock
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    EXPECT_CALL(callbacks, Pass() )
        .Times(5);

    // Trigger successes
    1 SHOULD FakeExpectation(true);
    2 SHOULD FakeExpectation(true);
    3 SHOULD_NOT FakeExpectation(false);
    4 SHOULD_NOT FakeExpectation(false);
    5 SHOULD_NOT FakeExpectation(false);
}

TEST( Should, ShouldCallFailCallbackOnFatal )
{
    // Create & setup mock
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL(callbacks, Fail("1 SHOULD-FAIL", true) )
            .Times(3);
        EXPECT_CALL(callbacks, Fail("1 SHOULD_NOT-FAIL", true) )
            .Times(2);
    }

    1 MUST FakeExpectation(false);
    1 MUST FakeExpectation(false);
    1 MUST FakeExpectation(false);
    1 MUST_NOT FakeExpectation(true);
    1 MUST_NOT FakeExpectation(true);
}

TEST( Should, ShouldCallFailCallbackOnNonFatal )
{
    // Create & setup mock
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL(callbacks, Fail("1 SHOULD-FAIL", false) )
            .Times(3);
        EXPECT_CALL(callbacks, Fail("1 SHOULD_NOT-FAIL", false) )
            .Times(2);
    }

    int x = 1;

    x SHOULD FakeExpectation(false);
    x SHOULD FakeExpectation(false);
    x SHOULD FakeExpectation(false);
    x SHOULD_NOT FakeExpectation(true);
    x SHOULD_NOT FakeExpectation(true);
}
