#pragma once
#if !defined INC_COMMONTYPES
#define      INC_COMMONTYPES

#include <stdint.h>

/** All classes which contain only pure virtual functions and are exposed through the SDK
    (DLL/.so boundaries), thus called interfaces, are declared with INTF.
    A class that is not exposed should not be declared with INTF.
*/
#define INTF struct

#if !defined IMPORTER && defined _WIN32
#define DllExport   __declspec( dllexport )
#elif defined _WIN32
#define DllExport   __declspec( dllimport )
#else
#define DllExport
#endif

#if defined _MSC_VER
// until such a time that MSC++ gets standards-compliant NOEXCEPT
#define NOEXCEPT
#endif

#ifdef __APPLE__
#define NOEXCEPT
#endif

/*! The interface that all other interfaces that provide object ownership to users
    inherit.
*/
INTF IDisposable
{
    /*!
     * Allow the caller to delete the memory and all other resources associated with this 
     * class instance
     */
    virtual void Release() NOEXCEPT = 0;
};


#endif // !defined INC_COMMONTYPES
