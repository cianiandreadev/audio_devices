#pragma once
#if !defined INC_LOGWRITERLEVEL
#define      INC_LOGWRITERLEVEL


/*! Available logging levels. The higher the level, the lower its numerical value representation.
*/
enum LogLevel {
    /*! This is not a real log level, but an indication of "not logging" */
    LOG_OFF,
    /*! Fatal - the highest level ,in general, only used by Spokes  */
    LOG_FATAL,
    /*! An error which causes irregular behavior */
    LOG_ERROR,
    /*! An error that is handled gracefully (including ingoring, if that is an option) */
    LOG_WARN,
    /*! Informational messages used to indicate some significant events */
    LOG_INFO,
    /*! Mesasges used only by a specialist to analyze program behavior */
    LOG_DEBUG,
    /*! Trace - should be avoided, meant to be used only during development */
    LOG_TRACE,
    /*! This is not a real log level, but an indication of "logging everything" */
    LOG_ALL,
    /*! A symbolic value for "not a log level" */
    LOG_UNKNOWN
};


#endif // !defined INC_LOGWRITERLEVEL
