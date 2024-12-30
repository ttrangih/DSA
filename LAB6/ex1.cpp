//22521514 Nguyen Thuy Trang - Lab6_ex1

#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
using namespace std;

class Graph {
private:
    unordered_map<int, list<int>> adjacencyList; // Adjacency List
    vector<vector<int>> adjacencyMatrix;        // Adjacency Matrix
    int numVertices;

public:
    // Constructor for initializing graph with 'n' vertices
    Graph(int n) : numVertices(n) {
        adjacencyMatrix = vector<vector<int>>(n, vector<int>(n, 0));
    }

    // Add an edge (Adjacency List)
    void addEdgeList(int u, int v) {
        adjacencyList[u].push_back(v);
        adjacencyList[v].push_back(u); // For undirected graph
    }

    // Add an edge (Adjacency Matrix)
    void addEdgeMatrix(int u, int v) {
        adjacencyMatrix[u][v] = 1;
        adjacencyMatrix[v][u] = 1; // For undirected graph
    }

    // Display the adjacency list
    void displayAdjList() {
        cout << "Adjacency List:\n";
        for (auto &node : adjacencyList) {
            cout << node.first << " -> ";
            for (auto &neighbor : node.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Display the adjacency matrix
    void displayAdjMatrix() {
        cout << "Adjacency Matrix:\n";
        for (int i = 0; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                cout << adjacencyMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    int n = 5; // Number of vertices
    Graph g(n);

    // Adding edges
    g.addEdgeList(0, 1);
    g.addEdgeList(0, 4);
    g.addEdgeList(1, 4);
    g.addEdgeList(1, 3);
    g.addEdgeList(1, 2);

    g.addEdgeMatrix(0, 1);
    g.addEdgeMatrix(0, 4);
    g.addEdgeMatrix(1, 4);
    g.addEdgeMatrix(1, 3);
    g.addEdgeMatrix(1, 2);

    // Displaying graph
    g.displayAdjList();
    g.displayAdjMatrix();

    return 0;
}
