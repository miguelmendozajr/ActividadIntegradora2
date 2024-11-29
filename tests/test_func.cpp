#include <catch2/catch_test_macros.hpp>
#include <tuple>
#include <string>
#include "func.h"


TEST_CASE("contains code") {
    REQUIRE(containsCode("abcabcabc", "abc") == 1);  // Match at index 1
    REQUIRE(containsCode("aaaaa", "aaa") == 1);      // Overlapping match
    REQUIRE(containsCode("abcdef", "xyz") == -1);    // No match
    REQUIRE(containsCode("", "abc") == -1);          // Empty transmission
    REQUIRE(containsCode("abc", "") == -1);          // Empty mcode
}