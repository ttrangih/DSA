#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
#include <functional>
using namespace std;

struct Edge {
    int u, v, weight;
    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

class Graph {
private:
    int nodes; // Number of devices
    vector<Edge> edges; // List of edges
    vector<vector<pair<int, int>>> adjList; // Adjacency list for Dijkstra

public:
    Graph(int nodes) : nodes(nodes) {
        adjList.resize(nodes);
    }

    void addEdge(int u, int v, int weight) {
        edges.emplace_back(u, v, weight);
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // Since it's an undirected graph
    }

    // Minimum Spanning Tree using Kruskal's Algorithm
    int kruskalMST() {
        sort(edges.begin(), edges.end(), [](Edge a, Edge b) {
            return a.weight < b.weight;
        });

        vector<int> parent(nodes, -1);

        function<int(int)> find = [&](int x) {
            if (parent[x] == -1) return x;
            return parent[x] = find(parent[x]);
        };

        auto unite = [&](int x, int y) {
            int setX = find(x);
            int setY = find(y);
            if (setX != setY) parent[setX] = setY;
        };

        int mstWeight = 0;
        for (const auto& edge : edges) {
            if (find(edge.u) != find(edge.v)) {
                mstWeight += edge.weight;
                unite(edge.u, edge.v);
                cout << "Edge included in MST: (" << edge.u << ", " << edge.v << ") with weight " << edge.weight << endl;
            }
        }

        return mstWeight;
    }

    // Shortest Path using Dijkstra's Algorithm
    void dijkstra(int src) {
        vector<int> dist(nodes, INT_MAX);
        dist[src] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.emplace(0, src);

        while (!pq.empty()) {
            int u = pq.top().second;
            int d = pq.top().first;
            pq.pop();

            if (d > dist[u]) continue;

            for (const auto& [v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    pq.emplace(dist[v], v);
                }
            }
        }

        cout << "Shortest distances from node " << src << ":\n";
        for (int i = 0; i < nodes; ++i) {
            cout << "Node " << i << ": " << dist[i] << endl;
        }
    }
};

int main() {
    int nodes = 6; // Number of devices
    Graph network(nodes);

    // Add connections (u, v, weight)
    network.addEdge(0, 1, 4);
    network.addEdge(0, 2, 3);
    network.addEdge(1, 2, 1);
    network.addEdge(1, 3, 2);
    network.addEdge(2, 3, 4);
    network.addEdge(3, 4, 2);
    network.addEdge(4, 5, 6);

    cout << "Minimum Spanning Tree (MST):\n";
    int mstWeight = network.kruskalMST();
    cout << "Total weight of MST: " << mstWeight << endl;

    cout << "\nShortest Path using Dijkstra's Algorithm:\n";
    network.dijkstra(0); // Find shortest paths from node 0

    return 0;
}
