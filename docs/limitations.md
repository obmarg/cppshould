Limitations
===========

This document details some of the anticipated limitations & difficulties for
this library when used with various different test frameworks.

CppUnit
-------

As it is the framework I am most familiar with, most of the PoC work I have
done is fairly compatible with it.

### SHOULD vs MUST

I expect to require a little boilerplate to implement proper SHOULD (as opposed
to MUST which can just use the existing failure methods) support - as it does
not currently have anything like this functionality that I can just piggy back
on top of.

Currently I am undecided exactly how to tackle this - either a macro that
should be called at the end a test function or a subclass of the
CppUnit::TestFixture class seem like they may be the best ways to go.
Alternatively it might be possible to replace the CPPUNIT_TEST macro with
something else.  That seems like the most work for end-users though compared to
the other options.

I am also unsure of how to handle output in the case when there have been
several SHOULD failures.  Obviously I can just stick all the error messages
together, but it would be nice if there was a better way to handle this.

Google Test
---------

### MUST difficulties

I expect to have difficulties implementing the MUST functionality for google
test, as the standard google test method of handling ASSERT_* is to return from
the function, and this will not be possible for either of my planned SHOULD &
Expect syntaxes.

It might be possible for me to implement different test macros from the
standard google test TEST_ options, but that does not sound like the best
option - it will be a fair bit of work and likely to be fragile.

Other options would be to just not support MUST for google test, or come up
with some other syntax for handling things.  In particular some support could
be implemented for EXPECT( x SHOULD_BE == y) or similar.  This might run into
some difficulties if any templates were used in the expression though, just
like BOOST_FOREACH has difficulties with this.  It is also way more verbose
than I like.

CppSpec
------

Not looked into this yet, but I may have difficulty playing nice with the whole
context functionality that it seems to use

Boost Test
------

Not looked into this heavily, but at first glance it appears to support
non-fatal errors and use exceptions, so this might actually be the best
framework to develop for.  Excellent.
