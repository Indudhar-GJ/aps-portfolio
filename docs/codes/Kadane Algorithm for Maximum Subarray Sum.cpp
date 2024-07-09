#include <iostream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

struct Result
{
    int maxSum;
    int startIndex;
    int endIndex;
};

Result maxSubarraySumWithLength(const vector<int> &arr, int length, bool findPositive)
{
    int maxSum = findPositive ? INT_MIN : INT_MAX;
    int currentSum = 0;
    int start = 0;
    Result res = {findPositive ? INT_MIN : INT_MAX, -1, -1};

    for (int i = 0; i < arr.size(); ++i)
    {
        currentSum += arr[i];
        if ((findPositive && arr[i] > 0) || (!findPositive && arr[i] < 0))
        {
            if ((findPositive && currentSum > maxSum) || (!findPositive && currentSum < maxSum))
            {
                maxSum = currentSum;
                res = {maxSum, start, i};
            }
        }
        if (i >= length - 1)
        {
            currentSum -= arr[start];
            ++start;
        }
    }
    return res;
}

int main()
{
    vector<int> arr = {1, -2, 3, 4, -1, 2, 1, -5, 4};
    int length = 3;

    Result maxPositive = maxSubarraySumWithLength(arr, length, true);
    Result maxNegative = maxSubarraySumWithLength(arr, length, false);

    if (maxPositive.maxSum != INT_MIN)
    {
        cout << "Maximum positive subarray sum with length " << length << " is "
             << maxPositive.maxSum << " from index " << maxPositive.startIndex
             << " to " << maxPositive.endIndex << endl;
    }

    if (maxNegative.maxSum != INT_MAX)
    {
        cout << "Maximum negative subarray sum with length " << length << " is "
             << maxNegative.maxSum << " from index " << maxNegative.startIndex
             << " to " << maxNegative.endIndex << endl;
    }

    return 0;
}
