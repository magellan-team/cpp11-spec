#include <gtest/gtest.h>
#include <log/Logger.h>

TEST(LogTest, should_be_able_to_trace_log)
{
    FATAL_LOG("fatal log = %d", 1);
    ERROR_LOG("error log = %d", 1);
    WARN_LOG("warn log = %d",   1);
    INFO_LOG("info log = %d",   1);
    DEBUG_LOG("debug log = %d", 1);
}
