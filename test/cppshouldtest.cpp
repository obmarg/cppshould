
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
