//
// This file provides some default overrides of EquivalenceTraits
//

#ifndef CPPSHOULD_EQUIVTRAITS_H_
#define CPPSHOULD_EQUIVTRAITS_H_

#include "cppshould/traits.hpp"

namespace cppshould {

//////
//
// Specializations for char* (we don't want to be comparing pointers)
//
//////
template< class LeftT >
struct EquivalenceTraits< LeftT, char* >
{
    static bool Equivalent( const LeftT& lhs, const std::string& rhs )
    {
        return EquivalenceTraits< 
            LeftT, std::string 
            >::Equivalent( lhs, rhs );
    }
};

template< class RightT >
struct EquivalenceTraits< char*, RightT >
{
    static bool Equivalent( const std::string& lhs, const RightT& rhs )
    {
        return EquivalenceTraits< 
            std::string, RightT 
            >::Equivalent( lhs, rhs );
    }
};

template<>
struct EquivalenceTraits< char*, char* >
{
    static bool Equivalent( const std::string& lhs, const std::string& rhs )
    {
        return EquivalenceTraits< 
            std::string, std::string 
            >::Equivalent( lhs, rhs );
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_EQUIVTRAITS_H_
