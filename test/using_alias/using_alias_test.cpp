#include <gtest/gtest.h>
#include <stack>
#include <list>
#include <array>
#include <map>
#include <unordered_map>
#include <assertion/type_assertion.h>

TEST(using_alias, can_be_equivalent_to_typedef)
{
    typedef std::unordered_map<int, int> IntHashMap_1;
    using IntHashMap_2 = std::unordered_map<int, int>;

    STATIC_ASSERT_SAME_TYPE(IntHashMap_1, IntHashMap_2);
}

TEST(using_alias, can_be_more_comprehensible_than_typedef)
{
    typedef int (*Functor1)(int, int);
    using Functor2 = int(*)(int, int);

    STATIC_ASSERT_SAME_TYPE(Functor1, Functor2);
}

namespace
{
    template <std::size_t N>
    using StringArray = std::array<std::string, N>;

    template <typename K, typename V>
    using GreaterMap = std::map<K, V, std::greater<K>>;
}

TEST(using_alias, can_be_used_for_partially_bound_template)
{
    StringArray<3> array {"c++98", "c++11"};

    ASSERT_EQ(std::string("c++98"), array[0]);
    ASSERT_EQ(std::string("c++11"), array[1]);
    ASSERT_EQ(std::string(""),      array[2]);
}

namespace
{
    template <typename T>
    struct LinkedStack
    {
        typedef std::stack<T, std::list<T>> type;
    };

    template <typename T>
    struct Station
    {
        typename LinkedStack<T>::type stack;
    };
}

TEST(dependent_types, must_be_preceded_by_typename)
{
    Station<int> station;

    STATIC_ASSERT_TYPE(Station<int>, station);
}

namespace
{
    template <typename T>
    using ArrayStack = std::stack<T, std::vector<T>>;

    template <typename T>
    struct Widget
    {
        ArrayStack<T> stack;
    };
}

TEST(using_alias, no_need_for_typename_vanishes)
{
    Widget<int> widget;

    STATIC_ASSERT_TYPE(Widget<int>, widget);
}

namespace cpp14
{
    template <class T>
    using remove_const_t = typename std::remove_const<T>::type;
}

TEST(using_alias, using_alias_is_simpler_than_typedef)
{
    STATIC_ASSERT_SAME_TYPE(int, std::remove_const<const int>::type);
    STATIC_ASSERT_SAME_TYPE(int, cpp14::remove_const_t<const int>);
}
