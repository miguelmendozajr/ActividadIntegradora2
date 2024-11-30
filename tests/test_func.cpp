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

    const std::string transmission = "3Afe44c79f00b29F0CDC9ecd69d0D61186DAA1e356BB9c4d3472DBBbC9FA5ba74E00683AE1BB34725b352A5a72ac3add0b66c5C08562d434DE3Ee9C086621f5FA8DDC56fd38aFf3A2Ec9AE1dfBD400e14aBC4c7eDaf4C22c8E1f42d1FEd3B322957d46aD7c1e9cA31EBe4f3bfaa670fbCbbcEAcaDD9BDE9a6bD035Bcdbeae29dfe7acbc38A1fA453CDc8060378fCDf67A6DAD978dA32E9df4a9Ac662c5fDDf0BCeFDBcC9e12EFF8bB3BbA0cC0ff149A52BeBE24DDbbb3B1D6b3B30CB64DbDCceC04e2bC3ce30fA4a109CBDACA6AAc8B1dBbeF5b7485F8Bd4466CAacfF8d06F7EdCC3Aadb6B9Fb63bea9bba12B8f7cACcb4dd38C9a27ebdb111EbDBaCCC5C8eD32dD52EF25f544Ea09C177f1A2D703FfA8DD5f0a1deDCBb0BE7fcB008Cc372145e408fb2ECD85D679cbA66Cedf3ff2B7603CBBcAA65CC3B6F3e7eCe5d743BFD359d871C1E3f8aFC2fCdfa34491e2E29ac6af6e58A36bBEb5c6eA62cE5b6C6A8d2D879ac6FCc0b973875cd1dF7db08EbFEC6eaFB3C47D1FFcDafACee23F849Ae25B6C385dae2fc9E7beDCF145424cfb1Dadce8b8fFcBce7cd96192F4c4FFD2cd07FdD242Dd80D50e483EfBC4DEc5a375e2f4F6Ce7B0F7c7a11274EE26fc610902F7a3380D91FEf0a0e5b8DcC7B22caF25dEc85fFAE7a2FcbfbE7D03623fBabFD5bebA3245d0F0d27AfF8b25f130FFBa64d254BbBabe6485AbCb9a8de394FE6F79e33Adab3fAa1bFfFC3EB12CD553E38F6EFEf5b0c1b3d82cDc4Ec3b3CBd2CAd5fCa4b7E4e14D608D9bD2635FE5A039bB74A213795C99a2deb45F4aFeD65b851B21b8cBBB795aAA6E367A4b3A0BC7bBbA8B13Fb51541EdFDe6858D7BeB324da2c23d7C09a2546fC897BE59f49de65eA8efdce58Df0dcefa1927C1b0e963469ff5BA2Ca1c21fB2e85Ddddcd9b85d5BeDdEd8ED7826A9C2E6f6CEcF3DCfAA08d9dF2bCcAa1cCC17Ff9C5865F2c5eC5afedeeb28e459c5f0AB8D5D3e5E5eBD1D96d86F024ed9d5FC18BE0Ef5eAc05eCFAebc917533DE66aB6cDaf8d1B13D6a13A2Fa9D43Db194aacaC8BB44f8E0C99f67a77E9dcd09EdE6B9D6fcb943bB18d14db7eCf7e53Dc5bdCDcaAC7d27Baa403ac5CD3D53CBAD19fFb7cc5c3efEb40a19EcB89E2f8Fc8d3Ec375DBdA5F9e8ff5DE381E6CfEbb7AFEccF4EbFBdcb26e3CfAacf410321f97d5F00055b92CD82cAe0CC5EA5e52dc73a5FA9abFBCF049aDffe94C8a33eb5D2D2DAAB7Eb6f58678";
    const std::string code = "39EAbea2982Ca986F2ABC45882f573376dc031E14df7CC741afA7FeF5da25FFD5fdA32EEdeeaDC6b604E7314595186f72452ba84bbB944BAEEDaaaaC41A3b5e3D02Ae41D634fdF4dCE6D496Ba85AfB68aADf5cF0790CC1A4aDc0aBf9Da0bD282025e137DaeE8FC90bCdF1134feCfAa6b54edCC7E2C7c5Eedde55F6F816A9c7528BdFf1E29C212e891ECa643F77C2ABfafdaE842775fDf1D4E1d7FEaabaa898Cbe7bF4FeBdd0EFCaB6809E20b1c16f4dB964DcdBf26b7aE7f3D4163E662f2D012C7B2fa6ffCbfDcDDAA7C7ECFfa8ae92ED1768f4D7Fa1Ab9a055250ce8dB09a97cAebFCffa4EeC7f42d635221bcd41ff7ffcFa6C92ffCabb21Aff";

    // Test case 1: Match within transmission
    REQUIRE(containsCode(transmission, code) == -1);
}
