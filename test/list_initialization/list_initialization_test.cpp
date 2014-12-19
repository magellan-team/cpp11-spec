#include <gtest/gtest.h>
#include <initializer_list>
#include <array>
#include "assertion/type_assertion.h"

TEST(initialization, direct_initialization)
{
    auto i(10);
    auto s("10");

    STATIC_ASSERT_TYPE(int, i);
    STATIC_ASSERT_TYPE(const char*, s);
}

TEST(initialization, copy_initialization)
{
    const auto i = 10;
    const auto s = std::string("10");

    STATIC_ASSERT_TYPE(const int, i);
    STATIC_ASSERT_TYPE(const std::string, s);
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
    auto i = {1};
    auto j{1};

    STATIC_ASSERT_TYPE(std::initializer_list<int>, i);
    STATIC_ASSERT_TYPE(std::initializer_list<int>, j);
}

TEST(list_initialization, build_in_type_supports_the_brace_initialization)
{
    const int ci = {10};
    const int cj{10};

    ASSERT_EQ(ci, cj);
}

namespace
{
    template <typename T, size_t N>
    inline size_t size_of_array(T (&arr)[N])
    {
        return N;
    }
}

TEST(list_initialization, c_style_array_supports_the_brace_initialization)
{
    const int arr1[] = {1, 2, 3};
    const int arr2[]{1, 2, 3};

    ASSERT_EQ(3, size_of_array(arr1));
    ASSERT_EQ(3, size_of_array(arr2));
}

TEST(list_initialization, the_size_brace_initialization_may_be_less_than_length_of_array)
{
    const int arr3[3]{10};

    ASSERT_EQ(10, arr3[0]);
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

namespace
{
    template <typename T>
    void assert_each_with_value(const std::vector<T>& values, const T& expected)
    {
        for (auto &value : values)
        {
            ASSERT_EQ(expected, value);
        }
    }
}

TEST(list_initialization, init_vector_using_parenthes_without_default_value)
{
    std::vector<int> v(10);

    ASSERT_EQ(10, v.size());
    assert_each_with_value(v, 0);
}

TEST(list_initialization, init_vector_using_parenthes_with_default_value)
{
    std::vector<int> v(10, 1);

    ASSERT_EQ(10, v.size());
    assert_each_with_value(v, 1);
}

TEST(list_initialization, init_vector_using_brace_with_only_one_element)
{
    std::vector<int> v{10};

    ASSERT_EQ(1, v.size());
    ASSERT_EQ(10, v[0]);
}

TEST(list_initialization, init_vector_using_brace_with_only_two_elements)
{
    std::vector<int> v{10, 1};

    ASSERT_EQ(2, v.size());
    ASSERT_EQ(10, v[0]);
    ASSERT_EQ(1,  v[1]);
}

TEST(list_initialization, init_vector_with_string_using_brace_with_only_one_element)
{
    std::vector<std::string> v{"hello"};

    ASSERT_EQ(1, v.size());
    ASSERT_EQ(std::string("hello"), v[0]);
}

TEST(list_initialization, init_vector_with_string_using_brace_with_only_two_elements)
{
    std::vector<std::string> v{"hello", "world"};

    ASSERT_EQ(2, v.size());
    ASSERT_EQ(std::string("hello"), v[0]);
    ASSERT_EQ(std::string("world"), v[1]);
}

// If list initialization isn’t possible,
// the compiler looks for other ways to
// initialize the object from the given values.
TEST(vector_string_initialization, using_brace_without_default_value)
{
    std::vector<std::string> v{10};

    ASSERT_EQ(10, v.size());
    assert_each_with_value(v, std::string(""));
}

TEST(vector_string_initialization, using_brace_with_default_value)
{
    std::vector<std::string> v{10, "hello"};

    ASSERT_EQ(10, v.size());
    assert_each_with_value(v, std::string("hello"));
}

TEST(list_initialization, std_array_supports_the_brace_initialization)
{
    std::array<int, 3> arr1{1, 2};

    ASSERT_EQ(3, arr1.size());
    ASSERT_EQ(0, arr1[2]);
}

TEST(list_initialization, aggregate_class_supports_the_brace_initialization)
{
    struct Rectangle
    {
        int width;
        int height;
    } r {1, 2};

    ASSERT_EQ(1,  r.width);
    ASSERT_EQ(2,  r.height);
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
    } point{1, 2};

    ASSERT_TRUE((Point(1, 2) == point));
}

TEST(list_initialization, array_in_the_class_supports_the_brace_initialization)
{
    struct Widget
    {
        Widget() : data1{1, 2}, p{new int[2]{3, 4}}
        {}

        ~Widget() { delete p; }

        void assertValid()
        {
            ASSERT_EQ(1, data1[0]);
            ASSERT_EQ(2, data1[1]);

            ASSERT_EQ(1, data2[0]);
            ASSERT_EQ(0, data2[1]);

            ASSERT_EQ(0, data3[0]);
            ASSERT_EQ(0, data3[1]);

            ASSERT_EQ(3, p[0]);
            ASSERT_EQ(4, p[1]);
        }

    private:
        const int data1[2]{0};  // {0, 0}
        const int data2[2]{1};  // {1, 0}
        const int data3[2]{0};  // {0, 0}

        const int* p{nullptr};
    };

    Widget().assertValid();
}

TEST(list_initialization, return_value_support_the_brace_initialization)
{
    struct Line
    {
        Line(int start, int length)
            : start(start), length(length)
        {}

        static Line create(int start, int length)
        {
            return {start, length};
        }

        void assert_valid()
        {
            ASSERT_EQ(1,  start);
            ASSERT_EQ(10, length);
        }

    private:
        int start;
        int length;
    };
    
    Line::create(1, 10).assert_valid();
}

namespace
{
    int sum(const std::initializer_list<int> numbers)
    {
        auto result = 0;
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

TEST(list_initialization, empty_braces_mean_no_arguments_but_not_an_empty_std_initializer_list)
{
    struct Rectangle
    {
        Rectangle() = default;

        Rectangle(const std::initializer_list<int> values)
            : invoked(true)
        {}

        bool wasInvoked() const
        { return invoked; }

    private:
        bool invoked = false;
    } rectangle1{}, rectangle2({}), rectangle3{{}};

    ASSERT_FALSE(rectangle1.wasInvoked());
    ASSERT_TRUE(rectangle2.wasInvoked());
    ASSERT_TRUE(rectangle2.wasInvoked());
}

TEST(list_initialization, braced_initializers_are_matched_to_std_initializer_list_parameters_if_at_all_possible)
{
    struct Widget
    {
        Widget(int, bool)
        {}

        Widget(const std::initializer_list<double>)
          : invoked(true)
        {}

        bool wasInvoked() const
        { return invoked; }

    private:
        bool invoked { false };
    } widget1(1, true), widget2{1, true};

    ASSERT_FALSE(widget1.wasInvoked());
    ASSERT_TRUE(widget2.wasInvoked());
}
