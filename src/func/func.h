#include <vector>
#include <string>
#include <tuple>

/// @brief Computes the factorial of a given number.
/// @param number The number for which the factorial is to be computed.
/// @return The factorial of the given number.
unsigned int factorial(unsigned int number);

/// @brief Computes the Longest Prefix Suffix (LPS) array for a given pattern.
/// The LPS array is used in the Knuth-Morris-Pratt (KMP) string matching algorithm.
/// @param pattern The string pattern to compute the LPS array for.
/// @return A vector of integers representing the LPS array.
std::vector<int> computeLPS(const std::string& pattern);

/// @brief Checks if a machine code (mcode) is present in a transmission.
/// Reads the contents of both files and determines if the mcode is a substring of the transmission.
/// @param transmissionContent The file containing the transmission data.
/// @param codeContent The file containing the machine code to search for.
/// @return 1 if the mcode is found in the transmission, -2 otherwise.
int containsCode(const std::string& transmissionContent, const std::string& codeContent);

/*
/// @brief Finds the longest palindromic substring in a given transmission file.
/// Reads the contents of the file and identifies the longest substring that is a palindrome.
/// @param transmissionFile The file containing the transmission data.
/// @return A tuple containing the start index, end index, and the longest palindromic substring.
std::tuple<int, int, std::string> findLongestPalindrome(const std::string& transmissionFile);


/// @brief Finds the longest common substring between two transmission files.
/// Reads the contents of both files and identifies the longest substring that appears in both.
/// @param transmission1File The file containing the first transmission data.
/// @param transmission2File The file containing the second transmission data.
/// @return A tuple containing the start index in the first file, start index in the second file, 
///         and the longest common substring.
std::tuple<int, int, std::string> findLongestCommonSubstring(const std::string& transmission1File, const std::string& transmission2File);
*/