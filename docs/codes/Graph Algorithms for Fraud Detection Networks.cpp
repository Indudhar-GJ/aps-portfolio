#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>

using namespace std;

class TransactionGraph
{
private:
    unordered_map<int, vector<int>> adjacencyList;

    void performDFS(int start, unordered_set<int> &visited, vector<int> &currentCluster)
    {
        stack<int> toVisit;
        toVisit.push(start);

        while (!toVisit.empty())
        {
            int currentNode = toVisit.top();
            toVisit.pop();

            if (visited.find(currentNode) == visited.end())
            {
                visited.insert(currentNode);
                currentCluster.push_back(currentNode);

                for (int neighbor : adjacencyList[currentNode])
                {
                    if (visited.find(neighbor) == visited.end())
                    {
                        toVisit.push(neighbor);
                    }
                }
            }
        }
    }

public:
    void recordTransaction(int sender, int receiver)
    {
        adjacencyList[sender].push_back(receiver);
        adjacencyList[receiver].push_back(sender);
    }

    vector<vector<int>> findTransactionClusters()
    {
        unordered_set<int> visitedNodes;
        vector<vector<int>> clusters;

        for (const auto &entry : adjacencyList)
        {
            int account = entry.first;
            if (visitedNodes.find(account) == visitedNodes.end())
            {
                vector<int> cluster;
                performDFS(account, visitedNodes, cluster);
                clusters.push_back(cluster);
            }
        }

        return clusters;
    }
};

int main()
{
    TransactionGraph transactionGraph;
    int numberOfTransactions, sender, receiver;

    cout << "Enter the number of transactions: ";
    cin >> numberOfTransactions;

    cout << "Enter transactions (sender receiver):" << endl;
    for (int i = 0; i < numberOfTransactions; ++i)
    {
        cin >> sender >> receiver;
        transactionGraph.recordTransaction(sender, receiver);
    }

    vector<vector<int>> clusters = transactionGraph.findTransactionClusters();

    cout << "Detected high volume transaction clusters:" << endl;
    for (const auto &cluster : clusters)
    {
        cout << "Cluster: ";
        for (int account : cluster)
        {
            cout << account << " ";
        }
        cout << endl;
    }

    return 0;
}
