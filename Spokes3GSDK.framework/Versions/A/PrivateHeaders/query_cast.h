#pragma once
#if !defined INC_QUERY_CAST
#define      INC_QUERY_CAST


#include <cassert>


#include "IHostCommand.h"
#include "IDeviceEvents.h"
#include "IDeviceListener.h"


/** Helper template function to be used on IHostCommand, IDeviceEvents and IDeviceListener
    interface (or any other interface that supports the "query" concept)
    to get an interface pointer. To be used like:

    IHostCommand *pHostCommand; // obtained somehow...
    IDeviceSettings *pDevSettings;
    if (query_interface(pHostCommand, &pDevSettings)) {
        // do something with pDevSettings
    }
    */
template<typename X, typename T>
inline bool query_interface(X *pX, T** pp) {
    assert(pp != nullptr);
    assert(pX != nullptr);
    auto pQuery = pX->getQuery();
    assert(pQuery != nullptr);
    return pQuery->query(pp);
}

/** Helper template function to be used on IHostCommand, IDeviceEvents and IDeviceListener
    interface (or any other cast that supports the "query" concept)
    to get an interface pointer. Used like dynamic_cast - just replace "dynamic" with "query".

    IHostCommand *pHostCommand; // obtained somehow...
    auto *pDevSettings = query_cast<IDeviceSettings>(pHostCommand)) {
        // do something with pDevSettings
    }
    */
template<typename T, typename X>
inline T *query_cast(X *pX) {
    auto pQuery = pX->getQuery();
    assert(pQuery != nullptr);
    T *p = nullptr;
    if (!pQuery->query(&p)) {
        return nullptr;
    }
    return p;
}

#endif // !defined INC_QUERY_CAST