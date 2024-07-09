#include <iostream>
#include <queue>
#include <vector>
#include <string>
#include <map>

using namespace std;

map<string, int> cardTypePriority = {
    {"Platinum", 4},
    {"Premium", 3},
    {"Gold", 2},
    {"Silver", 1}};

struct Transaction
{
    string cardType;
    int priority;
    string transactionDetails;

    Transaction(const string &type, const string &details) : cardType(type), transactionDetails(details)
    {
        if (cardTypePriority.find(cardType) != cardTypePriority.end())
        {
            priority = cardTypePriority[cardType];
        }
        else
        {
            priority = 0;
        }
    }

    bool operator<(const Transaction &other) const
    {
        return priority < other.priority;
    }
};

void processTransactions(priority_queue<Transaction> &pq)
{
    while (!pq.empty())
    {
        Transaction t = pq.top();
        pq.pop();
        cout << "Processing transaction: " << t.transactionDetails << " with card type: " << t.cardType << " and priority: " << t.priority << endl;
    }
}

int main()
{
    priority_queue<Transaction> transactionQueue;
    int n;

    cout << "Enter the number of transactions: ";
    cin >> n;

    cin.ignore();

    for (int i = 0; i < n; ++i)
    {
        string cardType, transactionDetails;

        cout << "Enter card type for transaction " << i + 1 << ": ";
        getline(cin, cardType);

        cout << "Enter transaction details for transaction " << i + 1 << ": ";
        getline(cin, transactionDetails);

        transactionQueue.push(Transaction(cardType, transactionDetails));
    }

    processTransactions(transactionQueue);

    return 0;
}
