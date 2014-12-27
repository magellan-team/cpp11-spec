#include <gtest/gtest.h>
#include <type_traits/type_traits_fixture.h>
#include "assertion/type_assertion.h"

TEST(type_property, is_const)
{
    STATIC_ASSERT_TRUE(std::is_const<const int>::value);
    STATIC_ASSERT_TRUE(std::is_const<const C2>::value);

    STATIC_ASSERT_FALSE(std::is_const<const C2&>::value);
    STATIC_ASSERT_FALSE(std::is_const<const C2*>::value);
    STATIC_ASSERT_FALSE(std::is_const<decltype(E1_ENUM)>::value);
}

TEST(type_property, is_abstrct)
{
    struct A
    {
        virtual void f() = 0;
        virtual ~A() = default;
    };

    struct B : A {};

    STATIC_ASSERT_TRUE(std::is_abstract<A>::value);
    STATIC_ASSERT_TRUE(std::is_abstract<B>::value);
}
