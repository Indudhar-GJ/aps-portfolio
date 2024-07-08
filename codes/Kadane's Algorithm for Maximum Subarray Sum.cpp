#include <iostream>
#include <vector>
using namespace std;

int kadane(const vector<int> &arr)
{
    int maxSoFar = arr[0], maxEndingHere = arr[0];
    for (size_t i = 1; i < arr.size(); ++i)
    {
        maxEndingHere = max(arr[i], maxEndingHere + arr[i]);
        maxSoFar = max(maxSoFar, maxEndingHere);
    }
    return maxSoFar;
}

int main()
{
    vector<int> arr = {1, -2, 3, 4, -1, 2, 1, -5, 4};
    cout << "Maximum subarray sum is " << kadane(arr) << endl;
    return 0;
}
