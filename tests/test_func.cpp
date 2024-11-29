/*
 * SonarQube, open source software quality management tool.
 * Copyright (C) 2008-2013 SonarSource
 * http://github.com/SonarOpenCommunity/sonar-cxx
 *
 * SonarQube is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * SonarQube is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#include <catch2/catch_test_macros.hpp>
#include "func.h"


TEST_CASE("factorial") {
    REQUIRE(factorial(0) == 1);

    // Edge case: factorial(1)
    REQUIRE(factorial(1) == 1);

    // Small values
    REQUIRE(factorial(2) == 2);       // 2! = 2
    REQUIRE(factorial(3) == 6);       // 3! = 6
    REQUIRE(factorial(4) == 24);      // 4! = 24
    REQUIRE(factorial(5) == 120);     // 5! = 120
    REQUIRE(factorial(6) == 720);     // 6! = 720
    REQUIRE(factorial(7) == 5040);    // 7! = 5040

    // Large values (ensure no overflow for reasonably large inputs)
    REQUIRE(factorial(10) == 3628800); // 10! = 3628800
    REQUIRE(factorial(12) == 479001600); // 12! = 479001600
}


TEST_CASE("contains code") {
    // Test case 1: Basic match
    const std::string transmission1 = "AAAAAA";
    const std::string code1 = "AAA";
    REQUIRE(containsCode(transmission1, code1) == 0);

    // Test case 2: Pattern appears at the end
    const std::string transmission2 = "AAAAAA";
    const std::string code2 = "AAA";
    REQUIRE(containsCode(transmission2, code2) == 3);

    // Test case 3: No match (pattern not found)
    const std::string transmission3 = "AAAAAA";
    const std::string code3 = "ZZZ";
    REQUIRE(containsCode(transmission3, code3) == -1);

    // Test case 4: Match exactly at the beginning
    const std::string transmission4 = "ABCDEF";
    const std::string code4 = "ABC";
    REQUIRE(containsCode(transmission4, code4) == 0);

    // Test case 5: Match at the middle
    const std::string transmission5 = "XYZABCDEF";
    const std::string code5 = "ABC";
    REQUIRE(containsCode(transmission5, code5) == 3);

    // Test case 6: Empty pattern (edge case)
    const std::string transmission6 = "XYZABCDEF";
    const std::string code6 = "";
    REQUIRE(containsCode(transmission6, code6) == 0);  // Empty pattern matches at the start

    // Test case 7: Empty content (edge case)
    const std::string transmission7 = "";
    const std::string code7 = "ABC";
    REQUIRE(containsCode(transmission7, code7) == -1);  // Non-empty pattern cannot match empty content

    // Test case 8: Single character pattern in a longer string
    const std::string transmission8 = "ABCDE";
    const std::string code8 = "D";
    REQUIRE(containsCode(transmission8, code8) == 3);

    // Test case 9: Multiple occurrences of the pattern
    const std::string transmission9 = "ABABABAB";
    const std::string code9 = "AB";
    REQUIRE(containsCode(transmission9, code9) == 0);  // First match at position 0

    // Test case 10: Large pattern (whole string is a match)
    const std::string transmission10 = "ABCDEF";
    const std::string code10 = "ABCDEF";
    REQUIRE(containsCode(transmission10, code10) == 0);  // Pattern matches the whole content
    
    // Test case 12: Pattern with repeating characters
    const std::string transmission12 = "AAAAAA";
    const std::string code12 = "AAA";
    REQUIRE(containsCode(transmission12, code12) == 0);

    // Test case 13: Single character pattern not found
    const std::string transmission13 = "BBBBBB";
    const std::string code13 = "A";
    REQUIRE(containsCode(transmission13, code13) == -1);
}
