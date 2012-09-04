//
// This file defines the Contain expectation
//

#ifndef CPPSHOULD_SHOULDINFO_H_
#define CPPSHOULD_SHOULDINFO_H_

#include <string>

namespace cppshould {

//
// Class for storing SHOULD info
//
struct ShouldInfo
{
    ShouldInfo( 
            std::string fileName, 
            int lineNum, 
            bool should=true
            ) :
    fileName( fileName ),
    lineNum( lineNum ),
    should( should )
    {}

    std::string fileName;
    int lineNum;
    bool should;
};


}   // namespace cppshould

#endif  // CPPSHOULD_SHOULDINFO_H_
