#include <iostream>
#include <vector>
#include <queue>
#include <map>
#include <climits>
#include <set>
#include <algorithm>
#include <stack>

using namespace std;

// Graph representation
class Graph {
public:
    Graph(int nodes) : nodes(nodes) {
        adjList.resize(nodes);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Undirected graph
    }

    // Dijkstra's algorithm to find the shortest path
    vector<int> dijkstra(int src, int dest) {
        vector<int> dist(nodes, INT_MAX);
        vector<int> parent(nodes, -1);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[src] = 0;
        pq.push({0, src});

        while (!pq.empty()) {
            int currDist = pq.top().first;
            int u = pq.top().second;
            pq.pop();

            if (currDist > dist[u]) continue;

            for (auto& [v, weight] : adjList[u]) {
                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    pq.push({dist[v], v});
                }
            }
        }

        // Retrieve the shortest path
        vector<int> path;
        for (int at = dest; at != -1; at = parent[at]) {
            path.push_back(at);
        }
        reverse(path.begin(), path.end());
        return path;
    }

    // Calculate betweenness centrality for traffic bottlenecks
    vector<double> calculateBetweenness() {
        vector<double> betweenness(nodes, 0.0);

        for (int src = 0; src < nodes; ++src) {
            vector<int> dist(nodes, INT_MAX);
            vector<int> numPaths(nodes, 0);
            vector<int> parentCount(nodes, 0);
            vector<double> dependency(nodes, 0.0);
            stack<int> s;

            dist[src] = 0;
            numPaths[src] = 1;
            queue<int> q;
            q.push(src);

            while (!q.empty()) {
                int u = q.front();
                q.pop();
                s.push(u);

                for (auto& [v, weight] : adjList[u]) {
                    if (dist[v] == INT_MAX) {
                        dist[v] = dist[u] + 1;
                        q.push(v);
                    }
                    if (dist[v] == dist[u] + 1) {
                        numPaths[v] += numPaths[u];
                        parentCount[v]++;
                    }
                }
            }

            while (!s.empty()) {
                int u = s.top();
                s.pop();

                for (auto& [v, weight] : adjList[u]) {
                    if (dist[v] == dist[u] + 1) {
                        dependency[u] += ((double)numPaths[u] / numPaths[v]) * (1 + dependency[v]);
                    }
                }

                if (u != src) {
                    betweenness[u] += dependency[u];
                }
            }
        }

        return betweenness;
    }

    void printGraph() {
        for (int i = 0; i < nodes; ++i) {
            cout << "Node " << i << ": ";
            for (auto& [neighbor, weight] : adjList[i]) {
                cout << "(" << neighbor << ", " << weight << ") ";
            }
            cout << endl;
        }
    }

private:
    int nodes;
    vector<vector<pair<int, int>>> adjList; // {node, weight}
};

int main() {
    // Create a graph representing a city's road network
    Graph g(6);

    // Add edges (road connections with travel time weights)
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 1);
    g.addEdge(1, 3, 7);
    g.addEdge(2, 4, 3);
    g.addEdge(3, 4, 2);
    g.addEdge(3, 5, 1);
    g.addEdge(4, 5, 5);

    cout << "City's Road Network:" << endl;
    g.printGraph();

    // Identify traffic bottlenecks
    vector<double> betweenness = g.calculateBetweenness();
    cout << "\nTraffic Bottlenecks (Betweenness Centrality):" << endl;
    for (int i = 0; i < betweenness.size(); ++i) {
        cout << "Node " << i << ": " << betweenness[i] << endl;
    }

    // Suggest alternative route
    int src = 0, dest = 5;
    vector<int> path = g.dijkstra(src, dest);
    cout << "\nOptimal Route from " << src << " to " << dest << ": ";
    for (int node : path) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
