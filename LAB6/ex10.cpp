#include <iostream>
#include <vector>
#include <queue>
#include <climits>

using namespace std;

// Define a pair of (distance, node)
typedef pair<int, int> pii;

class Graph {
public:
    Graph(int nodes) {
        this->nodes = nodes;
        adjList.resize(nodes);
    }

    // Add an edge to the graph
    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight});  // Assuming undirected graph
    }

    // Dijkstra's algorithm to find shortest path from source node
    void dijkstra(int source) {
        // Initialize distances to infinity, except the source node
        vector<int> dist(nodes, INT_MAX);
        dist[source] = 0;

        // Min-heap priority queue to store (distance, node) pairs
        priority_queue<pii, vector<pii>, greater<pii>> pq;
        pq.push({0, source});  // Start with source node with 0 distance

        while (!pq.empty()) {
            // Get the node with the smallest distance
            int u = pq.top().second;
            pq.pop();

            // Traverse all neighbors of the current node
            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;  // Neighbor node
                int weight = neighbor.second;  // Edge weight

                // Relaxation step: If a shorter path to v is found, update it
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.push({dist[v], v});  // Push the updated distance to the queue
                }
            }
        }

        // Print the shortest distance from source to all other nodes
        printDistances(dist);
    }

private:
    int nodes;  // Number of nodes
    vector<vector<pii>> adjList;  // Adjacency list for the graph

    // Function to print the shortest distances
    void printDistances(const vector<int>& dist) {
        cout << "Shortest distances from source node:" << endl;
        for (int i = 0; i < nodes; ++i) {
            if (dist[i] == INT_MAX) {
                cout << "Node " << i << ": Unreachable" << endl;
            } else {
                cout << "Node " << i << ": " << dist[i] << endl;
            }
        }
    }
};

int main() {
    // Create a graph with 6 nodes (0 to 5)
    Graph g(6);

    // Add edges (undirected graph)
    g.addEdge(0, 1, 5);
    g.addEdge(0, 2, 1);
    g.addEdge(1, 3, 2);
    g.addEdge(2, 1, 3);
    g.addEdge(2, 3, 7);
    g.addEdge(3, 4, 1);
    g.addEdge(4, 5, 6);
    g.addEdge(3, 5, 2);

    // Find shortest paths from node 0
    g.dijkstra(0);

    return 0;
}
