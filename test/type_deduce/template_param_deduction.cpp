#include <gtest/gtest.h>
#include "assertion/type_assertion.h"
#include <initializer_list>

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
    DEF_GENERIC_FUNC(universal_reference(T&& t))
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

TEST(lvalue_reference_to_const, should_deduce_for_nullptr)
{
    lvalue_reference_to_const<std::nullptr_t, const std::nullptr_t&>(nullptr);
}

TEST(lvalue_reference_to_const, should_deduce_for_pointer)
{
    auto pi = &i;
    auto pci = &ci;

    STATIC_ASSERT_TYPE(int*, pi);
    STATIC_ASSERT_TYPE(const int*, pci);

    lvalue_reference_to_const<int*, int* const&>(pi);
    lvalue_reference_to_const<const int*, const int* const&>(pci);
}

TEST(universal_reference, should_deduce_for_non_const_obj)
{
    universal_reference<int&, int&>(i);
}

TEST(universal_reference, should_deduce_for_ref_to_non_const_obj)
{
    universal_reference<int&, int&>(r);
}

TEST(universal_reference, should_deduce_for_const_obj)
{
    universal_reference<const int&, const int&>(ci);
}

TEST(universal_reference, should_deduce_for_ref_to_const_obj)
{
    universal_reference<const int&, const int&>(cr);
}

TEST(universal_reference, should_deduce_for_rvalue)
{
    universal_reference<int, int&&>(10);
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

namespace
{
    int arr[] = {1, 2, 3};
    const int carr[] = {1, 2, 3};

    auto &rarr = arr;
    auto &crarr = carr;
}

TEST(array_type, should_deduce_for_array)
{
    STATIC_ASSERT_TYPE(int[3], arr);
    STATIC_ASSERT_TYPE(const int[3], carr);

    STATIC_ASSERT_TYPE(int(&)[3], rarr);
    STATIC_ASSERT_TYPE(const int(&)[3], crarr);
}

TEST(array_decays_to_pointer, should_deduce_for_non_const_arr)
{
    value<int*, int*>(arr);
    const_value<int*, int*const>(arr);
}

TEST(array_not_decays_to_pointer, should_deduce_for_non_const_arr)
{
    lvalue_reference<int[3], int(&)[3]>(arr);
    lvalue_reference_to_const<int[3], const int(&)[3]>(arr);
}

TEST(array_decays_to_pointer, should_deduce_for_const_arr)
{
    value<const int*, const int*>(carr);
    const_value<const int*, const int* const>(carr);
}

TEST(array_not_decays_to_pointer, should_deduce_for_const_arr)
{
    lvalue_reference<const int[3], const int(&)[3]>(carr);
    lvalue_reference_to_const<int[3], const int(&)[3]>(carr);
}

static void func(int, double) {}

TEST(function_decays_to_pointer, should_deduce_for_function)
{
    value<void(*)(int, double), void(*)(int, double)>(func);
    const_value<void(*)(int, double), void(*const)(int, double)>(func);
}

TEST(function_not_decays_to_pointer, should_deduce_for_function)
{
    lvalue_reference<void(int, double), void(&)(int, double)>(func);

    using non_const_ref = void(&)(int, double);

    lvalue_reference_to_const<void(int, double), const non_const_ref>(func);
    lvalue_reference_to_const<void(int, double), non_const_ref>(func);
}

namespace
{
    DEF_GENERIC_FUNC(brace_initializer(std::initializer_list<T> t))
    DEF_GENERIC_FUNC(const_brace_initializer(const std::initializer_list<T> t))
}

TEST(cpp98_initialization, should_be_deduce_type_normally)
{
    auto a = 2;
    auto b(2);

    STATIC_ASSERT_TYPE(int, a);
    STATIC_ASSERT_TYPE(int, b);
}

TEST(initializer_list, should_deduce_for_brace_initialization)
{
    brace_initializer<int, std::initializer_list<int>>({1, 2, 3});
    const_brace_initializer<int, const std::initializer_list<int>>({1, 2, 3});
}
