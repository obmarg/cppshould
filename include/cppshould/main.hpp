//
// Main include file
//
// This file *must* be included once (and only once) in any application that
// uses cppsohould
//

#ifdef CPPSHOULD_MAIN_H_
#error "cppshould/main.hpp must only be included once"
#endif
#define CPPSHOULD_MAIN_H_

#include <cppshould/should.hpp>

namespace cppshould {

FailCallback ShouldBase::ms_failCallback = nullptr;
PassCallback ShouldBase::ms_passCallback = nullptr;

}
