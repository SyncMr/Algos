#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>        // std::fill_n
#include <queue>            // Priority Queue
#include <typeinfo>         // typeid
using namespace std;

/*
 * PROBLEM 1. Given two strings, find the first non matching character
 * bool     findFirstNonMatchingChar(string s1, string s2, char& result)
 *
 * PROBLEM 2: Find the unique character present in a string
 * char     findUniqueChar(string str)
 *
 * PROBLEM 3: Count the number of islands in a 2D matrix
 * uint32_t countConnectedIslands(int** twoDmat, uint32_t rows, uint32_t cols)
 *
 * PROBLEM 4: Given a input stream of numbers, compute the median after each entry
 * int      medianOfStreams(int number, maxHeap, minHeap)
 *
 * PROBLEM 5. Find the max sub array sum
 * int      maxSubArraySum(int arr[], int num)
 *
 * PROBLEM 5b. Find the max sub array product
 * int maxProduct(vector<int>& nums)
 * 
 * PROBLEM 6. Coin change problem
 * uint32_t minCoinChangeRec(uint32_t coins[], uint32_t num, uint32_t val)
 *
 * PROBLEM 7. Print Matrix Diagonally
 * void printMatrixDiagonally(int** twoDMatrix, uint32_t rows, uint32_t cols)
 *
 * PROBLEM 8. Given a string of 1s and 0s with '?' in between. A '?' can be either one or zero.
 * void printCombinationOnesZeros(string str, uint32_t stIdx, uint32_t lastQMarkPos)
 *
 * PROBLEM 9. Given an integer x, find ONE digit who is equal to its adjacent digits,
 * int largestNumByRemovingDup(int number)
 *
 * PROBLEM 10. Find Equilibrium Index of an array. Sum of left elements = Sum of Right elements
 * unint32_t equilibriumIndex(vector<int> nums)
 *
 */

// ------------------------------------------------------------------------------------------------
// PROBLEM 1. Given two strings, find the first non matching character
//            hello
//            hexllo
//            Ans: x
// Find the first non-match character in two strings.
// ------------------------------------------------------------------------------------------------
bool findFirstNonMatchingChar(string s1, string s2, char& result)
{
    uint32_t shortLen = (s1.length() < s2.length() ? s1.length() : s2.length());
    uint32_t i = 0;

    if (s1.empty() && s2.empty())
    {
        return false;
    }

    if (s1.empty())
    {
        result = s2[0];
        return true;
    }

    if (s2.empty())
    {
        result = s1[0];
        return true;
    }

    for (; i < shortLen; i++)
    {
        if (s1[i] != s2[i])
        {
            // Found a mismatch. Either s1[i] or s2[i]
            uint32_t x = i + 1;
            uint32_t y = i + 1;

            // Find first occurence of s2[i] in s1
            for (; x < shortLen; x++)
            {
                if (s1[x] == s2[i])
                {
                    break;
                }
            }    

            // Find first occurence of s1[i] in s2
            for (; y < shortLen; y++)
            {
                if (s2[y] == s1[i])
                {
                    break;
                }
            }

            if (x < y)
            {
                result = s1[i];
                return true;
            }
            if ( x > y)
            {
                result = s2[i];
                return true;
            }
        }
    }

    // If string 1 is bigger then return s1[i]
    if (i < s1.length())
    {
        result = s1[i];
        return true;
    }

    // If string 2 is bigger then return s2[i]
    if (i < s2.length())
    {
        result = s2[i];
        return true;
    }

    return false;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 2: Find the unique character present in a string
//            hlllhabcdedcba
//            Ans: e
// ------------------------------------------------------------------------------------------------
struct uniqChar
{
    bool isPresent;
    uint32_t index;
};

char findUniqueChar(string str)
{
    if (str.empty())
    {
        return str[0];
    }

    uint32_t minIndex = INT_MAX;
    unordered_map<char, uniqChar> charMap;

    for (uint32_t i = 0; i < str.length(); i++)
    {
        auto itr = charMap.find(str[i]);
        if (itr != charMap.end())
        {
            itr->second.isPresent = true;
        }
        else
        {
            uniqChar temp{false, i};
            charMap[str[i]] = temp;
        }
    }

    //for (unordered_map<char, uniqChar>::iterator itr = charMap.begin(); itr != charMap.end(); itr++)
    for (auto it = charMap.begin(); it != charMap.end(); it++)
    {

        if (!(it->second).isPresent)
        {
            if ((it->second).index < minIndex)
            {
                minIndex = it->second.index;
            }
        }
    }

    // VERY IMP: What if we don't have a Unique Char. Min index could be infinity.
    if (minIndex < str.length())
    {
        return str[minIndex];
    }
    else
    {
        // Return NULL if nothing is present.
        return 0;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 3: Count the number of islands in a 2D matrix
// ------------------------------------------------------------------------------------------------
template <size_t rows, size_t cols>
void printTwoDMatrix(int (&twoDmat)[rows][cols])
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << twoDmat[i][j] << ", ";
        }
        cout << endl;
    }
}

template <typename T>
void printTwoDPtrToPtr(T** array, uint32_t rows, uint32_t cols)
{
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            cout << array[i][j] << ", ";
        }
        cout << endl;
    }
    cout << endl;
}

int rowDirection[8] = {-1, -1, -1, 0 , 0, 1 , 1, 1};
int colDirection[8] = {-1, 0 , 1 , -1, 1, -1, 0, 1};

bool isValid(int** twoDmat, int row, int col, bool** visited, uint32_t maxRows, uint32_t maxCols)
{
    if (row < 0 || col < 0 || row >= maxRows || col >= maxCols)
    {
        return false;
    }

    // VERY IMP:
    // If we have already seen this, then we shouldn't go further deep. So return false;
    if (visited[row][col])
    {
        return false;
    }

    return (twoDmat[row][col] == 1);
}

void dfs(int** twoDmat, uint32_t row, uint32_t col, bool** visited, uint32_t maxRows, uint32_t maxCols)
{
    visited[row][col] = true;
    
    for (uint32_t i = 0; i < 8; i++)
    {
        int newRow = row + rowDirection[i];
        int newCol = col + colDirection[i];

        // We need maxRows and maxCols to find the size of the matrix.
        if (isValid(twoDmat, newRow, newCol, visited, maxRows, maxCols))
        {
            // newRow and newCol will be a positive number and within the range
            dfs(twoDmat, newRow, newCol, visited, maxRows, maxCols);
        }
    }
}

uint32_t countConnectedIslands(int** twoDmat, uint32_t rows, uint32_t cols)
{
    uint32_t numIslands = 0;
    bool **visited = new bool*[rows];

    // Initialize a Visited bool array
    for (uint32_t i = 0; i < rows; i++)
    {
        visited[i] = new bool[cols];
    }

    // Set all values of bool array to false;
    for (uint32_t i = 0; i < rows; i++)
    {
        for (uint32_t j = 0; j < cols; j++)
        {
            visited[i][j] = false;
        }
    }

    for (int x = 0; x < rows; x++)
    {
        for (int y = 0; y < cols; y++)
        {
            // IMP: go DFS only when we have a 1.
            if (visited[x][y] == false && twoDmat[x][y] == 1)
            {
                dfs(twoDmat, x, y, visited, rows, cols);
                numIslands++;
            }
        }
    }

    return numIslands;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 4: Given a input stream of numbers, compute the median after each entry
//            hlllhabcdedcba
//            Ans: e
// ------------------------------------------------------------------------------------------------

template <typename T>
void printHeap(T myHeap)
{
    while (!myHeap.empty())
    {
        cout << myHeap.top() << " ";
        myHeap.pop();
    }
    cout << endl;
}

int medianOfStreamsHeap(int element, priority_queue<int>& desHeap, priority_queue<int, std::vector<int>, std::greater<int> >& ascHeap)
{
    int topDesHeap = desHeap.top();
    int topAscHeap = ascHeap.top();

    // If the next element is bigger than the first element in Descending heap then it should
    // go to the ascending heap.
    if (element > desHeap.top())
    {
        ascHeap.push(element);

        // Heapify
        if (ascHeap.size() - desHeap.size() > 1)
        {
            desHeap.push(ascHeap.top());
            ascHeap.pop();
        }
    }
    else
    {
        desHeap.push(element);

        // Heapify if desHeap get more elements
        if (desHeap.size() - ascHeap.size() > 1)
        {
            ascHeap.push(desHeap.top());
            desHeap.pop();
        }
    }
}

int medianOfStreams(int numbers[], uint32_t size)
{
    priority_queue<int, std::vector<int>, std::greater<int> > ascHeap;
    priority_queue<int> desHeap;

    if (size < 2)
    {
        return 0;
    }

    if (numbers[0] > numbers[1])
    {
        ascHeap.push(numbers[0]);
        desHeap.push(numbers[1]);
    }
    else
    {
        desHeap.push(numbers[0]);
        ascHeap.push(numbers[1]);
    }

    // Put each new number into the heap as we get
    for (uint32_t i = 2; i < size; i++)
    {
        medianOfStreamsHeap(numbers[i], desHeap, ascHeap);
    }

    cout << endl << "Descending Heap: ";
    printHeap(desHeap);

    cout << endl << "Ascending Heap : ";
    printHeap(ascHeap);

    // To calculate the median get the top from both the heaps and find the median of them
    // If both heaps are of same size, Median will be the average.
    // Else median element will be the element of the larger heap
    if (ascHeap.size() == desHeap.size())
    {
        return ((ascHeap.top() + desHeap.top()) / 2);
    }
    else if (ascHeap.size() > desHeap.size())
    {
        return ascHeap.top();
    }
    else
    {
        return desHeap.top();
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5. Find the max sub array sum
//            -2 -3 4 -1 -2 1 5 -3
//            Ans: 7
// ------------------------------------------------------------------------------------------------
int maxSubArraySum(int arr[], int num)
{
    int curSum = 0;
    // VERY IMP. Else it will fail when just {-1} is passed.
    int maxSum = INT_MIN;

    for (uint32_t i = 0; i < num; i++)
    {
        curSum = max(arr[i], arr[i] + curSum);
        maxSum = max(curSum, maxSum);
    }

    return maxSum;
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 5b. Find the max sub array product
//            -2 -3 4 -1 -2 1 5 -3
//            Ans: 360
// ------------------------------------------------------------------------------------------------
int maxProduct(vector<int>& nums)
{
    // Array can have a single negative number
    int maxPosProd = nums[0];
    int minNegProd = nums[0];
    int finalProd = nums[0];

    for (int i = 1; i < nums.size(); i++)
    {
        int tmpMax = maxPosProd;
        int tmpMin = minNegProd;

        // Case 1: 5, 4
        // Case 2: 5, -4
        // Case 3: -5, 4
        // Case 4: -5, -4
        // For each new number the max product till now can be either
        //      a. Max till now     * a[i] - If result gives a positive value
        //      b. Min Neg till now * a[i] - If current number is negative
        //      c. a[i]                    - If 
        maxPosProd = max(max(tmpMax * nums[i], tmpMin * nums[i]), nums[i]);
        minNegProd = min(min(tmpMax * nums[i], tmpMin * nums[i]), nums[i]);
        finalProd = max(maxPosProd, finalProd);
    }

    return finalProd;

}

// ------------------------------------------------------------------------------------------------
// PROBLEM 6. Coin change problem
//            coins[] = {25, 10, 5}, V = 30
//            Ans: 2
// ------------------------------------------------------------------------------------------------
//uint32_t minCoinChangeRec(vector<int> coins)
uint32_t minCoinChangeRec(uint32_t coins[], uint32_t num, uint32_t val)
{
    if (val == 0)
    {
        return 0;
    }

    else
    {
        uint32_t minCoin = UINT_MAX;
        for (uint32_t i = 0; i < num; i++)
        {
            if (val >= coins[i])
            {
                // IMP: We have UNLIMITED supply of coins. So comment out the below line
                //int tempMinCoin = 1 + minCoinChangeRec(coins + 1 , num - 1, val - coins[i]);
                uint32_t tempMinCoin = minCoinChangeRec(coins + i , num - i, val - coins[i]);

                if (tempMinCoin != UINT_MAX)
                {
                    minCoin = min(1 + tempMinCoin, minCoin);
                }
            }
        }
        return minCoin;
    }
}

uint32_t minCoinChangeDP(uint32_t coins[], uint32_t num, uint32_t val)
{
    // We will store values till dpTable of VAL. So need space from 0 to Val + 1.
    // To store dpTable[5], we need an array of size 6.
    uint32_t dpTable[val+1];
    uint32_t tmpResult = UINT_MAX;
    std::fill_n(dpTable, val+1, UINT_MAX);

    dpTable[0] = 0;

    // Motto is to fill the DP table from 1 to Target Value
    // For each entry in the dp table, see if we can get that using an entry we have saved before.
    for(uint32_t i = 1; i <= val; i++)
    {
        for (uint32_t j = 0; j < num; j++)
        {
            // Only if the dp table entry is >= current coin proceed
            if (coins[j] <= i)
            {
                tmpResult = dpTable[i - coins[j]];
                if ((tmpResult != UINT_MAX) &&
                    (tmpResult + 1 < dpTable[i]))
                {
                    dpTable[i] = tmpResult + 1;
                }
            }
        }
    }

    return dpTable[val];
}

// Wrapper function to return -1 when we can't give out the Coin Change
int32_t minCoinChangeWrapper(uint32_t coins[], uint32_t num, uint32_t val)
{
    // Following is the recursive function
    //uint32_t minCoins = minCoinChangeRec(coins, num, val);

    // Following is the dynamic programming approach function
    uint32_t minCoins = minCoinChangeDP(coins, num, val);

    return (minCoins == UINT_MAX ? -1 : minCoins);
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 7. Print Matrix Diagonally
// ------------------------------------------------------------------------------------------------
template <int rows, int cols>
void printMatrixDiagonally(int (&twoDMatrix)[rows][cols])
//void printMatrixDiagonally(int (&twoDMatrix)[rows][cols])
//void printMatrixDiagonally(int twoDMatrix[3][3], int rows, int cols)
{
    int prevCol = 0;
    int prevRow = -1;
    int r = -1;
    int c = 0;
    int l = 0;

    // Total number of lines.
    for (; l < rows + cols - 1; l++)
    {
        if (prevRow < rows - 1)
        {
            prevRow++;
            r = prevRow;

            c = 0;
        }
        else
        {
            r = prevRow;

            prevCol++;
            c = prevCol;
        }

        while (r >= 0 && c < cols)
        {
            cout << twoDMatrix[r][c] << " ";
            r--;
            c++;
        }

        cout << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 8. Given a string of 1s and 0s with '?' in between. A '?' can be either one or zero.
//            Print All combinations of the string.
//
//            10?0
//            Ans: 1010
//                 1000
// ------------------------------------------------------------------------------------------------

void printCombinationOnesZeros(string str, uint32_t stIdx, uint32_t lastQMarkPos)
{
    if (stIdx == lastQMarkPos)
    {
        cout << str << endl;
        return;
    }

    for (uint32_t i = stIdx; i < str.size(); i++)
    {
        if (str[i] == '?')
        {
            str[i] = '0';
            printCombinationOnesZeros(str, i, lastQMarkPos);

            str[i] = '1';
            printCombinationOnesZeros(str, i, lastQMarkPos);
        }
    }
}

void findLastQMark(string str)
{
    uint32_t lastQMarkPos = str.size();
    for (int i = str.size()-1; i >=0; i--)
    {
        if (str[i] == '?')
        {
            lastQMarkPos = i;
        }
    }

    if (lastQMarkPos < str.size())
    {
        printCombinationOnesZeros(str, 0, lastQMarkPos);
    }
    else
    {
        cout << str << endl;
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 9. Given an integer x, find ONE digit who is equal to its adjacent digits,
//            and remove it. If there are multiple outcomes, return the largest number.
//
//            2234256623
//            Ans: 234256623 > 223425623
// ------------------------------------------------------------------------------------------------
int largestNumByRemovingDup(int number)
{
    string strNum = to_string(number);

    if (strNum.size() < 2)
    {
        return number;
    }

    for (uint32_t i = 0; i < strNum.size() - 1; i++)
    {
        if (strNum[i] == strNum[i+1])
        {
            if (i+2 < strNum.size())
            {
                if (strNum[i+1] < strNum[i+2])
                {
                    strNum.erase(i+1, 1);
                    return atoi(strNum.c_str());
                }
            }
            // Reached end of string and last digit is  repeated. Just remove it
            else
            {
                strNum.erase(i+1, 1);
                return atoi(strNum.c_str());
            }
        }
    }

    for (int32_t i = strNum.size()-1; i > 0; i--)
    {
        if (strNum[i] == strNum[i-1])
        {
            if (i-2 >= 0)
            {
                if (strNum[i-1] < strNum[i-2])
                {
                    strNum.erase(i-1, 1);
                    return atoi(strNum.c_str());
                }
                // Reached end of string and first digit is  repeated. Just remove it
                else
                {
                    strNum.erase(i-1, 1);
                    return atoi(strNum.c_str());
                }
            }
        }
    }
}

// ------------------------------------------------------------------------------------------------
// PROBLEM 10. Find Equilibrium Index of an array. Sum of left elements = Sum of Right elements
//            -7, 1, 5, 2, -4, 3, 0
//
//            Ans: 3
// ------------------------------------------------------------------------------------------------
int32_t equilibriumIndex(vector<int> nums)
{
    int totalSum = 0;
    int leftSum = 0;
    int rightSum = 0;
    for (int a: nums)
    {
        totalSum += a;
    }

    for (uint32_t i = 0; i < nums.size(); i++)
    {
        // IMP: First thing to do is add element to Left sum
        // For Right Sum, we should exclude the current element as well.
        rightSum = totalSum - (leftSum + nums[i]);
        if (rightSum == leftSum)
        {
            return i;
        }

        leftSum += nums[i];
    }

    return -1;
}

// ------------------------------------------------------------------------------------------------
// Main Function
// ------------------------------------------------------------------------------------------------
int main()
{
    // Problem 1:
    {
        string s1 = "hexlloahao";
        string s2 = "hexlloab";
        char result;
        if (findFirstNonMatchingChar(s1, s2, result))
        {
            cout << "First Non Match Char: " << result << endl;
        }
        else
        {
            cout << "No non Match Char" << endl;
        }
    }

    // Problem 2:
    {
        string s1 = "hlllhabcdedcba";
        cout << "Unique Char: " << findUniqueChar(s1) << endl;
    }

    // Problem 3:
    {
        uint32_t rows = 5;
        uint32_t cols = 5;
        /*
        int twoD[rows][cols] = {{1, 1, 0},
                                {0, 1, 0},
                                {1, 0, 0} };
                                */
        int twoD[rows][cols] = {{1, 1, 0, 0, 0},
                                {0, 1, 0, 0, 1},
                                {1, 0, 0, 1, 1},
                                {0, 0, 0, 0, 0},
                                {1, 0, 1, 0, 1}};

        int **arrayTwoD = new int *[rows];
        for (uint32_t i = 0; i < rows; i++)
        {
            arrayTwoD[i] = new int[cols];
        }

        for (uint32_t i = 0; i < rows; i++)
        {
            for (uint32_t j = 0; j < cols; j++)
            {
                arrayTwoD[i][j] = twoD[i][j];
            }
        }

        printTwoDPtrToPtr(arrayTwoD, rows, cols);
        cout << "Num Islands: " << countConnectedIslands(arrayTwoD, rows, cols) << endl;
    }
        
    // Problem 4: Median of Streams
    {
        int a[] = {5, 2, 4, 7, 2, 9, 1, 15, -3, 8, 13, -1, 3, 1, 6};
        //int a[] = {5, 2, 4, 7};
        cout << "Median of Stream: ";
        cout << medianOfStreams(a, sizeof(a) / sizeof(int)) << endl;
    }

    // Problem 6: Coin Change Problem
    {
        uint32_t coins[] = {10, 5};
        cout << "Min Coins: ";
        cout << minCoinChangeWrapper(coins, sizeof(coins)/sizeof(uint32_t), 20) << endl;
    }

    // Problem 7: Print Matrix Diagonally
    {
        int twoD[5][4] = {{1, 2, 3, 4},
                          {5, 6, 7, 8},
                          {9, 10, 11, 12},
                          {13, 14, 15, 16},
                          {17, 18, 19, 20}};
        /*
        int twoD[3][3] = {{1, 2, 3},
                          {4, 5, 6},
                          {7, 8, 9}};
                          */

        printMatrixDiagonally(twoD);
        //printMatrixDiagonally(twoD, 3, 3);
    }

    // Problem 8: Combination of 1s and 0s
    {
        string str = "10?0";
        findLastQMark(str);
    }

    // Problem 9: Remove duplicate int from a number
    {
        cout << largestNumByRemovingDup(122334) << endl;
        cout << largestNumByRemovingDup(433221) << endl << endl;
        cout << largestNumByRemovingDup(122334) << endl;
        cout << largestNumByRemovingDup(43332221) << endl << endl;
        cout << largestNumByRemovingDup(122334) << endl;
        cout << largestNumByRemovingDup(4333222) << endl;
    }

    // Problem 10. Find equilibrium Index
    {
        vector<int> nums = {-7, 1, 5, 2, -4, 3, 0};
        cout << "Eq Idx: " << equilibriumIndex(nums) << endl;
    }
    cout << endl;
    return 0;
}