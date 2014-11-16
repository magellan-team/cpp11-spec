#include <gtest/gtest.h>
#include "assertion/type_assertion.h"

TEST(nullptr, the_type_of_nullptr_is_std_nullptr_t)
{
    ASSERT_TYPE(std::nullptr_t, nullptr);
}

namespace
{
    int expect_call = 0;

    void func(int value)
    {
        expect_call = 1;
    }

    void func(int* ptr)
    {
        expect_call = 2;
    }
}

TEST(nullptr, only_nullptr_is_unambiguously_a_pointer)
{
    func(0);
    ASSERT_EQ(1, expect_call);

    func(nullptr);
    ASSERT_EQ(2, expect_call);

    func((int*)NULL);
    ASSERT_EQ(2, expect_call);
}
