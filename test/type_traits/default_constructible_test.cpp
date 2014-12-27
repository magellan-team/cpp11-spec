#include <gtest/gtest.h>
#include "assertion/type_assertion.h"

/*
 * A default constructor is trivial if it is not user-provided and if:
 * — its class has no virtual functions and no virtual base classes, and
 * — no non-static data member of its class has a brace-or-equal-initializer, and
 * — all the direct base classes of its class have trivial default constructors, and
 * — for all the non-static data members of its class that are of class type (or array thereof),
 *   each such class has a trivial default constructor.
 */
TEST(is_trivially_default_constructible, not_trivially_when_is_user_provided)
{
    struct A
    {
        A() {};
    };

    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<A>::value);
}

TEST(is_trivially_default_constructible, explicit_default_default_constructor_is_trivial_and_nothrowable)
{
    struct B
    {
        B() = default;
    };
    STATIC_ASSERT_TRUE(std::is_trivially_default_constructible<B>::value);
    STATIC_ASSERT_TRUE(std::is_nothrow_default_constructible<B>::value);
}

TEST(is_trivially_default_constructible, use_defined_default_constructor_is_not_nothrowable)
{
    struct C
    {
        C() : i(0) {}

        int i;
    };
    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<C>::value);
    STATIC_ASSERT_FALSE(std::is_nothrow_default_constructible<C>::value);
}

TEST(is_trivially_default_constructible, not_trivially_when_has_virtual_functions)
{
    struct A
    {
        virtual ~A() = default;
    };

    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<A>::value);
}

TEST(is_trivially_default_constructible, not_trivially_when_has_virtual_base_classes)
{
    struct A {};
    struct B : virtual A
    {
    };

    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<B>::value);
}

TEST(is_trivially_default_constructible, not_trivially_when_brace_or_equal_initializer)
{
    struct A
    {
        int i = 10;
    };

    struct B
    {
        int j{10};
    };

    STATIC_ASSERT_TRUE(std::is_default_constructible<A>::value);
    STATIC_ASSERT_TRUE(std::is_default_constructible<B>::value);

    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<A>::value);
    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<B>::value);
}

TEST(is_trivially_default_constructible, not_trivially_when_has_one_non_static_and_non_trivial_data_member)
{
    struct A
    {
        std::string s;  // string has no trivial default constructor.
    };

    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<A>::value);
}

TEST(is_trivially_default_constructible, not_trivially_when_base_class_is_not_trivial)
{
    struct A
    {
        std::string s;
    };

    struct B : A {};

    STATIC_ASSERT_FALSE(std::is_trivially_default_constructible<B>::value);
}

TEST(is_default_constructible, default_constructor_is_delete_when_user_defined_constructors_is_exist)
{
    struct A
    {
        A(int i) : i(i) {}

        int i;
        std::string s;
    };

    STATIC_ASSERT_FALSE(std::is_default_constructible<A>::value);
}

TEST(is_default_constructible, can_explicit_define_inline_default_constructor)
{
    struct B
    {
        B() = default;
        B(const B& rhs){}
    };

    STATIC_ASSERT_TRUE(std::is_default_constructible<B>::value);
    STATIC_ASSERT_TRUE(std::is_trivially_default_constructible<B>::value);
    STATIC_ASSERT_TRUE(std::is_nothrow_default_constructible<B>::value);

}
