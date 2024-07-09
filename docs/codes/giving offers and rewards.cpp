#include <iostream>
#include <vector>

using namespace std;

pair<int, int> findLeastUsagePeriod(const vector<int> &cardUsage)
{
    int n = cardUsage.size();
    if (n == 0)
        return {-1, -1};

    int minEndingHere = cardUsage[0];
    int minSoFar = cardUsage[0];
    int start = 0;
    int end = 0;
    int tempStart = 0;

    for (int i = 1; i < n; ++i)
    {
        if (minEndingHere > 0)
        {
            minEndingHere = cardUsage[i];
            tempStart = i;
        }
        else
        {
            minEndingHere += cardUsage[i];
        }

        if (minEndingHere < minSoFar)
        {
            minSoFar = minEndingHere;
            start = tempStart;
            end = i;
        }
    }

    return {start, end};
}

int main()
{
    vector<int> cardUsage;

    int n;
    cout << "Enter the number of months or periods: ";
    cin >> n;

    cout << "Enter the card usage values for each period:" << endl;
    for (int i = 0; i < n; ++i)
    {
        int usage;
        cout << "Period " << i + 1 << ": ";
        cin >> usage;
        cardUsage.push_back(usage);
    }

    pair<int, int> period = findLeastUsagePeriod(cardUsage);

    if (period.first == -1 && period.second == -1)
    {
        cout << "No valid period found." << endl;
    }
    else
    {
        cout << "Least card usage period: [" << period.first << ", " << period.second << "]" << endl;
    }

    return 0;
}
