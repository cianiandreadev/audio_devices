/*!
 * @file
 * @author	Plantronics, Inc.
 * @version	1.0
 *
 * @section LICENSE
 *
 * Copyright � 2012 Plantronics, Inc. All rights reserved.
 * This code is confidential and proprietary information belonging to 
 * Plantronics, Inc. and may not be copied, modified or distributed
 * without the express written consent of Plantronics, Inc.
 *
 * @section DESCRIPTION
 *
 * This class supports logging to a file and console. The logger is configured by a log4cxx config xml
 * file. Review log4cxx appache documentation for more information on how the logging framework is designed.
 * This class wraps log4cxx and attempts to simplify logging for portable C++ code.
 *
 * --> RECOMMENDATION: ONLY USE THE LOG_* MACROS DEFINED BELOW TO GET FILE AND LINE NUMBER FOR FREE
 */

#pragma once
#if !defined INC_LOGWRITER
#define      INC_LOGWRITER


#include "CommonTypes.h"

#if defined _MSC_VER
#define __func__ __FUNCTION__
#endif

#define STRINGIFY(x) #x
#define TOSTRING(x) STRINGIFY(x)

// RECOMMENDED API FOR LOGGING FROM CLIENT CODE
#define LOG_TRACE(x) LogWriter_trace((x), __func__, "<>")
#define LOG_DEBUG(x) LogWriter_debug((x), __func__, "<>")
#define LOG_INFO(x) LogWriter_info((x), __func__, "<>")
#define LOG_WARN(x) LogWriter_warn((x), __func__, "<>")
#define LOG_ERROR(x) LogWriter_error((x), __func__, "<>")
#define LOG_FATAL(x) LogWriter_fatal((x),  __func__, "<>")
//use this to log a message x if the condition y is true
//#define LOG_ASSERT(x,y) LogWriter_logassert((y), x,  __func__, "<>")

void LogWriter_trace(const char *message, const char *funcName, const char *lineNumber);
void LogWriter_debug(const char *message, const char *funcName, const char *lineNumber);
void LogWriter_info(const char *message, const char *funcName, const char *lineNumber);
void LogWriter_warn(const char *message, const char *funcName, const char *lineNumber);
void LogWriter_error(const char *message, const char *funcName, const char *lineNumber);
void LogWriter_fatal(const char *message, const char *funcName, const char *lineNumber);

void LogWriter_logassert(bool condition, const char *message, const char *funcName, const char *lineNumber);


#endif // !defined INC_LOGWRITER
