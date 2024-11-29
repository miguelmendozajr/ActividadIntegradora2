#pragma once

unsigned int factorial(unsigned int number);

std::vector<int> computeLPS(const std::string& pattern);

int containsCode(const std::string& transmissionFile, const std::string& mcodeFile);

std::tuple<int, int, std::string> findLongestPalindrome(const std::string& transmissionFile);

std::tuple<int, int, std::string> findLongestCommonSubstring(const std::string& transmission1File, const std::string& transmission2File);
