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

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <tuple>
#include <stdlib.h>
#include <string.h>
#include <cstring>

#include <cxxopts.hpp>
#include <fmt/format.h>
#include <nlohmann/json.hpp>
#include <spdlog/spdlog.h>

#include "config.hpp"
#include "func.h"

using namespace std; 

int main() {
    string transmission1File = "../transmission1.txt";
    string transmission2File = "../transmission2.txt";
    string mcode1File = "../mcode1.txt";
    string mcode2File = "../mcode2.txt";
    string mcode3File = "../mcode3.txt";

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
    cout<<endl<<"part3:"<<endl;
    tuple<int, int, string> longestCommonSubstring = findLongestCommonSubstring(transmission1File, transmission2File);
    cout << endl<<get<0>(longestCommonSubstring)<<endl<<get<1>(longestCommonSubstring)<<endl<<get<2>(longestCommonSubstring)<<endl;

    return 0;
}
