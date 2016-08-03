#pragma once

#include "DMTypes.h"
#include "IDeviceUsage.h"
#include "ICapabilities.h"


/** Device attributes interface. An object with this interface is owned by its
    Device object, which has the sole responsibility of managing its lifetime.
*/
INTF IDeviceAttributes
{
    /** Returns a non-owning pointer to the device capabilities object, which
        lifetime is managed solely by this object. So, the user should not keep
        this pointer, or should not use it after this object (actually Device
        object of this object) is destroyed.
    */
    virtual DeviceCaps const* GetDeviceCaps() NOEXCEPT = 0;

    /** Returns a non-owning pointer to the input capabilities object, which
        lifetime is managed solely by this object. So, the user should not keep
        this pointer, or should not use it after this object (actually Device
        object of this object) is destroyed.
    */
    virtual ICapabilities const* GetInputCaps() NOEXCEPT = 0;

    /** Returns a non-owning pointer to the output capabilities object, which
        lifetime is managed solely by this object. So, the user should not keep
        this pointer, or should not use it after this object (actually Device
        object of this object) is destroyed.
    */
    virtual ICapabilities const* GetOutputCaps() NOEXCEPT = 0;

    /** Returns a non-owning pointer to the feature object, which
        lifetime is managed solely by this object. So, the user should not keep
        this pointer, or should not use it after this object (actually Device
        object of this object) is destroyed.
    */
    virtual ICapabilities const* GetFeatureCaps() NOEXCEPT = 0;

    /** Returns the delay time, in milliseconds */
    virtual int32_t GetDelayTime() NOEXCEPT = 0;

    /** Sets the delay time, in milliseconds */
    virtual void SetDelayTime(int32_t value) NOEXCEPT = 0;

    /** Returns true if the given usage (on the default usage page) exists, either as
        a button or as a value usage, on any report type.
        */
    virtual bool HasUsage(USAGE usage) const NOEXCEPT = 0;

    /** Returns true if the given usage on the given usage page exists, either as
        a button or as a value usage, on any report type.
        */
    virtual bool HasUsage(USAGE usagePage, USAGE usage) const NOEXCEPT = 0;

    /** Returns true if the given usage (on the default usage page) for the given report type
        exists as a button usage.
    */
    virtual bool HasBtnUsage(USAGE usage, ReportType enumReportType) const NOEXCEPT = 0;

    /** Returns true if the given usage (on the default usage page) for the given report type
        exists as a value usage.
    */
    virtual bool HasValUsage(USAGE usage, ReportType enumReportType) const NOEXCEPT = 0;

    /** Returns true if the given usage on the given usage page for the given report type
        exists as a button usage.
    */
    virtual bool HasBtnUsage(USAGE usagePage, USAGE usage, ReportType enumReportType) const NOEXCEPT = 0;

    /** Returns true if the given usage on the given usage page for the given report type
        exists as a value usage.
    */
    virtual bool HasValUsage(USAGE usagePage, USAGE usage, ReportType enumReportType) const NOEXCEPT = 0;

    /** Creates and returns an owning pointer to the device usage object
        for the given report type.  The user should call Release() on the
        object on end-of-life.
    */
    virtual IDeviceUsage* GetDeviceUsage(ReportType eReportType)NOEXCEPT  = 0;

    /** Returns true if the given usage is constant (as per the report descriptor) */
    virtual bool IsConstant(USAGE usage) const NOEXCEPT = 0;

private:
    void operator delete(void *);
};
