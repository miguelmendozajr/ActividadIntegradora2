#include <catch2/catch_test_macros.hpp>
#include <tuple>
#include <string>
#include "func.h"


TEST_CASE("findLongestPalindrome") {
    string transmission1File = "/Users/miguelmendoza/Documents/Tec/4th/ActividadIntegradora/transmission1.txt";
    string mcode2File = "/Users/miguelmendoza/Documents/Tec/4th/ActividadIntegradora/mcode2.txt";

    REQUIRE(containsCode(transmission1File, mcode2File) == -1);
}
