#include <gtest/gtest.h>
#include "assertion/type_assertion.h"
#include <memory>

TEST(nullptr, the_type_of_nullptr_is_std_nullptr_t)
{
    STATIC_ASSERT_TYPE(std::nullptr_t, nullptr);
}

namespace
{
    int expect_call = 0;

    void func(int value)
    {
        expect_call = 1;
    }

    void func(void* ptr)
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

    func((void*)NULL);
    ASSERT_EQ(2, expect_call);
}

namespace
{
    std::shared_ptr<int> value_of(int value)
    {
        return std::make_shared<int>(value);
    }
}

TEST(nullptr, nullptr_is_more_meanful_than_primitive_0_or_NULL)
{
    ASSERT_TRUE(value_of(100) != nullptr);

    ASSERT_TRUE(value_of(100) != 0);
    ASSERT_TRUE(value_of(100) != NULL);
}

namespace
{
    template <typename Functor, typename Param>
    void log(Functor f, Param p)
    {
        f(p);
    }

    void fp(void*) {}
}

TEST(nullptr, only_nullptr_can_forward_template)
{
    log(fp, nullptr);

    log(fp, (void*)0);
    log(fp, (void*)NULL);
}

