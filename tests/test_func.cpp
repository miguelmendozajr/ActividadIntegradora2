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
    const std::string transmissionFile = "AAAAAA";
    const std::string codeFile = "z";

    REQUIRE( containsCode(transmissionFile, codeFile) == -1);
}