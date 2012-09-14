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
            bool positive,
            bool fatal
            ) :
    fileName( fileName ),
    lineNum( lineNum ),
    positive( positive ),
    fatal( fatal )
    {}

    std::string fileName;
    int lineNum;
    bool positive;
    bool fatal;
};


}   // namespace cppshould

#endif  // CPPSHOULD_SHOULDINFO_H_
