//
// This file defines the ShouldBe class that
// allows comparisons via tha SHOULD_BE macro
//

#ifndef CPPSHOULD_SHOULDBE_H_
#define CPPSHOULD_SHOULDBE_H_

#include "cppshould/expectations/be.hpp"
#include "cppshould/should.hpp"

namespace cppshould {

//
// The ShouldBe class
//
template< class ActualT >
class ShouldBe
{
public:
    ShouldBe( ActualT actual, ShouldBeInfo shouldInfo ):
    m_should( actual, shouldInfo )
    {}

    template< class ExpectedT >
    void operator==( ExpectedT expected )
    {
        m_should << expectations::Be(expected);
    }

    template< class ExpectedT >
    void operator>=( ExpectedT expected )
    {
        m_should << expectations::BeGreaterThanOrEqual(expected);
    }

    template< class ExpectedT >
    void operator<=( ExpectedT expected )
    {
        m_should << expectations::BeLessThanOrEqual(expected);
    }

    template< class ExpectedT >
    void operator>( ExpectedT expected )
    {
        m_should << expectations::BeGreaterThan(expected);
    }

    template< class ExpectedT >
    void operator<( ExpectedT expected )
    {
        m_should << expectations::BeLessThan(expected);
    }

private:
    Should< ActualT > m_should;
};

}

#endif  // CPPSHOULD_SHOULDBE_H_
