#ifndef HCDDE3E7F_33D9_42FB_BF1B_42D25574DDB4
#define HCDDE3E7F_33D9_42FB_BF1B_42D25574DDB4

void __log__(const int level, const char* file, const int line, const char* format, ...);

#define __LOG(level, format, ...) __log__(level, __FILE__, __LINE__, format, ##__VA_ARGS__)

enum Level { FATAL, ERROR, WARN, INFO, DEBUG, };

#define FATAL_LOG(format, ...) __LOG(FATAL, format, __VA_ARGS__)
#define ERROR_LOG(format, ...) __LOG(ERROR, format, __VA_ARGS__)
#define WARN_LOG(format, ...)  __LOG(WARN,  format, __VA_ARGS__)
#define INFO_LOG(format, ...)  __LOG(INFO,  format, __VA_ARGS__)
#define DEBUG_LOG(format, ...) __LOG(DEBUG, format, __VA_ARGS__)

#endif
