//22521514 Nguyen Thuy Trang - Lab6_ex5


#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

// Define a pair for representing vertices and their distances
typedef pair<int, int> Pair;

class Graph {
private:
    int numVertices;
    vector<vector<Pair>> adjList; // Adjacency list: {neighbor, weight}

public:
    // Constructor
    Graph(int vertices) : numVertices(vertices) {
        adjList.resize(vertices);
    }

    // Add edge to the graph
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // For undirected graph
    }

    // Dijkstra's Algorithm
    vector<int> dijkstra(int source) {
        vector<int> distances(numVertices, INT_MAX); // Distance array
        distances[source] = 0;

        // Min-heap priority queue
        priority_queue<Pair, vector<Pair>, greater<Pair>> pq;
        pq.push({0, source}); // {distance, vertex}

        while (!pq.empty()) {
            int currentDistance = pq.top().first;
            int currentVertex = pq.top().second;
            pq.pop();

            // Skip processing if the distance is outdated
            if (currentDistance > distances[currentVertex]) {
                continue;
            }

            // Relax edges
            for (auto &neighbor : adjList[currentVertex]) {
                int nextVertex = neighbor.first;
                int edgeWeight = neighbor.second;

                if (distances[currentVertex] + edgeWeight < distances[nextVertex]) {
                    distances[nextVertex] = distances[currentVertex] + edgeWeight;
                    pq.push({distances[nextVertex], nextVertex});
                }
            }
        }

        return distances;
    }
};

int main() {
    int vertices = 6;
    Graph g(vertices);

    // Adding edges with weights
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 4);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 5);
    g.addEdge(2, 3, 8);
    g.addEdge(2, 4, 6);
    g.addEdge(3, 4, 3);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 1);

    // Find shortest paths from vertex 0
    vector<int> distances = g.dijkstra(0);

    // Display results
    cout << "Shortest distances from source (0):" << endl;
    for (int i = 0; i < distances.size(); i++) {
        cout << "Vertex " << i << ": " << distances[i] << endl;
    }

    return 0;
}
