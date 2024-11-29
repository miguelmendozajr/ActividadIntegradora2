#include <catch2/catch_test_macros.hpp>
#include "func.h"


TEST_CASE("factorial") {
    REQUIRE(factorial(0) == 1);
}