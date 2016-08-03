#pragma once
#if !defined INC_CPPUTILITY
#define INC_CPPUTILITY


#include <sstream>
#include <memory>

#include "LogWriter.h"

#include "DeviceManager.h"


struct IDisposableDeleter {
    void operator()(IDisposable* ptr) {
        if (ptr != nullptr) ptr->Release();
    }
};

struct IDisposableNoOpDeleter {
	void operator()(IDisposable* ptr) {}
};

template<typename T>
using DisposableUniquePtr = std::unique_ptr<T, IDisposableDeleter>;

template<typename T>
using DisposableNoOpUniquePtr = std::unique_ptr<T, IDisposableNoOpDeleter>;

inline std::unique_ptr<IDeviceUsage, IDisposableDeleter> get_IDeviceUsage(IDeviceAttributes* attributes, ReportType type) {
    return std::unique_ptr<IDeviceUsage, IDisposableDeleter>(attributes->GetDeviceUsage(type), IDisposableDeleter());
}

inline std::unique_ptr<IDeviceUsage, IDisposableDeleter> get_IDeviceUsage(IDevice* device, ReportType type) {
    IDeviceAttributes* attributes = nullptr;
    device->getDeviceAttributes(&attributes);
    return get_IDeviceUsage(attributes, type);
}


inline std::unique_ptr<IDeviceGroup , IDisposableDeleter> get_Devices(IDeviceManager* mgr) {
    IDeviceGroup *p = nullptr;
    if (DM_RESULT_SUCCESS == mgr->getDevices(&p)) {
        return std::unique_ptr<IDeviceGroup , IDisposableDeleter>(p, IDisposableDeleter());
    }
    return nullptr;
}


inline std::unique_ptr<IDeviceGroup , IDisposableDeleter> get_HIDDevices(IDeviceManager* mgr, uint16_t i_usagePage) {
    IDeviceGroup *p = nullptr;
    if (DM_RESULT_SUCCESS == mgr->getHIDDevices(i_usagePage, &p)) {
        return std::unique_ptr<IDeviceGroup , IDisposableDeleter>(p, IDisposableDeleter());
    }
    return nullptr;
}


inline std::unique_ptr<IDeviceGroup , IDisposableDeleter> get_Devices(IDeviceManager* mgr, eVendorID vendorID) {
    IDeviceGroup *p = nullptr;
    if (DM_RESULT_SUCCESS == mgr->getDevices(vendorID, &p)) {
        return std::unique_ptr<IDeviceGroup , IDisposableDeleter>(p, IDisposableDeleter());
    }
    return nullptr;
}


inline std::unique_ptr<IDeviceGroup , IDisposableDeleter> get_Devices(IDeviceManager* mgr, eVendorID vendorID, eProductID productID) {
    IDeviceGroup *p = nullptr;
    if (DM_RESULT_SUCCESS == mgr->getDevices(vendorID, productID, &p)) {
        return std::unique_ptr<IDeviceGroup , IDisposableDeleter>(p, IDisposableDeleter());
    }
    return nullptr;
}

inline bool has_usage_page(IDevice* device, uint16_t i_usagePage) {
	IDeviceAttributes* attributes = nullptr;
	if (DM_RESULT_SUCCESS != device->getDeviceAttributes(&attributes))
		return false;
	auto caps = attributes->GetDeviceCaps();
	if (!caps)
		return false;
	return caps->UsagePage == i_usagePage;
}


inline void LogWriter_trace(const std::ostream& msgStream, const char *filePath, const char *lineNumber) {
    LogWriter_trace(dynamic_cast<const std::ostringstream&>(msgStream).str().c_str(), filePath, lineNumber);
}


inline void LogWriter_debug(const std::ostream& msgStream, const char *filePath, const char *lineNumber) {
    LogWriter_debug(dynamic_cast<const std::ostringstream&>(msgStream).str().c_str(), filePath, lineNumber);
}


inline void LogWriter_info(const std::ostream& msgStream, const char *filePath, const char *lineNumber) {
    LogWriter_info(dynamic_cast<const std::ostringstream&>(msgStream).str().c_str(), filePath, lineNumber);
}


inline void LogWriter_warn(const std::ostream& msgStream, const char *filePath, const char *lineNumber) {
    LogWriter_warn(dynamic_cast<const std::ostringstream&>(msgStream).str().c_str(), filePath, lineNumber);
}


inline void LogWriter_error(const std::ostream& msgStream, const char *filePath, const char *lineNumber) {
    LogWriter_error(dynamic_cast<const std::ostringstream&>(msgStream).str().c_str(), filePath, lineNumber);
}

inline void LogWriter_fatal(const std::ostream& msgStream, const char *filePath, const char *lineNumber) {
    LogWriter_fatal(dynamic_cast<const std::ostringstream&>(msgStream).str().c_str(), filePath, lineNumber);
}


#endif // !defined INC_CPPUTILITY
