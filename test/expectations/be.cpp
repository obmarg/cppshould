#include "cppshould/expectations/be.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include "mocks/callbacks.hpp"
#include <gtest/gtest.h>

using ::testing::InSequence;
using ::testing::_;

using cppshould::expectations::Be;
using cppshould::expectations::BeApprox;
using cppshould::testing::MockCallbacks;
using cppshould::testing::SetupCallbacks;

TEST( BeExpectation, ShouldWorkWithNumbers )
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
    1 SHOULD Be(1);
    2 SHOULD Be(2);
    3 SHOULD Be(3);
    4 SHOULD_NOT Be(1);

    // Fails
    5 SHOULD Be(4);
}

TEST( BeExpectation, ShouldWorkWithStrings )
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
    "Hello" SHOULD Be("Hello");
    str SHOULD Be("World");
    str SHOULD Be(str);
    "Helow" SHOULD_NOT Be("World");
    "World" SHOULD Be(str);

    // Fails
    str SHOULD_NOT Be("World");
}

TEST( BeExpectation, ShouldWorkWithVectors )
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
    vec1 SHOULD Be(vec2);
    vec2 SHOULD Be(vec1);

    // Fails
    vec1.push_back( 3 );
    vec1 SHOULD Be(vec2);
}

// TODO: add error message tests

// TODO: Add a test with a custom object ?
//

TEST( BeApproxExpectation, ShouldWorkWithIntegers )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(5);
        EXPECT_CALL( callbacks, Fail(_, false) )
            .Times(2);
    }

    1 SHOULD BeApprox(1, 1);
    2 SHOULD BeApprox(1, 1);
    5 SHOULD BeApprox(7, 2);
    1 SHOULD BeApprox(2, 1);
    5 SHOULD_NOT BeApprox(1, 3);

    1 SHOULD_NOT BeApprox(2, 1);
    1 SHOULD BeApprox(2, 0);
}

TEST( BeApproxExpectation, ShouldWorkWithFloats )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( callbacks, Pass() )
            .Times(5);
        EXPECT_CALL( callbacks, Fail(_, false) )
            .Times(2);
    }

    // Passes
    0.9 SHOULD BeApprox(1.0, 0.1);
    2.5 SHOULD BeApprox(2.0, 1.0);
    5.0 SHOULD BeApprox(7.0, 2.0);
    1.0 SHOULD BeApprox(2.0, 1.0);
    .05 SHOULD_NOT BeApprox(1.0, 0.5);

    // Fails
    1.0 SHOULD_NOT BeApprox(2.0, 1.0);
    1.0 SHOULD BeApprox(2.0, 0.0);
}

TEST( BeApproxExpectation, ShouldDoInterTypeComparisons )
{
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
    1 SHOULD BeApprox(1.0, 0.1);
    2.5 SHOULD BeApprox(2, 1);

    // Fails
    1 SHOULD_NOT BeApprox(1.2, 0.5);
    3.1 SHOULD BeApprox(2, 1);
}

// TODO: Add error message tests
