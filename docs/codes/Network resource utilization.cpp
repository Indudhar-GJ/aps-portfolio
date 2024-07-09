#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

const int MAX_V = 100;
struct Edge
{
    int v, capacity, flow;
    Edge(int _v, int _capacity, int _flow) : v(_v), capacity(_capacity), flow(_flow) {}
};

class Graph
{
    int V;
    vector<Edge> edges[MAX_V];

public:
    Graph(int V) : V(V) {}

    void addEdge(int u, int v, int capacity)
    {
        edges[u].push_back(Edge(v, capacity, 0));
        edges[v].push_back(Edge(u, 0, 0));
    }

    int fordFulkerson(int source, int sink)
    {
        int maxFlow = 0;

        vector<int> parent(V);

        while (bfs(source, sink, parent))
        {
            int pathFlow = INT_MAX;
            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                for (auto &edge : edges[u])
                {
                    if (edge.v == v)
                    {
                        pathFlow = min(pathFlow, edge.capacity - edge.flow);
                        break;
                    }
                }
            }

            for (int v = sink; v != source; v = parent[v])
            {
                int u = parent[v];
                for (auto &edge : edges[u])
                {
                    if (edge.v == v)
                    {
                        edge.flow += pathFlow;
                        for (auto &revEdge : edges[edge.v])
                        {
                            if (revEdge.v == u)
                            {
                                revEdge.flow -= pathFlow;
                                break;
                            }
                        }
                        break;
                    }
                }
            }

            maxFlow += pathFlow;
        }

        return maxFlow;
    }

private:
    bool bfs(int source, int sink, vector<int> &parent)
    {
        vector<bool> visited(V, false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;

        while (!q.empty())
        {
            int u = q.front();
            q.pop();

            for (const auto &edge : edges[u])
            {
                int v = edge.v;
                if (!visited[v] && edge.capacity > edge.flow)
                {
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                    if (v == sink)
                        return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    int V = 6;
    Graph graph(V);

    graph.addEdge(0, 1, 16);
    graph.addEdge(0, 2, 13);
    graph.addEdge(1, 2, 10);
    graph.addEdge(1, 3, 12);
    graph.addEdge(2, 1, 4);
    graph.addEdge(2, 4, 14);
    graph.addEdge(3, 2, 9);
    graph.addEdge(3, 5, 20);
    graph.addEdge(4, 3, 7);
    graph.addEdge(4, 5, 4);

    int source = 0;
    int sink = 5;

    cout << "Maximum flow from source to sink: " << graph.fordFulkerson(source, sink) << endl;

    return 0;
}
