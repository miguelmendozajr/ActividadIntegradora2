#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

bool containsCode(const std::string& transmissionFile, const std::string& mcodeFile) {
    std::ifstream transmission(transmissionFile);
    std::ifstream mcode(mcodeFile);

    std::string transmissionContent((std::istreambuf_iterator<char>(transmission)),
                                     std::istreambuf_iterator<char>());
    std::string mcodeContent((std::istreambuf_iterator<char>(mcode)),
                             std::istreambuf_iterator<char>());

    return transmissionContent.find(mcodeContent) != std::string::npos;
}

bool isPalindrome(const std::string& str) {
    std::string reversedStr = str;
    std::reverse(reversedStr.begin(), reversedStr.end());
    return str == reversedStr;
}

std::pair<int, int> findLongestPalindrome(const std::string& transmissionFile) {
    std::ifstream transmission(transmissionFile);

    std::string transmissionContent((std::istreambuf_iterator<char>(transmission)),
                                     std::istreambuf_iterator<char>());

    int maxLength = 0;
    std::pair<int, int> longestPalindrome;

    for (int i = 0; i < transmissionContent.length(); i++) {
        for (int j = i + 1; j < transmissionContent.length(); j++) {
            std::string substring = transmissionContent.substr(i, j - i + 1);
            if (isPalindrome(substring) && substring.length() > maxLength) {
                maxLength = substring.length();
                longestPalindrome = std::make_pair(i + 1, j + 1);
            }
        }
    }

    return longestPalindrome;
}

std::pair<int, int> findLongestCommonSubstring(const std::string& transmission1File, const std::string& transmission2File) {
    std::ifstream transmission1(transmission1File);
    std::ifstream transmission2(transmission2File);

    std::string transmission1Content((std::istreambuf_iterator<char>(transmission1)),
                                     std::istreambuf_iterator<char>());
    std::string transmission2Content((std::istreambuf_iterator<char>(transmission2)),
                                     std::istreambuf_iterator<char>());

    int maxLength = 0;
    std::pair<int, int> longestCommonSubstring;

    for (int i = 0; i < transmission1Content.length(); i++) {
        for (int j = 0; j < transmission2Content.length(); j++) {
            int length = 0;
            while (transmission1Content[i + length] == transmission2Content[j + length]) {
                length++;
                if (i + length >= transmission1Content.length() || j + length >= transmission2Content.length()) {
                    break;
                }
            }
            if (length > maxLength) {
                maxLength = length;
                longestCommonSubstring = std::make_pair(i + 1, i + length);
            }
        }
    }

    return longestCommonSubstring;
}

int main() {
    std::string transmission1File = "/Users/edselcisneros/Documents/ActividadIntegradora/ActividadIntegradora1/transmission1.txt";
    std::string transmission2File = "/Users/edselcisneros/Documents/ActividadIntegradora/ActividadIntegradora1/transmission2.txt";
    std::string mcode1File = "/Users/edselcisneros/Documents/ActividadIntegradora/ActividadIntegradora1/mcode1.txt";
    std::string mcode2File = "/Users/edselcisneros/Documents/ActividadIntegradora/ActividadIntegradora1/mcode2.txt";
    std::string mcode3File = "/Users/edselcisneros/Documents/ActividadIntegradora/ActividadIntegradora1/mcode3.txt";

    // Part 1
    std::cout << std::boolalpha;
    std::cout << containsCode(transmission1File, mcode1File) << std::endl;
    std::cout << containsCode(transmission1File, mcode2File) << std::endl;
    std::cout << containsCode(transmission1File, mcode3File) << std::endl;
    std::cout << containsCode(transmission2File, mcode1File) << std::endl;
    std::cout << containsCode(transmission2File, mcode2File) << std::endl;
    std::cout << containsCode(transmission2File, mcode3File) << std::endl;

    // Part 2
    std::pair<int, int> longestPalindrome1 = findLongestPalindrome(transmission1File);
    std::pair<int, int> longestPalindrome2 = findLongestPalindrome(transmission2File);
    std::cout << longestPalindrome1.first << " " << longestPalindrome1.second << std::endl;
    std::cout << longestPalindrome2.first << " " << longestPalindrome2.second << std::endl;

    // Part 3
    std::pair<int, int> longestCommonSubstring = findLongestCommonSubstring(transmission1File, transmission2File);
    std::cout << longestCommonSubstring.first << " " << longestCommonSubstring.second << std::endl;

    return 0;
}