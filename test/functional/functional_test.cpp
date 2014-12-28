#include <gtest/gtest.h>
#include <functional/functions.h>

namespace
{
    auto arr = {-1, -2, 3, 4};
}

TEST(higher_order_functions, map)
{
    std::vector<int> v;
    functional::map(arr, std::back_inserter(v), [](const int e) { return e > 0 ? e : -e; });

    ASSERT_EQ(1, v[0]);
    ASSERT_EQ(2, v[1]);
    ASSERT_EQ(3, v[2]);
    ASSERT_EQ(4, v[3]);
}

TEST(higher_order_functions, reduce)
{
    auto sum = functional::reduce(arr, 0, [](const int sum, const int e) { return sum + e; });

    ASSERT_EQ(4, sum);
}

TEST(higher_order_functions, filter)
{
    std::vector<int> v;
    functional::filter(arr, std::back_inserter(v), [](const int e) { return e > 0; });

    ASSERT_EQ(3, v[0]);
    ASSERT_EQ(4, v[1]);
}

TEST(higher_order_functions, each)
{
    auto sum = 0;
    functional::each(arr, [&sum](const int e) { sum += e; });

    ASSERT_EQ(4, sum);
}
