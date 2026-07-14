#include "AUI/Internal/Log.h"
#include <cstdio>
#include <cstdarg>

namespace AUI
{
bool stdoutLoggingEnabled = false;
FILE* logFilePtr = nullptr;

void Log::info(const char* expression, ...)
{
    // If enabled, write to stdout.
    if (stdoutLoggingEnabled) {
        std::va_list arg;
        va_start(arg, expression);

        std::vprintf(expression, arg);
        std::printf("\n");
        std::fflush(stdout);

        va_end(arg);
    }

    // If enabled, write to file.
    if (logFilePtr) {
        std::va_list arg;
        va_start(arg, expression);

        std::vfprintf(logFilePtr, expression, arg);
        std::fprintf(logFilePtr, "\n");
        std::fflush(logFilePtr);

        va_end(arg);
    }
}

void Log::error(const char* fileName, int line, const char* expression, ...)
{
    // If enabled, write to stdout.
    if (stdoutLoggingEnabled) {
        std::va_list arg;
        va_start(arg, expression);

        std::printf("Error at file: %s, line: %d\n", fileName, line);
        std::vprintf(expression, arg);
        std::printf("\n");
        std::fflush(stdout);

        va_end(arg);
    }

    // If enabled, write to file.
    if (logFilePtr) {
        std::va_list arg;
        va_start(arg, expression);

        std::fprintf(logFilePtr, "Error at file: %s, line: %d\n", fileName,
                     line);
        std::vfprintf(logFilePtr, expression, arg);
        std::fprintf(logFilePtr, "\n");
        std::fflush(logFilePtr);

        va_end(arg);
    }
}

void Log::enableStdoutLogging()
{
    stdoutLoggingEnabled = true;
}

void Log::enableFileLogging(const std::string& fileName)
{
    // Open the log file.
    logFilePtr = fopen(fileName.c_str(), "w");
    if (!logFilePtr) {
        std::printf("Failed to open log file for writing.\n");
    }
}

} // namespace AUI
