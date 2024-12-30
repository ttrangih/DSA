#include <iostream>
#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjList;
    int time; // Timer for discovery times

    // Helper function to perform DFS and find bridges
    void dfs(int u, vector<bool> &visited, vector<int> &disc, vector<int> &low, vector<int> &parent, vector<pair<int, int>> &bridges) {
        visited[u] = true;
        disc[u] = low[u] = ++time;

        // Traverse all adjacent vertices
        for (int v : adjList[u]) {
            if (!visited[v]) {
                parent[v] = u;
                dfs(v, visited, disc, low, parent, bridges);

                // Update low value of the current vertex based on the child
                low[u] = min(low[u], low[v]);

                // Check if the edge (u, v) is a bridge
                if (low[v] > disc[u]) {
                    bridges.push_back({u, v});
                }
            } else if (v != parent[u]) {
                // Update low value of u for back edge
                low[u] = min(low[u], disc[v]);
            }
        }
    }

public:
    // Constructor
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
        time = 0;
    }

    // Add edge (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Function to find all bridges in the graph
    vector<pair<int, int>> findBridges() {
        vector<bool> visited(numVertices, false);
        vector<int> disc(numVertices, -1); // Discovery times
        vector<int> low(numVertices, -1); // Lowest reachable vertex
        vector<int> parent(numVertices, -1);
        vector<pair<int, int>> bridges;

        // Perform DFS for each component
        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                dfs(i, visited, disc, low, parent, bridges);
            }
        }

        return bridges;
    }
};

int main() {
    int vertices = 5;
    Graph g(vertices);

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(3, 4);

    // Find bridges
    vector<pair<int, int>> bridges = g.findBridges();

    // Display bridges
    cout << "Bridges in the graph:" << endl;
    for (auto &bridge : bridges) {
        cout << bridge.first << " - " << bridge.second << endl;
    }

    return 0;
}
