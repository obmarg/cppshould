cppshould
=========

[![Build Status](https://secure.travis-ci.org/obmarg/cppshould.png)](http://travis-ci.org/obmarg/cppshould)

CppShould is a C++ library for expressing test expectations in near-english.
Here's a quick example:

    1 SHOULD_BE == 5;
    list SHOULD Contain(2);
    list SHOULD_NOT Contain(1);

Requirements
-------

The library itself only requires a modern C++ compiler.  GCC 4.6 & Clang 3.1
are the main test compilers and MSVC 2010 is tested occasionally, but it may
also work with others.

The tests of the library require the scons build system, and build against
google test & google mock (though these will be downloaded and built as part of
the build process - assuming you have wget installed)

Usage
------

CppShould is a header only library, so using it is just a case of including
it's files and away you go.

For more detailed use information, see the documentation (which isn't complete
yet.  But neither is the library itself, so that's hardly surprising)

Inspiration
-----

This library was inspired by a couple of projects from other languages:

* [RSpec Expectations](http://rubydoc.info/gems/rspec-expectations/frames) from the [RSpec](http://rspec.info/) Ruby library.
* [Should-DSL](http://www.should-dsl.info/) - a python library with a very similar purpose.
