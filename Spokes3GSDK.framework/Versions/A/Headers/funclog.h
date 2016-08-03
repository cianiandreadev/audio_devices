/***************************************************************************
 *
 * Copyright � 2012 Plantronics, Inc. All rights reserved.
 * This code is confidential and proprietary information belonging
 * to Plantronics, Inc. and may not be copied, modified or distributed
 * without the express written consent of Plantronics, Inc.
 *
 * Purpose: Function entry/exit logging
 *
 ****************************************************************************/


#if !defined INC_FUNCLOG
#define      INC_FUNCLOG

#if defined _MSC_VER
#define __func__ __FUNCTION__
//#define snprintf _snprintf_s
#endif

#ifdef __APPLE__
#define __func__ __PRETTY_FUNCTION__
#endif

#include <exception>
#include <cstdio>

#include "cpp/CppUtility.h"


/** Class for function entry/exit logging. To be used like:

    void f()
    {
        funclog flog(__func__);
        // whatever...
    }
*/
class funclog 
{
public:
    funclog(char const *func) : m_func(func) 
	{
#ifdef __APPLE__
		LogWriter_debug("entry", func, "<>");
#else
		LogWriter_trace("entry", func, "<>");
#endif
    }
    ~funclog() 
	{
        char s[512];
        snprintf(s, sizeof s, "exit %s", std::uncaught_exception() ? "on exception" : "");
		LogWriter_debug(s, m_func, "<>");
    }

private:
    char const *m_func;
};


/** Helper macro for literals concatenation */
#define FLOG_CONCAT(a, b) a##b

/** Helper macro for literals concatenation indirection */
#define FLOG_CONCAT2(a, b) FLOG_CONCAT(a, b)

/** Helper macro for funclog class. To be used like:

    void f()
    {
        FUNCLOG;
        // whatever...
    }
*/
#define FUNCLOG funclog FLOG_CONCAT2(flog_, __LINE__)(__func__)


#endif // !defined INC_FUNCLOG
