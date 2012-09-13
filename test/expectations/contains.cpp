#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include <gtest/gtest.h>

using cppshould::expectations::Contain;

std::vector< int > intList = { 1, 2, 3 };

TEST( ContainExpectation, ShouldAcceptVariables )
{
    intList SHOULD Contain(1);
    intList SHOULD_NOT Contain(10);
    
    // TODO: Replace these with assert_throws or whatever
    try
    {
        intList SHOULD Contain(10);
        ASSERT_TRUE( false );
    }
    catch( std::runtime_error& )
    {
    }
    try
    {
        intList SHOULD_NOT Contain(1);
        ASSERT_TRUE( false );
    }
    catch( std::runtime_error& )
    {
    }
}

TEST( ContainExpectation, ShouldAcceptInitializerLists ) 
{
    // TODO: Implement me
    ASSERT_TRUE( false );
}

TEST( ContainExpectation, ShouldAcceptRanges ) 
{
    // TODO: Implement me
    ASSERT_TRUE( false );
}
