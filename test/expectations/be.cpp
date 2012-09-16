#include "cppshould/expectations/be.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include "mocks/callbacks.hpp"
#include <gtest/gtest.h>

using ::testing::InSequence;
using ::testing::_;

using cppshould::expectations::Be;
using cppshould::expectations::BeApprox;
using cppshould::expectations::BeGreaterThan;
using cppshould::expectations::BeGreaterThanOrEqual;
using cppshould::expectations::BeLessThan;
using cppshould::expectations::BeLessThanOrEqual;
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

TEST( BeExpectation, ShouldOutputCorrectErrors )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( 
                callbacks, 
                Fail("Hello should be equal to World", false) 
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("Hello should not be equal to Hello", false) 
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("1 should be equal to 2", false) 
                );
    }

    "Hello" SHOULD Be("World");
    "Hello" SHOULD_NOT Be("Hello");
    1 SHOULD Be(2);
}

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

TEST( BeApproxExpectation, ShouldOutputCorrectErrors )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( 
                callbacks, 
                Fail(
                    "1 should be approximately equal to 3 "
                    "(by a factor of 1)", false
                    ) );
    }

    // Don't bother testing floating points since they
    // can give unpredictable output
    1 SHOULD BeApprox(3, 1);
}

TEST( ComparisonExpectations, ShouldWorkWithNumbers )
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
    1 SHOULD BeGreaterThan(0);
    2 SHOULD BeGreaterThan(1.5);
    1.5 SHOULD BeGreaterThan(1);
    1.0 SHOULD_NOT BeGreaterThan(2);

    1 SHOULD BeGreaterThanOrEqual(1);
    2 SHOULD BeGreaterThanOrEqual(1.0);
    3.5 SHOULD_NOT BeGreaterThanOrEqual(4);

    1 SHOULD BeLessThan(2);
    2.5 SHOULD BeLessThan(3);
    2.5 SHOULD_NOT BeLessThan(2);
    1 SHOULD_NOT BeLessThan(0);

    1 SHOULD BeLessThanOrEqual(1);
    2 SHOULD BeLessThanOrEqual(100);

    //
    // Fails
    //
    1 SHOULD BeGreaterThan(2);
    4 SHOULD_NOT BeGreaterThan(3);

    1 SHOULD BeGreaterThanOrEqual(2);
    1 SHOULD_NOT BeGreaterThanOrEqual(1);

    1 SHOULD BeLessThan(0);
    0 SHOULD_NOT BeLessThan(1);

    1 SHOULD BeLessThanOrEqual(0);
    2 SHOULD_NOT BeLessThanOrEqual(2);
}

TEST( ComparisonExpectations, ShouldOutputCorrectErrors )
{
    MockCallbacks callbacks;
    SetupCallbacks( callbacks );

    // Set expectations
    {
        InSequence dummy;
        EXPECT_CALL( 
                callbacks, 
                Fail("1 should be greater than 2", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("2 should not be greater than 1", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("3 should be greater than or equal to 4", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("5 should not be greater than or equal to 4", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("2 should be less than 1", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("1 should not be less than 2", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("2 should be less than or equal to 1", false)
                );
        EXPECT_CALL( 
                callbacks, 
                Fail("1 should not be less than or equal to 2", false)
                );
    }

    1 SHOULD BeGreaterThan(2);
    2 SHOULD_NOT BeGreaterThan(1);

    3 SHOULD BeGreaterThanOrEqual(4);
    5 SHOULD_NOT BeGreaterThanOrEqual(4);

    2 SHOULD BeLessThan(1);
    1 SHOULD_NOT BeLessThan(2);

    2 SHOULD BeLessThanOrEqual(1);
    1 SHOULD_NOT BeLessThanOrEqual(2);
}
