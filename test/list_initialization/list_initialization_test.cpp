#include <gtest/gtest.h>
#include <initializer_list>
#include <array>
#include "assertion/type_assertion.h"

TEST(initialization, direct_initialization)
{
    int i(10);
    std::string s("10");
}

TEST(initialization, copy_initialization)
{
    int i = 10;
    std::string s = "10";
}

TEST(initialization, brace_initialization)
{
    int i = {10};
    int j{10};

    std::string s = {"10"};
    std::string t{"10"};
}

TEST(list_initialization, the_type_of_brace_initialization_is_std_initializer_list)
{
    auto i(1);
    auto j = 1;
    STATIC_ASSERT_TYPE(int, i);
    STATIC_ASSERT_TYPE(int, j);

    auto m = {1};
    auto n{1};
    STATIC_ASSERT_TYPE(std::initializer_list<int>, m);
    STATIC_ASSERT_TYPE(std::initializer_list<int>, n);
}

TEST(list_initialization, build_in_type_supports_the_brace_initialization)
{
    const int ci = {10};
    const int cj{10};
}

TEST(list_initialization, c_style_array_supports_the_brace_initialization)
{
    const int arr1[] = {1, 2, 3};
    const int arr2[]{1, 2, 3};

    const int arr3[3]{1};

    ASSERT_EQ(0, arr3[1]);
    ASSERT_EQ(0, arr3[2]);
}

TEST(list_initialization, std_container_supports_the_brace_initialization)
{
    const std::vector<int> v1 = {1, 2, 3};
    const std::vector<int> v2{1, 2, 3};

    ASSERT_EQ(3, v1.size());
    ASSERT_EQ(3, v2.size());
}

TEST(list_initialization, std_array_supports_the_brace_initialization)
{
    std::array<int, 3> arr1 = {1, 2};
    std::array<int, 3> arr2{1, 2};

    ASSERT_EQ(3, arr1.size());
    ASSERT_EQ(0, arr1[2]);

    ASSERT_EQ(3, arr2.size());
    ASSERT_EQ(0, arr2[2]);
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

    ASSERT_EQ(1, rectangle1.width);
    ASSERT_EQ(2, rectangle2.height);
}

TEST(list_initialization, non_aggregate_class_supports_the_brace_initialization)
{
    struct Point
    {
        Point(int x, int y) : x(x), y(y)
        {}

        bool operator==(const Point& rhs) const
        {
            return x == rhs.x && y == rhs.y;
        }

    private:
        int x, y;
    };

    Point point1{1, 2};

    ASSERT_TRUE((Point(1, 2) == Point{1, 2}));
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
        int data3[3]{0};           // {0, 0, 0}

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

