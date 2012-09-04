//
// This file defines the base Expectation class
//

#include <string>

namespace cppshould {
namespace expectations {

//
// Base expectation class
// 
class BaseExpectation
{
public:
    virtual ~BaseExpectation() {};

    virtual std::string MessageIfPasses()=0;
    virtual std::string MessageIfFails()=0;
};

//
// Expectation template, all expectations should inherit from this
//
template< class ExpectT >
class Expectation
{
public:
    typedef ExpectT ExpectedT;
};

};
}; 
