//
// This file defines the structures that store info on
// the SHOULD expectation before the actual Should class
// is created.
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

//
// Class for storing SHOULD_BE info.
//
struct ShouldBeInfo : public ShouldInfo
{
    ShouldBeInfo( 
            std::string fileName, 
            int lineNum, 
            bool positive,
            bool fatal
            ) :
    ShouldInfo( fileName, lineNum, positive, fatal )
    {}
};

}   // namespace cppshould

#endif  // CPPSHOULD_SHOULDINFO_H_
