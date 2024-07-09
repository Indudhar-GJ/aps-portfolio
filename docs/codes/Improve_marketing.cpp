#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class UnionFind
{
public:
    UnionFind(int size)
    {
        parent.resize(size);
        rank.resize(size, 0);
        for (int i = 0; i < size; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unionSets(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);

        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

    bool connected(int x, int y)
    {
        return find(x) == find(y);
    }

private:
    vector<int> parent;
    vector<int> rank;
};

int main()
{
    UnionFind uf(10);

    vector<pair<int, int>> relationships = {
        {0, 1},
        {1, 2},
        {3, 4},
        {5, 6},
        {6, 7},
        {8, 9},
        {2, 3},
    };

    for (const auto &rel : relationships)
    {
        uf.unionSets(rel.first, rel.second);
    }

    cout << "User 0 and User 3 are connected: " << uf.connected(0, 3) << endl;
    cout << "User 5 and User 7 are connected: " << uf.connected(5, 7) << endl;
    cout << "User 8 and User 9 are connected: " << uf.connected(8, 9) << endl;

    unordered_map<int, int> groupSize;
    for (int i = 0; i < 10; ++i)
    {
        int root = uf.find(i);
        groupSize[root]++;
    }

    for (const auto &group : groupSize)
    {
        if (group.second > 2)
        {
            cout << "Significant group detected with root " << group.first << " involving " << group.second << " users." << endl;
        }
    }

    return 0;
}
