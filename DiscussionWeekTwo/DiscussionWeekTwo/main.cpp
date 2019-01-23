//
//  main.cpp
//  DiscussionWeekTwo
//
//  Created by Shawn Schwartz on 1/15/19.
//  Copyright © 2019 Shawn Schwartz. All rights reserved.
//

#include <iostream>
// #include <cstdlib>

using namespace std;

int FindDigitSum(int x)
{
     //first check if number is negative
     if (x < 0) { x = -1*x; }
     int digitSum = 0;
     while (x > 0) { digitSum += x % 10; x /= 10; }
     return digitSum;
}


int sum_nums(int x)
{
    int sum = 0;
    while (x != 0) {
        //sum = sum + x % 10;
        //x = x / 10;
        sum += x % 10;
        x /= 10;
    }
    return abs(sum);
}

int* GetDigitSumArr(int arr[], int arrSize)
{ // you always have to pass in the integer array size
    // we need to allocate memory for this new array
    //int digitSumArray[arrSize]; (this cant be done because it has to be known at compiletime,
    
    //so you have to dynamically allocate it
    // TODO: Deallocate later
    int* digitSumArr = new int[arrSize];
    for (int i = 0; i < arrSize; i++) {
        digitSumArr[i] = FindDigitSum(arr[i]);
    }
    
    return digitSumArr;

}

// another way to do it
void GetDigitSumArrTwo(int arr[], int arrSize, int *digitSumArr) // param3: given the pointer they want you to use to store the new array
// i.e., in main, you are going to allocate the memory yourself in main, whenever you pass in the pointer, youre going to assume that the memory is already allocated for you
{ // you always have to pass in the integer array size
    // we need to allocate memory for this new array
    //int digitSumArray[arrSize]; (this cant be done because it has to be known at compiletime,
    
    //so you have to dynamically allocate it
    for (int i = 0; i < arrSize; i++) {
        digitSumArr[i] = FindDigitSum(arr[i]);
    }
    
}

void PrintArr(int arr[], int arrSize)
{
    for (int i = 0; i < arrSize; i++) {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main()
{
    
    // Given an array of ints, return back an array of the same size such that each element in the array holds the sum of the digits for the integer at the corresponding index in the original array.
    
    // Subproblems
        // 1) sum the digits in an integer
        // 2) loop through array and call the summing the digits on the array elements
    
    cout << (101 % 10) << endl; //%10 will return the last digit of any positive number (i.e., 1 for 101)
    
    cout << sum_nums(-2021) << endl;
    
    cout << FindDigitSum(-2021) << endl;
    
    int arr[] = {-101, 2, 33, 2020};
    int arrSize = sizeof(arr) / sizeof(int);
    
    // for the second allocate func
    int* digitSumArrTwo = new int[arrSize]; // this is nicer because the allocation and deletion are in the same function, so you can see it 
    
    int *digitSumArr = GetDigitSumArr(arr, arrSize); //dynamically allocate memory
    
    GetDigitSumArrTwo(arr, arrSize, digitSumArrTwo);
    PrintArr(digitSumArrTwo, arrSize);
    
    PrintArr(digitSumArr, arrSize);
    
    // free up the memory
    delete[] digitSumArr; //[] b/c it is an array
    
    
    return 0;
}
