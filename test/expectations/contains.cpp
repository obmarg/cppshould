#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include "mocks/callbacks.hpp"
#include <gtest/gtest.h>

using ::testing::InSequence;
using ::testing::_;

using cppshould::expectations::Contain;
using cppshould::testing::MockCallbacks;
using cppshould::testing::SetupCallbacks;


// Data for the contain class.
class ContainExpectation : public ::testing::Test
{
public:
    ContainExpectation()
    {
        intList.push_back( 1 );
        intList.push_back( 2 );
        intList.push_back( 3 );
    }

    std::vector< int > intList;
};

TEST_F( ContainExpectation, ShouldAcceptVariables )
{
    // Set things up
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(2);
        EXPECT_CALL( callbacks, Fail(_, false) )
            .Times(2);
    }

    // Passes
    intList SHOULD Contain(1);
    intList SHOULD_NOT Contain(10);
    
    // Fails
    intList SHOULD Contain(10); 
    intList SHOULD_NOT Contain(1);
}

TEST_F( ContainExpectation, ShouldAcceptStrings ) 
{
    // Set things up
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(2);
        EXPECT_CALL( callbacks, Fail(_, false) )
            .Times(1);
    }

    std::string str = "Hello There!";

    // Passes
    str SHOULD Contain('H');
    str SHOULD_NOT Contain('b');

    // Fails
    str SHOULD_NOT Contain('h');
}

TEST_F( ContainExpectation, ShouldPrintCorrectErrors )
{
    // Set things up
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Fail("Hello! should contain W", false) );
        EXPECT_CALL( callbacks, Fail("Hello! should not contain H", false) );
    }

    std::string str = "Hello!";

    str SHOULD Contain('W');
    str SHOULD_NOT Contain('H');
}
