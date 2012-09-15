//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_SHOULD_H_
#define CPPSHOULD_SHOULD_H_

#include "cppshould/expectations/base.hpp"
#include "cppshould/traits.hpp"
#include "cppshould/shouldinfo.hpp"
#include <stdexcept>
#include <functional>
#include <sstream>

namespace cppshould {

typedef std::function< void (std::string, bool) > FailCallback;
typedef std::function< void () > PassCallback;

class ShouldBase
{
    friend class Callbacks;

protected:
    static FailCallback ms_failCallback;
    static PassCallback ms_passCallback;
};

//
// Class that holds the actual data and manages the comparison
//
template< class ActualT >
class Should : public ShouldBase
{
public:
    Should( 
            ActualT actual, 
            ShouldInfo shouldInfo 
            ):
    m_actual( actual ),
    m_shouldInfo( shouldInfo )
    {
        ActualT a = actual;
    }

    template< class ExpectationT >
    void operator<<( ExpectationT expectation );

private:
    std::string GetErrorMessage( 
            const expectations::BaseExpectation& expectation
            );
    
private:
    ActualT m_actual;
    ShouldInfo m_shouldInfo;
};

// TODO: May be possible to get this operator to return booleans
//       Therefore providing the option of just getting a bool
//       rather than throwing exceptions.
//
//       Look into it eventually
template< class ActualT >
template< class ExpectationT >
void Should< ActualT >::operator<<( ExpectationT expectation )
{
    bool matches = ExpectationTraits< ActualT, ExpectationT >::Matches(
            m_actual,
            expectation
            );
    if ( matches && !m_shouldInfo.positive )
    {
        // FAILURE (matches but shouldn't)
        if ( ms_failCallback )
        {
            ms_failCallback(
                    GetErrorMessage( expectation ), m_shouldInfo.fatal
                    );
        }
    }
    else if ( !matches && m_shouldInfo.positive )
    {
        // FAILURE (doesn't match but should)
        if ( ms_failCallback )
        {
            ms_failCallback( 
                    GetErrorMessage( expectation ), m_shouldInfo.fatal
                    );
        }
    }
    else
    {
        // SUCCESS 
        if ( ms_passCallback )
        {
            ms_passCallback();
        }
    }
}

//
// Handles getting error messages for failures
//
template< class ActualT >
std::string Should< ActualT >::GetErrorMessage( 
        const expectations::BaseExpectation& expectation 
        )
{
    // For now, lets just prepend actual to the error
    // message, and hope it works.
    // Also we'll ignore fatal vs non-fatal errors for now
    std::string actualString = ToStringTraits< ActualT >::Convert( m_actual );
    if ( m_shouldInfo.positive )
    {
        return actualString + expectation.MessageIfExpected();
    }
    else
    {
        return actualString + expectation.MessageIfUnexpected();
    }
}

}   // namespace cppshould

#endif  // CPPSHOULD_SHOULD_H_
