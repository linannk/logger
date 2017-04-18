#include "logger.h"

BEGIN_LOGGER_NAMESPACE
LogHelper::LogUtil& LogHelper::LogUtil::Inst() {
    static LogUtil s_inst;
    return s_inst;
}
END_LOGGER_NAMESPACE

#ifdef WIN32
#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

BEGIN_LOGGER_NAMESPACE
void SetConsoleForgroundColor(FILE* stream, unsigned short clr)
{
    if (stream == stdout) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, clr);
    }
    else if (stream == stderr) {
        HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
        SetConsoleTextAttribute(hStdErr, clr);
    }
}

void ResetConsoleForgroundColor(FILE* stream)
{
    if (stream == stdout) {
        HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
        SetConsoleTextAttribute(hStdOut, 0x07);
    }
    else if (stream == stderr) {
        HANDLE hStdErr = GetStdHandle(STD_ERROR_HANDLE);
        SetConsoleTextAttribute(hStdErr, 0x07);
    }
}
END_LOGGER_NAMESPACE
#else
BEGIN_LOGGER_NAMESPACE
void SetConsoleForegroundColor(FILE* stream, unsigned short clr) {
    fprintf(stream, "\033[3%d", clr);
}

void ResetConsoleForegroundColor(FILE* stream)
{
    fprintf(stream, "\033[0m");
}
END_LOGGER_NAMESPACE
#endif // WIN32
