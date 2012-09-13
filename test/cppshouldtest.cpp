
#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

using namespace cppshould::expectations;

int main( int argc, char** argv )
{
    testing::InitGoogleTest( &argc, argv );
    return RUN_ALL_TESTS();
}

TEST(ContainTest,BasicTest)
{
    std::vector< int > intList = { 1, 2, 3 };
    intList SHOULD Contain(1);
    intList >> cppshould::ShouldInfo(__FILE__, __LINE__) << Contain(1);
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
