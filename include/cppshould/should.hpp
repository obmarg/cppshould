//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_SHOULD_H_
#define CPPSHOULD_SHOULD_H_

#include "shouldinfo.hpp"

namespace cppshould {

//
// Class that holds the actual data and manages the comparison
//
template< class ActualT >
class Should
{
public:
    Should( 
            const ActualT& comp, 
            ShouldInfo shouldInfo 
            ):
    m_comp( comp ),
    m_shouldInfo( shouldInfo )
    {}

    // Maybe this should be global?  Ideally don't want to pollute the global 
    // namespace though
    template< class MatcherT >
    void operator<<( MatcherT matcher );
    
private:
    const ActualT& m_comp;
    ShouldInfo m_shouldInfo;
};

template< class ActualT >
template< class MatcherT >
void Should< ActualT >::template operator<<( MatcherT matcher )
{
    // TODO: For now, do nothing.  At some point call through to matcher traits 
    //       though
}

}   // namespace cppshould

#endif  // CPPSHOULD_SHOULD_H_
