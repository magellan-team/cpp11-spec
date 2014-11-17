#include <gtest/gtest.h>
#include <initializer_list>
#include <array>
#include "assertion/type_assertion.h"

TEST(list_initialization, the_type_of_brace_initialization_is_std_initializer_list)
{
    auto list = {1, 3, 3};
    ASSERT_TYPE(std::initializer_list<int>, list);
}

TEST(list_initialization, build_in_type_supports_the_brace_initialization)
{
    const auto ci = {10};
    const auto cj{10};
}

TEST(list_initialization, c_style_array_supports_the_brace_initialization)
{
    const int arr1[] = {1, 2, 3};
    const int arr2[]{1, 2, 3};
    const int arr3[3]{1};
}

TEST(list_initialization, std_container_supports_the_brace_initialization)
{
    const std::vector<int> v1 = {1, 2, 3};
    const std::vector<int> v2{1, 2, 3};
}

TEST(list_initialization, std_array_supports_the_brace_initialization)
{
    std::array<int, 3> arr1 = {1, 2};
    std::array<int, 3> arr2{1, 2};
}

TEST(list_initialization, aggregate_class_supports_the_brace_initialization)
{
    struct Rectangle
    {
        int width;
        int height;
    };

    Rectangle rectangle1 = {1, 2};
    Rectangle rectangle2{1, 2};
}

TEST(list_initialization, non_aggregate_class_supports_the_brace_initialization)
{
    // 6. non-aggregate class
    struct Point
    {
        Point(int x, int y) : x(x), y(y)
        {}

    private:
        int x, y;
    };

    Point point1 = {1, 2};
    Point point2{1, 2};
}

TEST(list_initialization, array_in_the_class_supports_the_brace_initialization)
{
    struct Widget
    {
        Widget() : data1{1, 2, 3}, p{new int[3]{1, 2, 3}}
        {}

        Widget(std::initializer_list<int> list)
        {
            int i = 0;
            for(const auto e : list)
            {
                data3[i++] = e;
            }
        }

        ~Widget()
        {
            delete p;
        }

    private:
        const int data1[3] = {0};  // {0, 0, 0}
        const int data2[3]{1};     // {1, 0, 0}
        int data3[3]{0};

        const int* p{nullptr};
    };

    Widget widget1 = {1, 2, 3};
    Widget widget2{1, 2, 3};
}

TEST(list_initialization, return_value_support_the_brace_initialization)
{
    struct Line
    {
        Line(int start, int length) : start(start), length(length)
        {}

        static Line create(int start, int length)
        {
            return {start, length};
        }

    private:
        int start;
        int length;
    };
    
    Line::create(1, 10);
}

namespace
{
    int sum(const std::vector<int>& numbers)
    {
        int result = 0;
        for (auto num : numbers)
        {
            result += num;
        }
        return result;
    }
}


TEST(list_initialization, function_param_support_the_brace_initialization)
{
    ASSERT_EQ(6, sum({1, 2, 3}));
}

