#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    int numVertices;
    vector<vector<int>> adjList;

public:
    // Constructor
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    // Add edge to the graph (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // For undirected graph
    }

    // Breadth-First Search (BFS)
    vector<int> bfs(int start) {
        vector<bool> visited(numVertices, false);
        vector<int> traversalOrder;
        queue<int> q;

        // Start from the initial node
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int current = q.front();
            q.pop();
            traversalOrder.push_back(current);

            // Enqueue all unvisited neighbors
            for (int neighbor : adjList[current]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }

        return traversalOrder;
    }
};

int main() {
    int vertices = 6;
    Graph g(vertices);

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    // Perform BFS
    vector<int> traversalOrder = g.bfs(0);

    // Display traversal order
    cout << "Breadth-First Search Order: ";
    for (int node : traversalOrder) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
