#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include <gtest/gtest.h>

using cppshould::expectations::Contain;

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
    intList SHOULD Contain(1);
    intList SHOULD_NOT Contain(10);
    
    // TODO: Replace these with assert_throws or whatever
    EXPECT_THROW(
            ( intList SHOULD Contain(10) ), 
            std::runtime_error
            );
    try
    {
        intList SHOULD_NOT Contain(1);
        ASSERT_TRUE( false );
    }
    catch( std::runtime_error& )
    {
    }
}

TEST_F( ContainExpectation, ShouldAcceptStrings ) 
{
    std::string str = "Hello There!";

    str SHOULD Contain('H');
    str SHOULD_NOT Contain('h');
}
