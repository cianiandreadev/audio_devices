#pragma once

#ifndef IDEVICEUSAGE
#define IDEVICEUSAGE
#endif

#include "DMTypes.h"
#include "Usage.h"
#include <memory>
#include <vector>

/** Device usage interface.

    It holds an array of usages of interes to the user, provides functions to work
    with those usages, but also with all usages of the device.  This includes reading
    and writing reports.

    It also holds an internal buffer for report(s).
*/
class IDeviceUsage : public IDisposable
{
public:
    /** Adds a usage to the internal array of usages */
    virtual void AddUsage(const Usage& usage) = 0;

    /** Adds a usage to the internal array of usages with the default value */
    virtual void AddUsage(uint16_t usagePage, uint16_t usage) = 0;

    /** Adds a usage to the internal array of usages, with the given value */
    virtual void AddUsage(uint16_t usagePage, uint16_t usage, unsigned long value) = 0;

    /** Returns a non-owning pointer to the found usage. The usage is looked for in the
        internal array.
        If the usage is not found, returns nullptr.
    */
    virtual Usage const* FindUsage(const USAGE usage) NOEXCEPT = 0;

    /** Set the values of all the usages from the internal array to the internal report buffer.

        Initializes the internal report buffer if it is not initialized.
    */
    virtual DMResult SetUsage() NOEXCEPT = 0;

    /** Set the value of the given usage to the internal report
        buffer, bypassing the internal usage array.

        Initializes the internal report buffer if it is not initialized,
        as per the first element of the usage array.
    */
    virtual DMResult SetOutputUsage(const Usage& usage) NOEXCEPT = 0;

    /** Set the given usage to the internal report buffer, bypassing the
        internal usage array, using the default value.

        Initializes the internal report buffer if it is not initialized,
        as per the first element of the usage array.
    */
    virtual DMResult SetOutputUsage(uint16_t usagePage, uint16_t usage) NOEXCEPT = 0;

    /** Set the given usage to the internal report buffer, bypassing the
        internal usage array, using the given value.

        Initializes the internal report buffer if it is not initialized,
        as per the first element of the usage array.
    */
    virtual DMResult SetOutputUsage(uint16_t usagePage, uint16_t usage, unsigned long value) NOEXCEPT = 0;

    /** Set the given usage to the internal report buffer, bypassing the
        internal usage array, using the given value.

        Initializes the internal report buffer if it is not initialized,
        as per the given reportID.
    */
    virtual DMResult SetOutputUsage(uint8_t reportID, uint16_t usagePage, uint16_t usage, unsigned long value) NOEXCEPT = 0;
    

    /** Sets the first usage in the internal usage array to the internal report buffer, using
        the given value. Bypasses the value of the usage in the internal array.

        Assumes the internal report buffer is initialized.
        */
    virtual DMResult SetValue(int32_t val) NOEXCEPT = 0;

    /** Sets the given usage in the internal usage array to the internal report buffer, using
        the given value. Bypasses the internal usage array.

        Assumes the internal report buffer is initialized.
        */
    virtual DMResult SetValue(const Usage& usage) NOEXCEPT = 0;

    /** Sets the given usage in the internal usage array to the internal report buffer, using
        the given value. Bypasses the internal usage array.

        Initializes the internal report buffer (if not already initialized).
        */
    virtual DMResult SetOutputValue(const Usage& usage) NOEXCEPT = 0;

    /** Sets the given usage in the internal usage array to the internal report buffer, using
        the default value. Bypasses the internal usage array.

        Initializes the internal report buffer (if not already initialized).
        */
    virtual DMResult SetOutputValue(uint16_t usagePage, uint16_t usage) NOEXCEPT = 0;

    /** Sets the given usage in the internal usage array to the internal report buffer, using
        the given value. Bypasses the internal usage array.

        Initializes the internal report buffer (if not already initialized).
        */
    virtual DMResult SetOutputValue(uint16_t usagePage, uint16_t usage, unsigned long value) NOEXCEPT = 0;

    /** Returns the report ID which contains the given usage (and usage page).
    */
    virtual DMResult GetReportID(uint16_t i_usagePage, uint16_t i_usage, uint8_t &o_reportID) NOEXCEPT = 0;

	/** Returns the report ID which contains the given usage for default PLT usage page
    */
    virtual DMResult GetReportID(uint16_t i_usage, uint8_t &o_reportID) NOEXCEPT = 0;

    /** Returns the maximum length of the usage list array (to be used with GetUsages functions).
    */
    virtual int32_t GetMaxUsageListLength(USAGE usagePage) NOEXCEPT = 0;

    /** Reads the active usages for the given usage page from the internal report buffer. Bypasses the internal usage array.
    */
    virtual DMResult GetUsages(USAGE usagePage, USAGE usages[], uint32_t& maxUsageListLen) NOEXCEPT = 0;

    /** Reads the active usages for the given usage page from the given report buffer. Bypasses the internal usage array.
    */
    virtual DMResult GetUsages(USAGE usagePage, USAGE usages[], uint32_t& maxUsageListLen, uint8_t const * pReportBuffer, int32_t reportBufferSize) NOEXCEPT = 0;

    /** Reads the active usages from the internal report buffer and copies the values to the
        internal usage array.
        */
    virtual DMResult GetUsage() NOEXCEPT = 0;

    /** Returns the usage value of the first usage in the internal usage array from the internal report buffer.
        Bypasses the internal usage array.
    */
    virtual uint32_t GetValue() NOEXCEPT = 0;

    /** Gives the usage value of the given usage from the internal report buffer.
        Bypasses the internal usage array.
    */
    virtual DMResult GetValue(USAGE usagePage, USAGE usage, uint32_t &data) NOEXCEPT = 0;

    /** Gives the usage value of the given usage from the given report buffer. 
        Bypasses the internal usage array.
    */
    virtual DMResult GetValue(USAGE usagePage, USAGE usage, uint8_t* buffer, int32_t bufferSize, uint32_t& data) NOEXCEPT = 0;

    /** Gives the value array of the first usage in the internal usage array from the internal report buffer.
        The value array is read to the given buffer with the given length. Length can be calculated by calling
        GetValueArraySize() function.
    */
    virtual DMResult GetValueArray(uint8_t* values, uint16_t len) NOEXCEPT = 0;

    /** Gives the value array of the given usage from the internal report buffer.
        The value array is read to the given buffer with the given length. Length can be calculated by calling
        GetValueArraySize() function.
    */
    virtual DMResult GetValueArray(uint16_t usagePage, USAGE usage, uint8_t* values, uint16_t len) NOEXCEPT = 0;

    /** Gives the required size (dimension) of the value array of the first usage in the internal usage array.
    */
    virtual uint32_t GetValueArraySize() const NOEXCEPT = 0;

    /** Gives the required size (dimension) of the value array of the given usage in the internal usage array.
    */
    virtual uint32_t GetValueArraySize(uint16_t usagePage, USAGE usage) const NOEXCEPT = 0;

    /** Gives the usage data value of the given usage from the internal report buffer. The data index is
        read from device attributes (capabilities).
    */
    virtual DMResult GetData(USAGE usagePage, USAGE usage, uint32_t& data) NOEXCEPT = 0;

    /** Gives the usage data value of the given usage from the given report buffer. The data index is
        read from device attributes (capabilities).
    */
    virtual DMResult GetData(USAGE usagePage, USAGE usage, uint8_t const * buffer, int32_t bufferSize, uint32_t& data) NOEXCEPT = 0;

    /** Given the array of usages that were ON in a previous read, and those from a current read,
        gives a list of the usages that are in the current and weren't in the previous ("make" list/array).
        It is assumed that all arrays are of the same dimension, and that the elements of the arrays
        that are not populated with usage ID have the value 0.

        The elements of the make list which are not populated with usage ID will have the value set to 0.
        */
    virtual DMResult GetMakeList(pUSAGE previousUsageList, pUSAGE currentUsageList, pUSAGE makeList, int32_t usageListLen) NOEXCEPT = 0;

    /** Given the array of usages that were ON in a previous read, and those from a current read,
        gives a list of the usages that are were the previous and aren't in the current.
        It is assumed that all arrays are of the same dimension, and that the elements of the arrays
        that are not populated with usage ID have the value 0.

        The elements of the break list which are not populated with usage ID will have the value set to 0.
        */
    virtual DMResult GetBreakList(pUSAGE previousUsageList, pUSAGE currentUsageList, pUSAGE breakList, int32_t usageListLen) NOEXCEPT = 0;

    /** Given the array of usages that were ON in a previous read, and those from a current read,
        gives two lists (arrays):
        - a list of the usages that are in the current and weren't in the previous (make list)
        - a list of the usages that are were the previous and aren't in the current (break list)

        It is assumed that all arrays are of the same dimension, and that the elements of the arrays
        that are not populated with usage ID have the value 0.

        The elements of the break and make lists which are not populated with usage ID will have the value set to 0.
        */
    virtual DMResult GetMakeBreakList(pUSAGE previousUsageList, pUSAGE currentUsageList, pUSAGE makeList, pUSAGE breakList, uint32_t usageListLen) NOEXCEPT = 0;

    /** Writes the report in the internal report buffer to the device */
    virtual DMResult WriteReport() = 0;

    /** Writes the given report buffer to the device, using default length. Excess bytes are filled with zeros. */
    virtual DMResult WriteReport(uint8_t const *buffer, int32_t len) NOEXCEPT = 0;

    /** Writes the given report buffer to the device with the given length */
    virtual DMResult WriteReportRaw(uint8_t const *buffer, int32_t len) NOEXCEPT = 0;

    /** Writes the given report buffer to the device with the given length, using alternate method */
    virtual DMResult WriteReportCT(uint8_t const *buffer, int32_t len) NOEXCEPT = 0;

    /** Writes the report in the internal report buffer to the device, with a delay */
    virtual DMResult WriteReportWithDelay() NOEXCEPT = 0;

    /** Gives a non-owning pointer to the array of chars which holds the report buffer,
        and also the dimension of the array (number of elements).
        */
    virtual DMResult GetReport(uint8_t** reportBuffer, uint32_t *length) NOEXCEPT = 0;

    /** Reads a feature report from the device and puts it in the provided buffer.
        This buffer should be obtained by calling GetReport() member function or
        properly initialized by some other means.
    */
    virtual DMResult ReadFeature(uint8_t* buffer, int32_t len) NOEXCEPT = 0;

    /** Reads a feature report from the device and puts it in the internal report buffer.
    */
    virtual DMResult ReadFeature() NOEXCEPT = 0;

    /** Reads an input report from the device and puts it in the provided buffer.
        This buffer should be obtained by calling GetReport() member function or
        properly initialized by some other means.
    */
    virtual DMResult ReadInput(uint8_t* buffer, int32_t len) NOEXCEPT = 0;

    /** Reads an input report from the device and puts it in the internal report buffer.
    */
    virtual DMResult ReadInput() NOEXCEPT = 0;

private:
    void operator delete(void*);
};

typedef IDeviceUsage* pDeviceUsage;
typedef IDeviceUsage** ppDeviceUsage;
