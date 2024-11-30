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
#include <fstream>
#include <sstream>
#include <string>

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

std::string readFileToString(const std::string& filePath) {
    std::ifstream file(filePath);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filePath);
    }

    std::ostringstream buffer;
    buffer << file.rdbuf(); // Read the file into the buffer
    return buffer.str();
}

TEST_CASE("contains code") {
    // Test case 1: Basic match

    const std::string transmission1 = "AAAAAA";
    const std::string code1 = "AAA";
    REQUIRE(containsCode(transmission1, code1) == 1);

    // Test case 3: No match (pattern not found)
    const std::string transmission3 = "AAAAAA";
    const std::string code3 = "ZZZ";
    REQUIRE(containsCode(transmission3, code3) == -1);

    // Test case 10: Large pattern (whole string is a match)
    const std::string transmission4 = "WERFD";
    const std::string code4 = "WERT";
    REQUIRE(containsCode(transmission4, code4) == -1);  // Pattern matches the whole content

    // Test case 10: Large pattern (whole string is a match)
    const std::string transmission10 = "ABCDEF";
    const std::string code10 = "ABCDEF";
    REQUIRE(containsCode(transmission10, code10) == 1);  // Pattern matches the whole content

    // Test case 13: Single character pattern not found
    const std::string transmission13 = "BBBBBB";
    const std::string code13 = "A";
    REQUIRE(containsCode(transmission13, code13) == -1);

    const std::string transmissionPath = "../transmission1.txt";
    const std::string codePath = "../mcode2.txt";

    std::string transmission;
    std::string code;

    try {
        transmission = readFileToString(transmissionPath);
        code = readFileToString(codePath);
    } catch (const std::exception& e) {
        FAIL("Error reading files: " << e.what());
    }

    // Test case 1: Match within transmission
    REQUIRE(containsCode(transmission, code) == -1);
}
