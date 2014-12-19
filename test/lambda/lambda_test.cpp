#include <gtest/gtest.h>
#include <assertion/type_assertion.h>
#include <algorithm>

struct Lambda : testing::Test
{
    void SetUp() override
    {
        numbers.push_back(-10);
        numbers.push_back(0);
        numbers.push_back(10);
    }

protected:
    std::vector<int> numbers;
};

TEST_F(Lambda, should_be_able_to_call_lambda)
{
    auto found = std::find_if(numbers.cbegin(), numbers.cend(),
        [](const int value){ return value > 0 && value < 20; });

    ASSERT_NE(numbers.cend(), found);
}
