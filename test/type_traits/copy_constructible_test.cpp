#include <gtest/gtest.h>
#include "assertion/type_assertion.h"

/*
 * A copy/move constructor for class X is trivial if it is not user-provided and if
 * — class X has no virtual functions and no virtual base classes, and
 * — the constructor selected to copy/move each direct base class subobject is trivial, and
 * — for each non-static data member of X that is of class type (or array thereof),
 *   the constructor selected to copy/move that member is trivial;
 *
 * */
TEST(is_trivially_copy_constructible, not_trivially_when_is_user_provided)
{
    struct A
    {
        A(const A&) {};
    };

    STATIC_ASSERT_FALSE(std::is_trivially_copy_constructible<A>::value);
    STATIC_ASSERT_FALSE(std::is_nothrow_copy_constructible<A>::value);
}

TEST(is_trivially_copy_constructible, explicit_defaultly_is_trivial_and_nothrowable)
{
    struct A
    {
        A(const A&) = default;
    };

    STATIC_ASSERT_TRUE(std::is_trivially_copy_constructible<A>::value);
    STATIC_ASSERT_TRUE(std::is_trivially_copy_constructible<A>::value);
}

TEST(is_trivially_copy_constructible, not_trivially_when_has_virtual_functions)
{
    struct A
    {
        virtual ~A() = default;
    };

    STATIC_ASSERT_FALSE(std::is_trivially_copy_constructible<A>::value);
}

TEST(is_trivially_copy_constructible, not_trivially_when_has_virtual_base_classes)
{
    struct A {};
    struct B : virtual A
    {
    };

    STATIC_ASSERT_FALSE(std::is_trivially_copy_constructible<B>::value);
}

TEST(is_trivially_copy_constructible, not_trivially_when_has_one_non_static_and_non_trivial_data_member)
{
    struct A
    {
        std::string s;  // string has no trivial copy constructor.
    };

    STATIC_ASSERT_FALSE(std::is_trivially_copy_constructible<A>::value);
}

TEST(is_trivially_copy_constructible, not_trivially_when_base_class_is_not_trivial)
{
    struct A
    {
        std::string s;
    };

    struct B : A {};

    STATIC_ASSERT_FALSE(std::is_trivially_copy_constructible<B>::value);
}

TEST(is_copy_constructible, is_delete_when_base_class_is_not_copy_constructible)
{
    struct A
    {
    private:
        A(const A&);
    };

    struct B
    {
        B(const B&) = delete;
    };

    struct C : A {};
    struct D : B {};

    STATIC_ASSERT_FALSE(std::is_copy_constructible<A>::value);
    STATIC_ASSERT_FALSE(std::is_copy_constructible<B>::value);
    STATIC_ASSERT_FALSE(std::is_copy_constructible<C>::value);
    STATIC_ASSERT_FALSE(std::is_copy_constructible<D>::value);
}

TEST(is_copy_constructible, is_delete_when_one_of_non_static_members_is_not_copy_constructible)
{
    struct A
    {
    private:
        A(const A&);
    };

    struct B
    {
        B(const B&) = delete;
    };

    struct C { A a; };

    struct D { B b; };

    STATIC_ASSERT_FALSE(std::is_copy_constructible<A>::value);
    STATIC_ASSERT_FALSE(std::is_copy_constructible<B>::value);
    STATIC_ASSERT_FALSE(std::is_copy_constructible<C>::value);
    STATIC_ASSERT_FALSE(std::is_copy_constructible<D>::value);
}
