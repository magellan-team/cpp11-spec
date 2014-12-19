#include <gtest/gtest.h>
#include <initializer_list>
#include <numeric>

template <typename T, typename C>
T sum(const C& c, T init = T())
{
    for(const auto &e : c)
    {
        init += e;
    }

    return init;
}

TEST(range_for, all_stl_containers_support_range_based_for)
{
    std::vector<int> v{1, 2, 3};

    ASSERT_EQ(6, sum<int>(v));
}

TEST(range_for, array_supports_range_based_for)
{
    int arr[] = {1, 2, 3};

    ASSERT_EQ(6, sum<int>(arr));
}

TEST(range_for, list_initializer_supports_range_based_for)
{
    auto list = {1, 2, 3};
    
    ASSERT_EQ(6, sum<int>(list));
}

namespace
{
    template <typename T, size_t MAX_NUM>
    struct FixedArray
    {
        FixedArray(std::initializer_list<T> list)
        { std::copy(list.begin(), list.end(), array); }

        void fill(const T& value)
        { std::fill(begin(), end(), value); }

        T* begin()
        { return std::begin(array); }

        T* end()
        { return std::end(array); }

        const T* begin() const
        { return std::begin(array); }

        const T* end() const
        { return std::end(array); }

    private:
        T array[MAX_NUM];
    };    
}

TEST(range_for, user_defined_type_support_range_for_only_if_begin_and_end_are_valid)
{
    FixedArray<int, 3> array{1, 2, 3};

    ASSERT_EQ(6, sum<int>(array));
}

TEST(range_for, modify_element_when_iterate_list)
{
    FixedArray<int, 3> array{1, 2, 3};

    for (auto &e : array)
    {
        e *= 2;
    }

    ASSERT_EQ(12, sum<int>(array));
}

TEST(range_for, use_const_reference_when_iterate_class_type)
{
    std::vector<std::string> sv;

    sv.emplace_back("c++98");
    sv.emplace_back("|");
    sv.emplace_back("c++11");

    ASSERT_EQ("c++98|c++11", sum<std::string>(sv));
}

