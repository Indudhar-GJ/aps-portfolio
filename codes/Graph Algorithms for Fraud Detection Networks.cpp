#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

void dfs(int node, unordered_map<int, vector<int>> &graph, vector<bool> &visited)
{
    visited[node] = true;
    cout << "Visited node: " << node << endl;
    for (int neighbor : graph[node])
    {
        if (!visited[neighbor])
        {
            dfs(neighbor, graph, visited);
        }
    }
}

int main()
{
    unordered_map<int, vector<int>> graph = {
        {1, {2, 3}},
        {2, {4}},
        {3, {5}},
        {4, {6}},
        {5, {6}},
        {6, {}}};

    vector<bool> visited(7, false);
    dfs(1, graph, visited);

    return 0;
}
