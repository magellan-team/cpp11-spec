#include "log/Logger.h"
#include <log/stdioext.h>
#include <stdarg.h>
#include <iostream>

#ifdef _MSC_VER

    #include <Windows.h>

    #define C_RED     (FOREGROUND_RED   | FOREGROUND_INTENSITY)
    #define C_BLUE    (FOREGROUND_BLUE  | FOREGROUND_INTENSITY)
    #define C_GREEN   (FOREGROUND_GREEN | FOREGROUND_INTENSITY)
    #define C_YELLOW  (FOREGROUND_RED   | FOREGROUND_GREEN |FOREGROUND_INTENSITY)
    #define C_MAGENTA (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
    #define C_CYAN    (FOREGROUND_GREEN | FOREGROUND_BLUE  |FOREGROUND_INTENSITY)
    #define C_WHITE   (FOREGROUND_RED   | FOREGROUND_BLUE  |FOREGROUND_GREEN )

    struct Color
    {
        explicit Color(unsigned int color) : color(color) {}

        std::ostream& operator()(std::ostream& os) const
        {
            ::SetConsoleTextAttribute
                 (::GetStdHandle(STD_OUTPUT_HANDLE), color);

            return os;
        }

    private:
        unsigned int color;
    };
#else
    #define C_RED     "\033[1;31m"
    #define C_GREEN   "\033[1;32m"
    #define C_YELLOW  "\033[1;33m"
    #define C_BLUE    "\033[1;34m"
    #define C_MAGENTA "\033[1;35m"
    #define C_CYAN    "\033[1;36m"
    #define C_WHITE   "\033[0m"

    struct Color
    {
        explicit Color(const char* color) : color(color) {}

        std::ostream& operator()(std::ostream& os) const
        {
            return os << color;
        }

    private:
        const char* color;
    };
#endif

namespace
{
    std::ostream& operator<<(std::ostream& os, const Color& color)
    {
        return color(os);
    }

    void trace(const Color& color, const char* file, const int line, const char* format, va_list valist)
    {
        static char buff[1024];

        VSNPRINTF(buff, sizeof(buff), format, valist);

        std::cout << color << file << ":" << line << ":"
                  << buff  << "."  << std::endl   << Color(C_WHITE);
    }

    const Color& getColor(const int level)
    {
        static const Color colors[] =
        { Color(C_RED), Color(C_MAGENTA), Color(C_YELLOW), Color(C_CYAN), Color(C_BLUE) };

        return colors[level];
    }
}

void __log__(const int level, const char* file, const int line, const char* format, ...)
{
    va_list valist;
    va_start(valist, format);
    trace(getColor(level), file, line, format, valist);
    va_end(valist);
}
