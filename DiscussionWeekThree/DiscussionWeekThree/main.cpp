//
//  main.cpp
//  DiscussionWeekThree
//
//  Created by Shawn Schwartz on 1/22/19.
//  Copyright © 2019 Shawn Schwartz. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>

// Delimiting string with **
// Create an array of appropriate size by counting the stars in the string
// Extra substrings corresponding to the marked words
// mark the indices of the * characters and store in a vector/array ("This is a *string*) --> substr(8, 15-8) (starting index, num of chars)
// Loop through and extract words between indices

std::vector<int> FindCharIndices(const std::string toSearch, char delimiter)
{
    std::vector<int> indices;
    for (int i = 0; i < toSearch.size(); i++)
        if (toSearch[i] == delimiter)
            indices.push_back(i);
    return indices;
}

void PrintVector(const std::vector<int> vec)
{
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl;
}

void PrintVector(const std::vector<std::string> vec)
{
    for (int i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl;
}

std::vector<std::string> ExtractSubstrings(const std::string toSearch, const std::vector<int> indices)
{
    std::vector<std::string> stringsVec;
    for (int i = 0; i + 1 < indices.size(); i++)
    {
        int startIndex = indices[i] + 1; // because we want the character that is after the star
        int stringSize = indices[i + 1] - indices[i] - 1;
        std::string substr = toSearch.substr(startIndex, stringSize);
        stringsVec.push_back(substr);
        
        // Need to skip over the second star (that doesn't mark the beginning of a word (the end))
        i++;
    }
    return stringsVec;
}

int main()
{
//    std::string input;
//    std::cout << "Please enter a string: ";
//    getline(std::cin, input);
//
//    int a_size = (int)std::count(input.begin(), input.end(), '*') / 2;
    
    std::string str = "This is a string *with* stars, marking *   words* *a* *";
//    for (int i = 0; i < str.size(); i++)
//        std::cout << i << ": " << str[i] << std::endl;
    
    std::vector<int> indices = FindCharIndices(str, '*');
    
    //PrintVector(indices);
    std::cout << str << std::endl;
    std::vector<std::string> newStr = ExtractSubstrings(str, indices);
    PrintVector(newStr);
    return 0;
}
