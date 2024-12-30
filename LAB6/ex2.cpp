#include <iostream>
#include <vector>
#include <stack>
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

    // Recursive DFS
    void dfsRecursive(int start, vector<bool> &visited) {
        visited[start] = true;
        cout << start << " ";

        for (int neighbor : adjList[start]) {
            if (!visited[neighbor]) {
                dfsRecursive(neighbor, visited);
            }
        }
    }

    // Iterative DFS using stack
    void dfsIterative(int start) {
        vector<bool> visited(numVertices, false);
        stack<int> s;
        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited[current]) {
                cout << current << " ";
                visited[current] = true;
            }

            // Push neighbors to stack in reverse order to simulate recursion order
            for (auto it = adjList[current].rbegin(); it != adjList[current].rend(); ++it) {
                if (!visited[*it]) {
                    s.push(*it);
                }
            }
        }
    }

    // Wrapper function to call recursive DFS
    void performDFSRecursive(int start) {
        vector<bool> visited(numVertices, false);
        cout << "Recursive DFS: ";
        dfsRecursive(start, visited);
        cout << endl;
    }

    // Wrapper function to call iterative DFS
    void performDFSIterative(int start) {
        cout << "Iterative DFS: ";
        dfsIterative(start);
        cout << endl;
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

    // Perform DFS
    g.performDFSRecursive(0);
    g.performDFSIterative(0);

    return 0;
}
