#include <gtest/gtest.h>
#include <assertion/type_assertion.h>

namespace
{
    auto i = 10;
}

TEST(lvalue, assignment_expr_that_return_ref_type)
{
    auto &&result = (i=10);
    STATIC_ASSERT_LVALUE_REF(result);

    auto &&sum = (i+=10);
    STATIC_ASSERT_LVALUE_REF(sum);
}

TEST(lvalue, subscript_expr_that_return_ref_type)
{
    int arr[] = {1, 2, 3};
    auto &&element = arr[2];
    STATIC_ASSERT_LVALUE_REF(element);
}

TEST(lvalue, prefix_increment_or_decrement_expr_return_noref_type)
{
    auto &&prefix = ++i;
    STATIC_ASSERT_LVALUE_REF(prefix);
}

