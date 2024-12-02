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

#define CATCH_CONFIG_MAIN

#include <catch2/catch_test_macros.hpp>
#include <vector>
#include "func.h"

TEST_CASE("factorial") {
    REQUIRE(factorial(0) == 1);
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(4) == 24);
};

TEST_CASE("Test 1") {
    const std::vector<std::vector<int>> distances = {
        {0, 16, 45, 32},
        {16, 0, 18, 21},
        {45, 18, 0, 7},
        {32, 21, 7, 0}
    };

    const std::vector<std::vector<int>> capacities = {
        {0, 48, 12, 18},
        {52, 0, 42, 32},
        {18, 46, 0, 56},
        {24, 36, 52, 0}
    };

    // Points
    const std::vector<Point> centers = {
        Point(200.0, 500.0),
        Point(300.0, 100.0),
        Point(450.0, 150.0),
        Point(520.0, 480.0)
    };


    NetworkOptimizer optimizer(4, distances, capacities, centers);
    int output = optimizer.calculateMaxFlow();

    REQUIRE(output == 78);

};

