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



TEST_CASE("Test 3") {
    const std::vector<std::vector<int>> capacities = {
        {0, 48, 12, 18},
        {52, 0, 42, 32},
        {18, 46, 0, 56},
        {24, 36, 52, 0}
    };

    REQUIRE(calculateMaxFlow(4, capacities) == 78);
};

TEST_CASE("Test 4") {
    const std::vector<Point> centers = {
        Point(200, 500),
        Point(300, 100),
        Point(450, 150),
        Point(520, 480)
    };

    const Point location(400, 300);

    Point output = findNearestCenter(centers, location);
    REQUIRE(output.x == 450 && output.y == 150);
};

