//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_SHOULD_H_
#define CPPSHOULD_SHOULD_H_

#include "shouldinfo.hpp"
#include <stdexcept>

namespace cppshould {

//
// Class that holds the actual data and manages the comparison
//
template< class ActualT >
class Should
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
void Should< ActualT >::template operator<<( ExpectationT expectation )
{
    using expectations::ExpectationTraits;

    bool matches = ExpectationTraits< ActualT, ExpectationT >::Matches(
            m_actual,
            expectation
            );
    if ( matches && m_shouldInfo.shouldNot )
    {
        // FAILURE 
        //
        // For now, lets just throw an exception.
        // In the future this should probably call into some
        // generic(ish) code.
        throw std::runtime_error( "FAIL" );
    }
    else if ( !matches && !m_shouldInfo.shouldNot )
    {
        // FAILURE 
        //
        // For now, lets just throw an exception.
        // In the future this should probably call into some
        // generic(ish) code.
        throw std::runtime_error( "FAIL" );
    }
    else
    {
        // SUCCESS (Could probably handle this as well)
    }
}

}   // namespace cppshould

#endif  // CPPSHOULD_SHOULD_H_
