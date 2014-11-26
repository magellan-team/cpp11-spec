#include <gtest/gtest.h>
#include "smart_pointer/StringBlob.h"
#include <memory>

TEST(StringBlob, string)
{
    StringBlob blob1 { "str1", "str2", "str3" };
    StringBlob blob2 { blob1 };

    std::string result;
    for(const auto & str : blob2)
    {
        result += str;
    }

    ASSERT_EQ("str1str2str3", result);
}
