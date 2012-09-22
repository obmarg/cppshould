//
// This file defines some utilities used throughout cppshould
//

#ifndef CPPSHOULD_UTILS_H_
#define CPPSHOULD_UTILS_H_

#include <type_traits>

namespace cppshould {

template< class T >
struct remove_refcv
{
    typedef typename std::remove_reference< 
        typename std::remove_cv< T >::type 
        >::type type;
};

}   // namespace cppshould

#endif  // CPPSHOULD_UTILS_H_
