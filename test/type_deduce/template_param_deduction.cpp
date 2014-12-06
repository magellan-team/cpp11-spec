#include <gtest/gtest.h>
#include "assertion/type_assertion.h"

namespace
{
    auto i = 10;
    auto &r = i;

    const auto  ci = 10;
    auto& cr = ci;

    auto p = &i;
    auto pc = &ci;
    const int* const cpc = &i;

#define DEF_GENERIC_FUNC(prototype)                                                         \
    template <typename ExpectTemplateParamType, typename ExpectArgumentType, typename T>    \
    void prototype                                                                          \
    {                                                                                       \
        STATIC_ASSERT_SAME_TYPE(ExpectTemplateParamType, T);                                \
        STATIC_ASSERT_SAME_TYPE(ExpectArgumentType, decltype(t));                           \
    }

    DEF_GENERIC_FUNC(lvalue_reference(T& t))
    DEF_GENERIC_FUNC(lvalue_reference_to_const(const T& t))
    DEF_GENERIC_FUNC(lvalue_pointer(T* t))
    DEF_GENERIC_FUNC(lvalue_pointer_to_const(const T* t))
    DEF_GENERIC_FUNC(rvalue_reference(T&& t))
    DEF_GENERIC_FUNC(value(T t))
    DEF_GENERIC_FUNC(const_value(const T t))
}

TEST(lvalue_reference, should_deduce_for_non_const_obj)
{
    lvalue_reference<int, int&>(i);
}

TEST(lvalue_reference, should_deduce_for_ref_to_non_const_obj)
{
    lvalue_reference<int, int&>(r);
}

TEST(lvalue_reference, should_deduce_for_const_obj)
{
    lvalue_reference<const int, const int&>(ci);
}

TEST(lvalue_reference, should_deduce_for_ref_to_const_obj)
{
    lvalue_reference<const int, const int&>(cr);
}

TEST(lvalue_reference_to_const, should_deduce_for_non_const_obj)
{
    lvalue_reference_to_const<int, const int&>(i);
}

TEST(lvalue_reference_to_const, should_deduce_for_ref_to_non_const_obj)
{
    lvalue_reference_to_const<int, const int&>(r);
}

TEST(lvalue_reference_to_const, should_deduce_for_const_obj)
{
    lvalue_reference_to_const<int, const int&>(ci);
}

TEST(lvalue_reference_to_const, should_deduce_for_ref_to_const_obj)
{
    lvalue_reference_to_const<int, const int&>(cr);
}

TEST(rvalue, should_deduce_for_non_const_obj)
{
    rvalue_reference<int&, int&>(i);
}

TEST(rvalue, should_deduce_for_ref_to_non_const_obj)
{
    rvalue_reference<int&, int&>(r);
}

TEST(rvalue, should_deduce_for_const_obj)
{
    rvalue_reference<const int&, const int&>(ci);
}

TEST(rvalue, should_deduce_for_ref_to_const_obj)
{
    rvalue_reference<const int&, const int&>(cr);
}

TEST(rvalue, should_deduce_for_rvalue)
{
    rvalue_reference<int, int&&>(10);
}

TEST(value, should_deduce_for_non_const_obj)
{
    value<int, int>(i);
    const_value<int, const int>(i);
}

TEST(value, should_deduce_for_ref_to_non_const_obj)
{
    value<int, int>(r);
    const_value<int, const int>(r);
}

TEST(value, should_deduce_for_const_obj)
{
    value<int, int>(ci);
    const_value<int, const int>(ci);
}

TEST(value, should_deduce_for_ref_to_const_obj)
{
    value<int, int>(cr);
    const_value<int, const int>(cr);
}

TEST(value, should_deduce_for_const_pointer_to_const_obj)
{
    value<const int*, const int*>(cpc);
    const_value<const int*, const int* const>(cpc);
}

TEST(array_decays_to_pointer, should_deduce_for_arr)
{
    const int arr[] = {1, 2, 3};

    lvalue_reference<const int[3], const int(&)[3]>(arr);
    lvalue_reference_to_const<int[3], const int(&)[3]>(arr);
    
    value<const int*, const int*>(arr);
}

static void func(int, double) {}

TEST(function_decays_to_pointer, should_deduce_for_function)
{
    value<void(*)(int, double), void(*)(int, double)>(func);
    lvalue_reference<void(int, double), void(&)(int, double)>(func);
    lvalue_reference_to_const<void(int, double), void(&)(int, double)>(func);
}
