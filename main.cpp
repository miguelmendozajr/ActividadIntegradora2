#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>

using namespace std; 

vector<int> computeLPS(const string& pattern) {
    int m = pattern.length();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = lps[len - 1];
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

int containsCode(const string& transmissionFile, const string& mcodeFile) {
    ifstream transmission(transmissionFile);
    ifstream mcode(mcodeFile);

    string transmissionContent((istreambuf_iterator<char>(transmission)), istreambuf_iterator<char>());
    string mcodeContent((istreambuf_iterator<char>(mcode)), istreambuf_iterator<char>());

    int n = transmissionContent.length();
    int m = mcodeContent.length();

    vector<int> lps = computeLPS(mcodeContent);

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
            if (j != 0) {
                j = lps[j - 1];
            } else {
                i++;
            }
        }
    }

    return -1; // mcode not found
}

tuple<int, int, string> findLongestPalindrome(const string& transmissionFile) {
    ifstream transmission(transmissionFile);

    string transmissionContent((istreambuf_iterator<char>(transmission)),
                                     istreambuf_iterator<char>());

    int maxLength = 0;
    int start = 0;
    int end = 0;
    
    for (int i = 0; i < transmissionContent.size(); i++){
        // odd
        int left = i;
        int right = i;
        while (left >= 0 && right < transmissionContent.size() && transmissionContent[left] == transmissionContent[right]){
            int length = right - left + 1;
            if (length > maxLength){
                maxLength = length;
                start = left;
                end = right;
            }
            left--;
            right++;
        }

        // even 
        left = i;
        right = i + 1;
        while (left >= 0 && right < transmissionContent.size() && transmissionContent[left] == transmissionContent[right]){
            int length = right - left + 1;
            if (length > maxLength){
                maxLength = length;
                start = left;
                end = right;
            }
            left--;
            right++;
        }
    }
   return make_tuple(start + 1, end + 1, transmissionContent.substr(start, maxLength));
}

// TODO: Use LCS algorithm
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


// TODO: Adapt functions output
int main() {
    string transmission1File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/transmission1.txt";
    string transmission2File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/transmission2.txt";
    string mcode1File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/mcode1.txt";
    string mcode2File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/mcode2.txt";
    string mcode3File = "/Users/miguelmendoza/Documents/Tec/4th/DSA/ActividadIntegradora/mcode3.txt";

    vector<string> transmissionFiles = {transmission1File, transmission2File};
    vector<string> codeFiles = {mcode1File, mcode2File, mcode3File};
    
    // Part 1
    for (int i = 0; i < transmissionFiles.size(); i++){
        for (int j = 0; j < codeFiles.size(); j++){
            int index = containsCode(transmissionFiles[i], codeFiles[j]);
            if (index == -1){
                cout << "false" << endl;
            } else {
                cout << "true" << " " << index << endl;
            }

        }
    }

    // Part 2
    for (int i = 0; i < transmissionFiles.size(); i++){
        tuple<int, int, string> result = findLongestPalindrome(transmissionFiles[i]);
        int startIndex = get<0>(result);
        int endIndex = get<1>(result);
        string longestPalindrome = get<2>(result);
        cout << startIndex << " " << endIndex << " " << longestPalindrome << endl;
    }

    // Part 3
    pair<int, int> longestCommonSubstring = findLongestCommonSubstring(transmission1File, transmission2File);
    cout << longestCommonSubstring.first << " " << longestCommonSubstring.second << endl;

    return 0;
}