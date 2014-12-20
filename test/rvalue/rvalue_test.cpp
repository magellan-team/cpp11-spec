#include <gtest/gtest.h>
#include <assertion/type_assertion.h>

TEST(rvalue, literal_constant)
{
    auto &&i = 10;
    STATIC_ASSERT_RVALUE_REF(i);

    auto &&b = true;
    STATIC_ASSERT_RVALUE_REF(b);

    auto &&d = 0.0;
    STATIC_ASSERT_RVALUE_REF(d);

    auto &&f = 0.0f;
    STATIC_ASSERT_RVALUE_REF(f);
}

namespace
{
    auto i = 10;
}

TEST(rvalue, arithmetic_expr_return_noref_type)
{
    auto &&sum = i + 10;
    STATIC_ASSERT_RVALUE_REF(sum);
}

TEST(rvalue, relation_expr_return_noref_type)
{
    auto &&less = i < 10;
    STATIC_ASSERT_RVALUE_REF(less);
}

TEST(rvalue, postfix_increment_or_decrement_expr_return_noref_type)
{
    auto &&postfix = i++;
    STATIC_ASSERT_RVALUE_REF(postfix);
}

TEST(rvalue, bitwise_expr_return_noref_type)
{
    auto &&bitwise = i & 0xFF;
    STATIC_ASSERT_RVALUE_REF(bitwise);
}

TEST(rvalue, conversion_expr_return_noref_type)
{
    auto &&conversion = static_cast<short>(i);
    STATIC_ASSERT_RVALUE_REF(conversion);
}

TEST(rvalue, lambda_expr)
{
    auto &&lambda = [](){ return false; };
    STATIC_ASSERT_RVALUE_REF(lambda);
}

TEST(rvalue, std_move)
{
    auto &&rvalue = std::move(i);
    STATIC_ASSERT_RVALUE_REF(rvalue);
}

TEST(rvalue, functions_that_return_noref_type)
{
    auto &&ptr = std::make_shared<int>(10);
    STATIC_ASSERT_RVALUE_REF(ptr);
}

namespace
{
    std::string&& operator+(std::string& lhs, const std::string& rhs)
    {
        lhs += rhs;
        return std::move(lhs);
    }
}

TEST(rvalue, functions_that_return_rvalue_ref)
{
    auto &&str = std::string("c++") + "11";
    STATIC_ASSERT_RVALUE_REF(str);
}

namespace
{
    struct Foo
    {
        Foo() {};

        const std::string& getQualifier() const &
        {
            qualifier += "const lvalue ref qualifier";
            return qualifier;
        }

        std::string& getQualifier() &
        {
            qualifier += "lvalue ref qualifier";
            return qualifier;
        }

        std::string&& getQualifier() &&
        {
            qualifier += "rvalue ref qualifier";
            return std::move(qualifier);
        }

    private:
        mutable std::string qualifier = "";
    };
}

TEST(rvalue, const_lvalue_ref_qualifier)
{
    const Foo cfoo;
    ASSERT_EQ(std::string("const lvalue ref qualifier"), cfoo.getQualifier());
}

TEST(rvalue, lvalue_ref_qualifier)
{
    Foo foo;
    ASSERT_EQ(std::string("lvalue ref qualifier"), foo.getQualifier());
}

TEST(rvalue, rvalue_ref_qualifier)
{
    ASSERT_EQ(std::string("rvalue ref qualifier"), Foo().getQualifier());
}
