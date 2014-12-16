#include <gtest/gtest.h>
#include "assertion/type_assertion.h"
#include <deque>

TEST(decltype, returns_the_type_of_that_variable_including_top_level_const_and_references)
{
    const auto ci = 10;
    auto &cr = ci;

    decltype(ci) a = ci;
    decltype(cr) b = ci;

    STATIC_ASSERT_TYPE(const int,  a);
    STATIC_ASSERT_TYPE(const int&, b);
}

TEST(decltype, with_double_parentheses_is_always_reference_type)
{
    auto i = 10;
    const auto ci = 20;

    decltype((i))  a = i;
    decltype((ci)) b = ci;
    
    STATIC_ASSERT_TYPE(int&, a);
    STATIC_ASSERT_TYPE(const int&, b);
}

namespace
{
#define AT(i) std::forward<Container>(c)[i]

    template <typename Container, typename T>
    auto modify_last(Container&& c, const T& v) -> decltype(AT(c.size()))
    {
        AT(c.size()) = v;
        return AT(c.size());
    }

    std::deque<int> make_deque()
    {
        return std::deque<int>{1, 2, 3};
    }

    std::deque<int>& get_exist_deque()
    {
        static std::deque<int> queue{1, 2, 3};
        return queue;
    }
}

TEST(decltype, return_type_depends_on_its_parameter_types)
{
    auto e = modify_last(make_deque(), 10);
    ASSERT_EQ(10, e);

    auto& f = modify_last(get_exist_deque(), 10);
    ASSERT_EQ(10, f);
}
