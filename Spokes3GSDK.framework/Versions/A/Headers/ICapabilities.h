#pragma once
#if !defined IDEVICECAPABILITIES
#define      IDEVICECAPABILITIES


#include "DMTypes.h"
#include "HIDtypes.h"


/** Capabilities class - used for device, input, output and feature
    capabilities, that is, button and value usages.  */
INTF ICapabilities : public IDisposable
{
    /** Adds a button capability */
    virtual void AddButtonCap(ButtonCap const& buttonCap) NOEXCEPT = 0;

    /** Adds a value capability */
    virtual void AddValueCap(ValueCap const& valueCap) NOEXCEPT = 0;

    /** Returns a non-owning pointer to the button capability for the given usage page
        and usage. Returns nullptr if there is no such usage.
        */
    virtual ButtonCap const* GetButtonUsage(uint16_t usagePage, uint16_t usage) const NOEXCEPT = 0;

    /** Returns a non-owning pointer to the value capability for the given usage page
        and usage. Returns nullptr if there is no such usage.
        */
    virtual ValueCap const* GetValueUsage(uint16_t usagePage, uint16_t usage) const NOEXCEPT = 0;

    /** Gives a non-owning pointer to the array of (all) available button capabilities,
        and dimension of the array (number of elements).
    */
    virtual DMResult GetButtonCaps(ButtonCap const** ppCaps, uint32_t *length) const NOEXCEPT = 0;

    /** Gives a non-owning pointer to the array of (all) available value capabilities,
        and dimension of the array (number of elements).
    */
    virtual DMResult GetValueCaps(ValueCap const** ppCaps, uint32_t *length) const NOEXCEPT = 0;

    /** Returns number of button caps */
    virtual uint32_t GetButtonCapsCount() const NOEXCEPT = 0;

    /** Returns number of value caps */
    virtual uint32_t GetValueCapsCount() const NOEXCEPT = 0;

private:
    void operator delete(void *);
};


#endif // !defined IDEVICECAPABILITIES
