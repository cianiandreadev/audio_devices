#include "LogWriterLevel.h"

typedef void (*LogWriter_ProxyPF)(LogLevel level, char const *message, char const *file, char const *lineNumber);