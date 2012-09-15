//!
//! .. todo:: define help text for this file.
//!
//!     At the moment I'm thinking something like
//!     "Definining custom failure & success handlers"
//!     blah blah blah

#ifndef CPPSHOULD_CALLBACKS_H_
#define CPPSHOULD_CALLBACKS_H_

#include "cppshould/should.hpp"

namespace cppshould {

//!
//! .. todo::   Also define help for this class
//!
class Callbacks 
{
public:
    static void SetFailCallback( FailCallback failCallback )
    {
        ShouldBase::ms_failCallback = std::move( failCallback );
    }
    static void SetPassCallback( PassCallback passCallback )
    {
        ShouldBase::ms_passCallback = std::move( passCallback );
    }
};

}   // namespace cppshould

#endif  //  CPPSHOULD_CALLBACKS_H_
