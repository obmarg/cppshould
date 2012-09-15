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
    
    EXPECT_THROW(
            ( intList SHOULD Contain(10) ), 
            std::runtime_error
            );
    EXPECT_THROW(
            ( intList SHOULD_NOT Contain(1) ),
            std::runtime_error
            );
}

TEST_F( ContainExpectation, ShouldAcceptStrings ) 
{
    std::string str = "Hello There!";

    str SHOULD Contain('H');
    str SHOULD_NOT Contain('b');

    EXPECT_THROW(
            ( str SHOULD_NOT Contain('h') ),
            std::runtime_error
            );
}
