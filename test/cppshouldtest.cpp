
#include "cppshould/expectations/contain.hpp"
#include "cppshould/operators.hpp"
#include "cppshould/macros.hpp"
#include <iostream>
#include <vector>

using namespace cppshould::expectations;

int main( int argc, char** argv )
{
    std::vector< int > intList = { 1, 2, 3 };
    intList SHOULD Contain(1);
    intList >> cppshould::ShouldInfo(__FILE__, __LINE__) << Contain(1);
    try
    {
        intList SHOULD Contain(10);
        std::cout << "no exception";
    }
    catch( std::runtime_error& )
    {
        std::cout << "Caught Exception";
    }
}
