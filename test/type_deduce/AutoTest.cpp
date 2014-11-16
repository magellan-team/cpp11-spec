#include <gtest/gtest.h>
#include "base/Assertion.h"

TEST(AutoTest, uses_object_type_when_reference_as_initializer)
{
    auto i = 10, &r = i;
    auto a = r;
    
    ASSERT_TYPE(int,  i);
    ASSERT_TYPE(int&, r);
    ASSERT_TYPE(int,  a);
}

TEST(AutoTest, auto_ordinarily_ignores_top_level_const)
{
    const auto ci = 10;
    auto &cr = ci;
    
    auto a = ci;
    auto b = cr;

    ASSERT_TYPE(const int,  ci);
    ASSERT_TYPE(const int&, cr);
    
    ASSERT_TYPE(int, a);
    ASSERT_TYPE(int, b);
}

TEST(AutoTest, auto_ordinarily_keep_low_level_const)
{
    const auto ci = 10;
    auto &cr = ci;
   
    auto d = &ci;
    auto e = &cr;

    ASSERT_TYPE(const int*, d);
    ASSERT_TYPE(const int*, e);
    
    auto *f = &ci;
    auto *g = &cr;

    ASSERT_TYPE(const int*, f);
    ASSERT_TYPE(const int*, g);
    
    const auto *h = &ci;
    const auto *j = &cr;

    ASSERT_TYPE(const int*, h);
    ASSERT_TYPE(const int*, j);
}

TEST(AutoTest, top_level_const_in_the_initializer_was_kept_when_ask_for_a_reference_to_an_auto_deduced_type)
{
    const auto ci = 10;

    auto &cr1 = ci;
    const auto &cr2 = ci;

    ASSERT_TYPE(const int&, cr1);    
    ASSERT_TYPE(const int&, cr2);    
}

