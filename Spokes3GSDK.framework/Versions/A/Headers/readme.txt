SPOKES 3G SDK
=============

This directory contains the Spokes 3G SDK header files.

The main header files are:

- DeviceManager.h has all the core interfaces of DM

- Spokes3G.h has all the core interfaces above DM

All other header files are included from those main header files.

There are the following sub-directories:

- cpp: contains headers specific to C++ users of the SDK


CONTENTS
========

The header files contain:

- Constants declarations (enums, #defines...)

- Interface definitions (as classes)

- Factory (object creation/getting) functions - as free functions

Scalar types are preffered to structures (records, Plain Old C Objects), 
but are used when the alternative is too verbose.

There are no namespaces or templates, as they are not portable.

That is all that can be in the Spokes 3G SDK header files.


INTERFACES
==========

Interfaces are declared with the INTF declaration. They are
pure abstract classes. That is, they _only_ have pure virtual
functions.

They don't have virtual destructors, as this is not portable.

None of the interface functions throw exceptions, as they are not portable.


Interface Ownership Policy
--------------------------

Interfaces to objects that the Spokes SDK user owns have (are inherited from)
IDisposable interface.  SDK user should, in general, manage the life-time 
of such objects and call the IDisposable::Release() on end-of-life.  But, 
there are exceptions, as some SDK functions return interfaces that inherit 
IDisposable, but which Spokes SDK manages, and user should not manage. 
Documentation for each function states the ownership assumptions and
requirements.

If the interface doesn't inherit IDisposable, then the user doesn't own
the object and can only assume that the object exists during the execution
of the function which receives the pointer or reference to such object.
The user should save a copy of any data from such objects for further use.