#include <type_traits>

#define ASSERT_TYPE(expect_type, actual_type)                                      \
  static_assert(std::is_same<expect_type, decltype(actual_type)>::value,           \
  "expect " #actual_type " with type '" #expect_type "', but static assert fail.")

