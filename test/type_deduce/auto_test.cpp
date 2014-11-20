#include <gtest/gtest.h>
#include "assertion/type_assertion.h"

TEST(auto, uses_object_type_when_reference_as_initializer)
{
    auto i = 10;
    auto &r = i;
    auto a = r;
    
    STATIC_ASSERT_TYPE(int,  i);
    STATIC_ASSERT_TYPE(int&, r);
    STATIC_ASSERT_TYPE(int,  a);
}

TEST(auto, auto_ordinarily_ignores_top_level_const)
{
    const auto ci = 10;
    auto &cr = ci;
    
    auto a = ci;
    auto b = cr;

    STATIC_ASSERT_TYPE(const int,  ci);
    STATIC_ASSERT_TYPE(const int&, cr);
    
    STATIC_ASSERT_TYPE(int, a);
    STATIC_ASSERT_TYPE(int, b);
}

TEST(auto, auto_ordinarily_keep_low_level_const)
{
    const auto ci = 10;
    auto &cr = ci;
   
    auto d = &ci;
    auto e = &cr;

    STATIC_ASSERT_TYPE(const int*, d);
    STATIC_ASSERT_TYPE(const int*, e);
    
    auto *f = &ci;
    auto *g = &cr;

    STATIC_ASSERT_TYPE(const int*, f);
    STATIC_ASSERT_TYPE(const int*, g);
    
    const auto *h = &ci;
    const auto *j = &cr;

    STATIC_ASSERT_TYPE(const int*, h);
    STATIC_ASSERT_TYPE(const int*, j);
}

TEST(auto, top_level_const_in_the_initializer_was_kept_when_ask_for_a_reference_to_an_auto_deduced_type)
{
    const auto ci = 10;

    auto &cr1 = ci;
    const auto &cr2 = ci;

    STATIC_ASSERT_TYPE(const int&, cr1);    
    STATIC_ASSERT_TYPE(const int&, cr2);    
}

TEST(auto, auto_deduced_type_for_stl_container_iterator)
{
    std::vector<int> v{1, 2, 3};
    
    auto i = v.begin();
    auto ci = v.cbegin();
    auto ri = v.rbegin();
    auto rci = v.crbegin();

    STATIC_ASSERT_TYPE(std::vector<int>::iterator, i);
    STATIC_ASSERT_TYPE(std::vector<int>::const_iterator, ci);
    STATIC_ASSERT_TYPE(std::vector<int>::reverse_iterator, ri);
    STATIC_ASSERT_TYPE(std::vector<int>::const_reverse_iterator, rci);
}

namespace
{
    int sum(int a, int b)
    {
        return a + b;
    }
}

TEST(auto, auto_deduced_type_for_function)
{
    auto f = sum;
    STATIC_ASSERT_TYPE(int (*)(int, int), f);
    STATIC_ASSERT_TYPE(auto (*)(int, int) -> int, f);

    decltype(sum) *g = sum;
    STATIC_ASSERT_TYPE(int (*)(int, int), g);
    STATIC_ASSERT_TYPE(auto (*)(int, int) ->int, g);
}
