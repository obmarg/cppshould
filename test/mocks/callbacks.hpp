
#ifndef MOCKS_CALLBACKS_H_
#define MOCKS_CALLBACKS_H_

#include "cppshould/callbacks.hpp"
#include <gmock/gmock.h>
#include <functional>

namespace cppshould {
namespace testing {

using namespace std::placeholders;

//
// Define an interface for the callbacks
// (to allow us to mock them)
//
class CallbackInterface
{
public:
    virtual ~CallbackInterface(){};
    virtual void Fail(std::string, bool)=0;
    virtual void Pass()=0;
};

//
// Create a mock class for the callbacks
//
class MockCallbacks : public CallbackInterface
{
public:
    MOCK_METHOD2(Fail, void(std::string, bool));
    MOCK_METHOD0(Pass, void());
};

// A function to hook up the callbacks
static void SetupCallbacks( CallbackInterface& callbacks )
{
    cppshould::Callbacks::SetFailCallback(
            std::bind( &CallbackInterface::Fail, &callbacks, _1, _2 )
            );
    cppshould::Callbacks::SetPassCallback(
            std::bind( &CallbackInterface::Pass, &callbacks )
            );
}

}   // namespace testing
}   // namespace cppshould

#endif  // MOCKS_CALLBACKS_H_
