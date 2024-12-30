//22521514 Nguyen Thuy Trang - Lab6_ex4

#include <iostream>
#include <vector>
#include <unordered_map>
#include <stack>
#include <set>
#include <queue>
using namespace std;

class Graph {
private:
    unordered_map<int, vector<int>> adjacencyList; // For adjacency list
    vector<vector<int>> adjacencyMatrix;          // For adjacency matrix
    int vertexCount;

public:
    // Constructor
    Graph() : vertexCount(0) {}

    // Method to add a vertex
    void addVertex() {
        vertexCount++;

        // Expand the adjacency matrix
        for (auto &row : adjacencyMatrix) {
            row.push_back(0);
        }
        adjacencyMatrix.push_back(vector<int>(vertexCount, 0));

        // Add entry for adjacency list
        adjacencyList[vertexCount - 1] = vector<int>();
    }

    // Method to add an edge
    void addEdge(int from, int to) {
        if (from >= vertexCount || to >= vertexCount) {
            cout << "Invalid vertices: " << from << " -> " << to << endl;
            return;
        }

        // Add edge to adjacency list
        adjacencyList[from].push_back(to);

        // Add edge to adjacency matrix
        adjacencyMatrix[from][to] = 1;
    }

    // Display the adjacency list
    void displayAdjacencyList() {
        cout << "Adjacency List:" << endl;
        for (const auto &pair : adjacencyList) {
            int key = pair.first;
            const vector<int> &value = pair.second;

            cout << key << ": ";
            for (int v : value) {
                cout << v << " ";
            }
            cout << endl;
        }
    }

    // Display the adjacency matrix
    void displayAdjacencyMatrix() {
        cout << "Adjacency Matrix:" << endl;
        for (const auto &row : adjacencyMatrix) {
            for (int value : row) {
                cout << value << " ";
            }
            cout << endl;
        }
    }

    // Recursive Depth-First Search
    void dfsRecursive(int start, set<int> &visited) {
        if (visited.count(start)) return;

        cout << start << " ";
        visited.insert(start);

        for (int neighbor : adjacencyList[start]) {
            dfsRecursive(neighbor, visited);
        }
    }

    // Iterative Depth-First Search
    void dfsIterative(int start) {
        set<int> visited;
        stack<int> s;
        s.push(start);

        while (!s.empty()) {
            int current = s.top();
            s.pop();

            if (!visited.count(current)) {
                cout << current << " ";
                visited.insert(current);

                for (auto it = adjacencyList[current].rbegin(); it != adjacencyList[current].rend(); ++it) {
                    s.push(*it);
                }
            }
        }
    }

    // Breadth-First Search
    vector<int> bfs(int start) {
        vector<int> traversalOrder;
        set<int> visited;
        queue<int> q;

        q.push(start);
        visited.insert(start);

        while (!q.empty()) {
            int current = q.front();
            q.pop();

            traversalOrder.push_back(current);

            for (int neighbor : adjacencyList[current]) {
                if (!visited.count(neighbor)) {
                    q.push(neighbor);
                    visited.insert(neighbor);
                }
            }
        }

        return traversalOrder;
    }

    // Detect cycle in directed graph using DFS
    bool hasCycleDirectedUtil(int node, set<int> &visited, set<int> &recStack) {
        visited.insert(node);
        recStack.insert(node);

        for (int neighbor : adjacencyList[node]) {
            if (recStack.count(neighbor)) {
                return true; // Cycle found
            }
            if (!visited.count(neighbor) && hasCycleDirectedUtil(neighbor, visited, recStack)) {
                return true;
            }
        }

        recStack.erase(node);
        return false;
    }

    bool hasCycleDirected() {
        set<int> visited;
        set<int> recStack;

        for (int i = 0; i < vertexCount; i++) {
            if (!visited.count(i) && hasCycleDirectedUtil(i, visited, recStack)) {
                return true;
            }
        }

        return false;
    }

    // Detect cycle in undirected graph using DFS
    bool hasCycleUndirectedUtil(int node, int parent, set<int> &visited) {
        visited.insert(node);

        for (int neighbor : adjacencyList[node]) {
            if (!visited.count(neighbor)) {
                if (hasCycleUndirectedUtil(neighbor, node, visited)) {
                    return true;
                }
            } else if (neighbor != parent) {
                return true; // Cycle found
            }
        }

        return false;
    }

    bool hasCycleUndirected() {
        set<int> visited;

        for (int i = 0; i < vertexCount; i++) {
            if (!visited.count(i) && hasCycleUndirectedUtil(i, -1, visited)) {
                return true;
            }
        }

        return false;
    }
};

int main() {
    Graph graph;

    // Adding vertices
    graph.addVertex(); // Vertex 0
    graph.addVertex(); // Vertex 1
    graph.addVertex(); // Vertex 2
    graph.addVertex(); // Vertex 3

    // Adding edges for directed graph
    graph.addEdge(0, 1);
    graph.addEdge(1, 2);
    graph.addEdge(2, 0);
    graph.addEdge(2, 3);

    // Display the adjacency list and matrix
    graph.displayAdjacencyList();
    graph.displayAdjacencyMatrix();

    // Check for cycles in directed graph
    cout << "\nChecking for cycles in directed graph: " << (graph.hasCycleDirected() ? "Cycle detected" : "No cycle detected") << endl;

    // Create a new graph for undirected testing
    Graph undirectedGraph;

    // Adding vertices
    undirectedGraph.addVertex(); // Vertex 0
    undirectedGraph.addVertex(); // Vertex 1
    undirectedGraph.addVertex(); // Vertex 2
    undirectedGraph.addVertex(); // Vertex 3

    // Adding edges for undirected graph
    undirectedGraph.addEdge(0, 1);
    undirectedGraph.addEdge(1, 2);
    undirectedGraph.addEdge(2, 0);
    undirectedGraph.addEdge(2, 3);

    // Check for cycles in undirected graph
    cout << "Checking for cycles in undirected graph: " << (undirectedGraph.hasCycleUndirected() ? "Cycle detected" : "No cycle detected") << endl;

    return 0;
}
