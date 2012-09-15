//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_SHOULD_H_
#define CPPSHOULD_SHOULD_H_

#include "cppshould/traits.hpp"
#include "cppshould/shouldinfo.hpp"
#include <stdexcept>
#include <functional>

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
            const ActualT& actual, 
            ShouldInfo shouldInfo 
            ):
    m_actual( actual ),
    m_shouldInfo( shouldInfo )
    {}

    // Maybe this should be global?  Ideally don't want to pollute the global 
    // namespace though
    template< class MatcherT >
    void operator<<( MatcherT matcher );
    
private:
    const ActualT& m_actual;
    ShouldInfo m_shouldInfo;
};

// TODO: Should be possible to get this operator to return booleans
//       Therefore providing the option of just getting a bool
//       rather than throwing exceptions.
//
//       Look into it eventually
template< class ActualT >
template< class ExpectationT >
void Should< ActualT >::operator<<( ExpectationT expectation )
{
    // TODO: Get error string from somewhere (either expectation or traits)
    bool matches = ExpectationTraits< ActualT, ExpectationT >::Matches(
            m_actual,
            expectation
            );
    if ( matches && !m_shouldInfo.positive )
    {
        // FAILURE (matches but shouldn't)
        if ( ms_failCallback )
        {
            // TODO: Fill this in with error string
            ms_failCallback( "FAIL", m_shouldInfo.fatal );
        }
    }
    else if ( !matches && m_shouldInfo.positive )
    {
        // FAILURE (doesn't match but should)
        if ( ms_failCallback )
        {
            // TODO: Fill this in with error string
            ms_failCallback( "FAIL", m_shouldInfo.fatal );
        }
    }
    else
    {
        // SUCCESS (Could probably handle this as well)
        if ( ms_passCallback )
        {
            ms_passCallback();
        }
    }
}

}   // namespace cppshould

#endif  // CPPSHOULD_SHOULD_H_
