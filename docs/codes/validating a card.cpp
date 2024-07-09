#include <iostream>
#include <vector>
#include <bitset>
#include <functional>

using namespace std;

class BloomFilter
{
private:
    vector<function<size_t(const string &)>> hashFunctions;
    bitset<1000000> filter;

public:
    BloomFilter()
    {
        hashFunctions = {
            hash<string>{}};
    }

    void add(const string &cardNumber)
    {
        for (auto &hashFunction : hashFunctions)
        {
            size_t index = hashFunction(cardNumber) % filter.size();
            filter.set(index);
        }
    }

    bool contains(const string &cardNumber)
    {
        for (auto &hashFunction : hashFunctions)
        {
            size_t index = hashFunction(cardNumber) % filter.size();
            if (!filter.test(index))
            {
                return false;
            }
        }
        return true;
    }
};

int main()
{
    BloomFilter bloomFilter;

    bloomFilter.add("1234567890123456");
    bloomFilter.add("2345678901234567");
    bloomFilter.add("3456789012345678");

    string cardNumber;
    cout << "Enter card number to validate: ";
    cin >> cardNumber;

    if (bloomFilter.contains(cardNumber))
    {
        cout << "Card " << cardNumber << " is blocked, expired, or blacklisted. Transaction canceled." << endl;
    }
    else
    {
        cout << "Card " << cardNumber << " is valid. Proceed with transaction." << endl;
    }

    return 0;
}
