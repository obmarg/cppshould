//
// This file defines a number of specializations for ToStringTraits
//

#ifndef CPPSHOULD_TOSTRING_H_
#define CPPSHOULD_TOSTRING_H_

#include <sstream>
#include <vector>

namespace cppshould {

//
// A specialization for vectors
//
template< class TypeT >
struct ToStringTraits< std::vector< TypeT > >
{
    typedef std::vector< TypeT > VecT;

    static std::string Convert( const VecT& input )
    {
        std::ostringstream oss;
        oss << "[ ";
        bool first = true;
        for( typename VecT::const_iterator it = std::begin(input); 
                it != std::end(input); ++it 
                )
        {
            // I miss boost::join
            if ( first )
            {
                first = false;
            }
            else
            {
                oss << ", ";
            }
            oss << *it;
        }
        oss << " ]";
        return oss.str();
    }
};

}   // namespace cppshould

#endif  // CPPSHOULD_TOSTRING_H_
