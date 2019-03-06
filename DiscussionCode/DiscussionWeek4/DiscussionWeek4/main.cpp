//
//  main.cpp
//  DiscussionWeek4
//
//  Created by Shawn Schwartz on 1/31/19.
//  Copyright © 2019 Shawn Schwartz. All rights reserved.
//

#include <iostream>
#include <vector>
#include <string>

// Task: Given a string containing numbers composed of digits, e.g. ,--> covert all numbers in the string to words
// you want to check if the subtracted value of char b-a is less than 9 or greater than 0
// use function isdigit (either cctype stdlib)
// Tasks we need to complete:
    // 1) Find the indices that correspond to the digits
    // 2) Extract the numbers composed of digits and convert them to their enlgish representation
    // 3) Split the original string at the digits and store them in a separate vector
    // 4) Combine the strings to form the final string -> for output

// Note: for checking the indices of consecutive numbers, if the next number indices isn't the next consecutive number, then that number sequence is over

bool isDigit(std::string s)
{
    return false;
}

std::vector<int> GetDigitIndices(std::string str)
{
    std::vector<int> vec;
    for (int i = 0; i < str.size(); i++)
    {
        if (isDigit(str.at(i)))
        {
            vec.push_back(i);
        }
    }
    
    return vec;
}

std::vector<std::string> GetNumStrings(std::vector<int> indices, std::string str)
{
    // have two indices (i,j)
    // substring (i, j-i+1) --> j-i = 0
    int i, j;
    i = j = 0;
    std::vector<std::string> digitwords;
    
    while (i < indices.size())
    {
        while (j + 1 < indices.size() && indices[j+1] - indices[j] == 1)
        {
            j = j + 1;
        }
        digitwords.push_back(str.substr(indices[i], j - i + 1));
        i = j + 1;
        j++;
    }
    return digitwords;
}

int main()
{
    GetDigitIndices("hi");
}
