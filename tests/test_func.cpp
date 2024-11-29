/***************************************************************************************
 * File: main.cpp
 * Author: Miguel Mendoza Jaidar
 * Email: miguel.mendoza.jaidar@example.com
 * 
 * Project: [Project Name or Description]
 * 
 * Ownership: 
 * This file is the intellectual property of Miguel Mendoza Jaidar.
 * Unauthorized copying of this file, via any medium, is strictly prohibited.
 * 
 * License: 
 * Licensed under the MIT License. You may obtain a copy of the License at:
 * https://opensource.org/licenses/MIT
 * 
 * Usage:
 * Permission is hereby granted, free of charge, to any person obtaining a copy of 
 * this software and associated documentation files (the "Software"), to deal in 
 * the Software without restriction, including without limitation the rights to use, 
 * copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the 
 * Software, and to permit persons to whom the Software is furnished to do so, 
 * subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in all 
 * copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, 
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A 
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT 
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION 
 * OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 ***************************************************************************************/


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
    const std::string transmissionFile = "../transmission1.txt";
    const std::string codeFile = "../mcode2.txt";

    REQUIRE( containsCode(transmissionFile, codeFile)== -1);
}