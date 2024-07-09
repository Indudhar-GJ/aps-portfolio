#include <iostream>
#include <unordered_map>
using namespace std;

int main()
{
    unordered_map<string, string> transactionRecords;
    transactionRecords["TXN12345"] = "Transaction details for TXN12345";
    transactionRecords["TXN67890"] = "Transaction details for TXN67890";

    string txnID = "TXN12345";
    if (transactionRecords.find(txnID) != transactionRecords.end())
    {
        cout << transactionRecords[txnID] << endl;
    }
    else
    {
        cout << "Transaction not found." << endl;
    }

    return 0;
}
