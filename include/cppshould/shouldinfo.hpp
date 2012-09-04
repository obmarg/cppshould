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
            bool shouldNot=false
            ) :
    fileName( fileName ),
    lineNum( lineNum ),
    shouldNot( shouldNot )
    {}

    std::string fileName;
    int lineNum;
    bool shouldNot;
};


}   // namespace cppshould

#endif  // CPPSHOULD_SHOULDINFO_H_
