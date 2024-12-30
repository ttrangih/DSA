#include <iostream>
#include <vector>
#include <list>
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

    // Add edge (undirected)
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    // Helper function to perform DFS and collect connected components
    void dfs(int node, vector<bool> &visited, list<int> &component) {
        visited[node] = true;
        component.push_back(node);

        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfs(neighbor, visited, component);
            }
        }
    }

    // Function to find all connected components
    vector<list<int>> findConnectedComponents() {
        vector<bool> visited(numVertices, false);
        vector<list<int>> connectedComponents;

        for (int i = 0; i < numVertices; i++) {
            if (!visited[i]) {
                list<int> component;
                dfs(i, visited, component);
                connectedComponents.push_back(component);
            }
        }

        return connectedComponents;
    }
};

int main() {
    int vertices = 6;
    Graph g(vertices);

    // Adding edges to the graph
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(3, 4);

    // Find connected components
    vector<list<int>> connectedComponents = g.findConnectedComponents();

    // Display connected components
    cout << "Connected Components:" << endl;
    for (int i = 0; i < connectedComponents.size(); i++) {
        cout << "Component " << i + 1 << ": ";
        for (int vertex : connectedComponents[i]) {
            cout << vertex << " ";
        }
        cout << endl;
    }

    return 0;
}
