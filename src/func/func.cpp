#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <tuple>
#include <stdexcept>

unsigned int factorial(unsigned int number) {
    unsigned int result = 1;
    for (unsigned int i = 2; i <= number; i++) {
        result *= i;
    }
    return result;
}

std::vector<int> computeLPS(const std::string& pattern) {
    if (pattern.empty()) return {};
    int m = pattern.length();
    std::vector<int> lps(m, 0);
    int len = 0, i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            len = (len != 0) ? lps[len - 1] : 0;
        }
    }
    return lps;
}

int containsCode(const std::string& transmissionFile, const std::string& mcodeFile) {
    std::ifstream transmission(transmissionFile);
    if (!transmission.is_open()) {
        throw std::runtime_error("Failed to open transmission file: " + transmissionFile);
    }

    std::ifstream mcode(mcodeFile);
    if (!mcode.is_open()) {
        throw std::runtime_error("Failed to open mcode file: " + mcodeFile);
    }

    std::string transmissionContent((std::istreambuf_iterator<char>(transmission)), std::istreambuf_iterator<char>());
    std::string mcodeContent((std::istreambuf_iterator<char>(mcode)), std::istreambuf_iterator<char>());

    if (transmissionContent.empty() || mcodeContent.empty()) {
        return -1; // Invalid data or no content
    }

    int n = transmissionContent.length();
    int m = mcodeContent.length();

    std::vector<int> lps = computeLPS(mcodeContent);

    int i = 0; // index for transmissionContent
    int j = 0; // index for mcodeContent

    while (i < n) {
        if (mcodeContent[j] == transmissionContent[i]) {
            j++;
            i++;
        }

        if (j == m) {
            return i - j + 1; // mcode found, return the starting index
        } else if (i < n && mcodeContent[j] != transmissionContent[i]) {
            j = (j != 0) ? lps[j - 1] : 0;
        }
    }

    return -1; // mcode not found
}


std::tuple<int, int, std::string> findLongestPalindrome(const std::string& transmissionContent) {

    int maxLength = 0, start = 0, end = 0;

    for (int i = 0; i < transmissionContent.size(); i++) {
        // Odd-length palindrome
        int left = i, right = i;
        while (left >= 0 && right < transmissionContent.size() && transmissionContent[left] == transmissionContent[right]) {
            int length = right - left + 1;
            if (length > maxLength) {
                maxLength = length;
                start = left;
                end = right;
            }
            left--;
            right++;
        }

        // Even-length palindrome
        left = i;
        right = i + 1;
        while (left >= 0 && right < transmissionContent.size() && transmissionContent[left] == transmissionContent[right]) {
            int length = right - left + 1;
            if (length > maxLength) {
                maxLength = length;
                start = left;
                end = right;
            }
            left--;
            right++;
        }
    }

    return std::make_tuple(start + 1, end + 1, transmissionContent.substr(start, maxLength));
}

std::tuple<int, int, std::string> findLongestCommonSubstring(const std::string& transmission1File, const std::string& transmission2File) {
    std::ifstream transmission1(transmission1File);
    if (!transmission1.is_open()) {
        throw std::runtime_error("Failed to open transmission1 file: " + transmission1File);
    }

    std::ifstream transmission2(transmission2File);
    if (!transmission2.is_open()) {
        throw std::runtime_error("Failed to open transmission2 file: " + transmission2File);
    }

    std::string transmission1Content((std::istreambuf_iterator<char>(transmission1)), std::istreambuf_iterator<char>());
    std::string transmission2Content((std::istreambuf_iterator<char>(transmission2)), std::istreambuf_iterator<char>());

    if (transmission1Content.empty() || transmission2Content.empty()) {
        return std::make_tuple(-1, -1, "");
    }

    int len1 = transmission1Content.size();
    int len2 = transmission2Content.size();
    std::vector<std::vector<int>> longest(len1 + 1, std::vector<int>(len2 + 1, 0));
    int maxLen = 0, endRow = -1;

    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (transmission1Content[i - 1] == transmission2Content[j - 1]) {
                longest[i][j] = longest[i - 1][j - 1] + 1;
                if (maxLen < longest[i][j]) {
                    maxLen = longest[i][j];
                    endRow = i;
                }
            }
        }
    }

    if (maxLen == 0) {
        return std::make_tuple(-1, -1, "");
    }

    std::string finalStr = transmission1Content.substr(endRow - maxLen, maxLen);
    return std::make_tuple(endRow - maxLen + 1, endRow, finalStr);
}
