#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

using namespace std; 

bool containsCode(const string& transmissionFile, const string& mcodeFile) {
    ifstream transmission(transmissionFile);
    ifstream mcode(mcodeFile);

    string transmissionContent((istreambuf_iterator<char>(transmission)),
                                     istreambuf_iterator<char>());
    string mcodeContent((istreambuf_iterator<char>(mcode)),
                             istreambuf_iterator<char>());

    return transmissionContent.find(mcodeContent) != string::npos;
}

bool isPalindrome(const string& str) {
    string reversedStr = str;
    reverse(reversedStr.begin(), reversedStr.end());
    return str == reversedStr;
}

pair<int, int> findLongestPalindrome(const string& transmissionFile) {
    ifstream transmission(transmissionFile);

    string transmissionContent((istreambuf_iterator<char>(transmission)),
                                     istreambuf_iterator<char>());

    int maxLength = 0;
    pair<int, int> longestPalindrome;

    for (int i = 0; i < transmissionContent.length(); i++) {
        for (int j = i + 1; j < transmissionContent.length(); j++) {
            string substring = transmissionContent.substr(i, j - i + 1);
            if (isPalindrome(substring) && substring.length() > maxLength) {
                maxLength = substring.length();
                longestPalindrome = make_pair(i + 1, j + 1);
            }
        }
    }

    return longestPalindrome;
}

pair<int, int> findLongestCommonSubstring(const string& transmission1File, const string& transmission2File) {
    ifstream transmission1(transmission1File);
    ifstream transmission2(transmission2File);

    string transmission1Content((istreambuf_iterator<char>(transmission1)),
                                     istreambuf_iterator<char>());
    string transmission2Content((istreambuf_iterator<char>(transmission2)),
                                     istreambuf_iterator<char>());

    int maxLength = 0;
    pair<int, int> longestCommonSubstring;

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
                longestCommonSubstring = make_pair(i + 1, i + length);
            }
        }
    }

    return longestCommonSubstring;
}

int main() {
    string transmission1File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/ActividadIntegradora1/transmission1.txt";
    string transmission2File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/ActividadIntegradora1/transmission2.txt";
    string mcode1File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/ActividadIntegradora1/mcode1.txt";
    string mcode2File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/ActividadIntegradora1/mcode2.txt";
    string mcode3File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/ActividadIntegradora1/mcode3.txt";

    // Part 1
    cout << boolalpha;
    cout << containsCode(transmission1File, mcode1File) << endl;
    cout << containsCode(transmission1File, mcode2File) << endl;
    cout << containsCode(transmission1File, mcode3File) << endl;
    cout << containsCode(transmission2File, mcode1File) << endl;
    cout << containsCode(transmission2File, mcode2File) << endl;
    cout << containsCode(transmission2File, mcode3File) << endl;

    // Part 2
    pair<int, int> longestPalindrome1 = findLongestPalindrome(transmission1File);
    pair<int, int> longestPalindrome2 = findLongestPalindrome(transmission2File);
    cout << longestPalindrome1.first << " " << longestPalindrome1.second << endl;
    cout << longestPalindrome2.first << " " << longestPalindrome2.second << endl;

    // Part 3
    pair<int, int> longestCommonSubstring = findLongestCommonSubstring(transmission1File, transmission2File);
    cout << longestCommonSubstring.first << " " << longestCommonSubstring.second << endl;

    return 0;
}