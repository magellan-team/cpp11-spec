#include <gtest/gtest.h>
#include "assertion/type_assertion.h"

namespace
{
    auto i = 10;
    const auto  ci = 10;
    const auto& cr = i;
    
    template <typename ExpectTemplateParamType, typename ExpectArgumentType, typename T>
    void lvalue_reference(T& t)
    {
        //ASSERT_TYPE(ExpectTemplateParamType, T);
        //ASSERT_TYPE(ExpectArgumentType, decltype(t));
    } 
}

TEST(lvalue_reference, should_deduce_for_non_const_obj)
{
    lvalue_reference<int, int&>(i);
}
