#include <gtest/gtest.h>
#include <type_traits/type_traits_fixture.h>
#include "assertion/type_assertion.h"

TEST(composite_type, is_arithmetic)
{
    STATIC_ASSERT_TRUE(std::is_arithmetic<int>::value);
    STATIC_ASSERT_TRUE(std::is_arithmetic<float>::value);

    STATIC_ASSERT_FALSE(std::is_arithmetic<void>::value);
    STATIC_ASSERT_FALSE(std::is_arithmetic<std::nullptr_t>::value);

    STATIC_ASSERT_FALSE(std::is_arithmetic<int&>::value);
    STATIC_ASSERT_FALSE(std::is_arithmetic<float*>::value);

    STATIC_ASSERT_FALSE(std::is_arithmetic<C1>::value);
    STATIC_ASSERT_FALSE(std::is_arithmetic<E1>::value);
    STATIC_ASSERT_FALSE(std::is_arithmetic<U1>::value);
}

TEST(composite_type, is_fundamental)
{
    STATIC_ASSERT_TRUE(std::is_fundamental<void>::value);
    STATIC_ASSERT_TRUE(std::is_fundamental<int>::value);
    STATIC_ASSERT_TRUE(std::is_fundamental<float>::value);
    STATIC_ASSERT_TRUE(std::is_fundamental<std::nullptr_t>::value);

    STATIC_ASSERT_FALSE(std::is_fundamental<int&>::value);
    STATIC_ASSERT_FALSE(std::is_fundamental<float*>::value);

    STATIC_ASSERT_FALSE(std::is_fundamental<C1>::value);
    STATIC_ASSERT_FALSE(std::is_fundamental<E1>::value);
    STATIC_ASSERT_FALSE(std::is_fundamental<U1>::value);
}

TEST(composite_type, is_compound)
{
    STATIC_ASSERT_FALSE(std::is_compound<void>::value);
    STATIC_ASSERT_FALSE(std::is_compound<int>::value);
    STATIC_ASSERT_FALSE(std::is_compound<float>::value);
    STATIC_ASSERT_FALSE(std::is_compound<std::nullptr_t>::value);

    STATIC_ASSERT_TRUE(std::is_compound<int&>::value);
    STATIC_ASSERT_TRUE(std::is_compound<float*>::value);

    STATIC_ASSERT_TRUE(std::is_compound<C1>::value);
    STATIC_ASSERT_TRUE(std::is_compound<E1>::value);
    STATIC_ASSERT_TRUE(std::is_compound<U1>::value);
}

TEST(composite_type, is_reference)
{
    STATIC_ASSERT_TRUE(std::is_compound<int&>::value);
    STATIC_ASSERT_TRUE(std::is_compound<C1&>::value);

    STATIC_ASSERT_TRUE(std::is_compound<int&&>::value);
    STATIC_ASSERT_TRUE(std::is_compound<C1&&>::value);
}

TEST(composite_type, is_member_pointer)
{
    STATIC_ASSERT_TRUE(std::is_member_pointer<int C3::*>::value);
    STATIC_ASSERT_TRUE(std::is_member_pointer<void (C3::*)(int) const>::value);
}

TEST(composite_type, is_scalar)
{
    STATIC_ASSERT_TRUE(std::is_scalar<int>::value);
    STATIC_ASSERT_TRUE(std::is_scalar<float>::value);
    STATIC_ASSERT_TRUE(std::is_scalar<E1>::value);
    STATIC_ASSERT_TRUE(std::is_scalar<int*>::value);
    STATIC_ASSERT_TRUE(std::is_scalar<int C3::*>::value);
    STATIC_ASSERT_TRUE(std::is_scalar<void (C3::*) (int) const>::value);
    STATIC_ASSERT_TRUE(std::is_scalar<std::nullptr_t>::value);
}
