#include <gtest/gtest.h>
#include <initializer_list>

TEST(range_for, all_stl_containers_support_range_based_for)
{
    std::vector<int> v{1, 2, 3};

    int sum = 0;
    for(auto i : v)
    {
        sum += i;
    }

    ASSERT_EQ(6, sum);
}

TEST(range_for, array_supports_range_based_for)
{
    int arr[] = {1, 2, 3};
   
    int sum = 0;
    for(auto i : arr)
    {
       sum += i;
    }

    ASSERT_EQ(6, sum);
}

TEST(range_for, list_initializer_supports_range_based_for)
{
    auto list = {1, 2, 3};
    
    int sum = 0;
    for(auto i : list)
    {
        sum += i;
    }
   
    ASSERT_EQ(6, sum);
}

namespace
{
    template <typename T, size_t MAX_NUM>
    struct FixedArray
    {
    	FixedArray(std::initializer_list<T> list)
    	{
    		std::copy(list.begin(), list.end(), array);
    	}

    	void fill(const T& value)
    	{
    		std::fill(begin(), end(), value);
    	}

        T* begin()
        {
        	return array;
        }

        T* end()
        {
        	return array + MAX_NUM;
        }

        const T* begin() const
        {
        	return array;
        }

        const T* end() const
        {
        	return array + MAX_NUM;
        }

    private:
        T array[MAX_NUM];
    };    
}

TEST(range_for, user_defined_type_support_range_for_only_if_begin_and_end_are_valid)
{
    FixedArray<int, 3> array{1, 2, 3};

    int sum = 0;
    for (auto e : array)
    {
    	sum += e;
    }

    ASSERT_EQ(6, sum);
}

TEST(range_for, modify_element_when_iterate_list)
{
    FixedArray<int, 3> array{1, 2, 3};

    for (auto &e : array)
    {
    	e *= 2;
    }

    int sum = 0;
    for (auto e : array)
    {
    	sum += e;
    }

    ASSERT_EQ(12, sum);
}

TEST(range_for, use_const_reference_when_iterate_class_type)
{
	std::vector<std::string> sv;

	sv.emplace_back("hello,");
	sv.emplace_back("world!");

	std::string result;
    for (const auto& e : sv)
    {
    	result += e;
    }

    ASSERT_EQ("hello,world!", result);
}

