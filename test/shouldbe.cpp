#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include "mocks/callbacks.hpp"
#include <gtest/gtest.h>

using ::testing::InSequence;
using ::testing::_;

using cppshould::testing::MockCallbacks;
using cppshould::testing::SetupCallbacks;

TEST( ShouldBe, EqualsShouldWorkWithNumbers )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(4);
        EXPECT_CALL( callbacks, Fail(_, false) );
    }

    // Passes
    1 SHOULD_BE == 1;
    2 SHOULD_BE == 2;
    3 SHOULD_BE == 3;
    4 SHOULD_NOT_BE == 1;

    // Fails
    5 SHOULD_BE == 4;
}

TEST( ShouldBe, EqualsShouldWorkWithStrings )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(5);
        EXPECT_CALL( callbacks, Fail(_, false) );
    }

    std::string str = "World";

    // Passes
    "Hello" SHOULD_BE == "Hello";
    str SHOULD_BE == "World";
    str SHOULD_BE == str;
    "Helow" SHOULD_NOT_BE == "World";
    "World" SHOULD_BE == str;

    // Fails
    str SHOULD_NOT_BE == "World";
}

TEST( ShouldBe, EqualsShouldWorkWithVectors )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(2);
        EXPECT_CALL( callbacks, Fail(_, false) );
    }

    // Create some data
    std::vector< int > vec1, vec2;
    vec1.push_back( 1 );
    vec1.push_back( 2 );
    vec2.push_back( 1 );
    vec2.push_back( 2 );

    // Passes
    vec1 SHOULD_BE == vec2;
    vec2 SHOULD_BE == vec1;

    // Fails
    vec1.push_back( 3 );
    vec1 SHOULD_BE == vec2;
}

TEST( ShouldBe, ComparisonsShouldWorkWithNumbers )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(13);
        EXPECT_CALL( callbacks, Fail(_, false) )
            .Times(8);
    }

    //
    // Passes
    //
    1 SHOULD_BE > 0;
    2 SHOULD_BE > 1.5;
    1.5 SHOULD_BE > 1;
    1.0 SHOULD_NOT_BE > 2;

    1 SHOULD_BE >= 1;
    2 SHOULD_BE >= 1.0;
    3.5 SHOULD_NOT_BE >= 4;

    1 SHOULD_BE < 2;
    2.5 SHOULD_BE < 3;
    2.5 SHOULD_NOT_BE < 2;
    1 SHOULD_NOT_BE < 0;

    1 SHOULD_BE <= 1;
    2 SHOULD_BE <= 100;

    //
    // Fails
    //
    1 SHOULD_BE > 2;
    4 SHOULD_NOT_BE > 3;

    1 SHOULD_BE >= 2;
    1 SHOULD_NOT_BE >= 1;

    1 SHOULD_BE < 0;
    0 SHOULD_NOT_BE < 1;

    1 SHOULD_BE <= 0;
    2 SHOULD_NOT_BE <= 2;
}

