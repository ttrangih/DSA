#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <set>
#include <cmath>
#include <limits>
using namespace std;

class Graph {
public:
    Graph(int nodes) : nodes(nodes) {
        adjList.resize(nodes);
    }

    void addEdge(int u, int v) {
        adjList[u].insert(v);
        adjList[v].insert(u); // Undirected graph
    }

    // Degree centrality
    vector<int> degreeCentrality() {
        vector<int> centrality(nodes, 0);
        for (int i = 0; i < nodes; ++i) {
            centrality[i] = adjList[i].size();
        }
        return centrality;
    }

    // Simple community detection based on modularity optimization (greedy grouping)
    map<int, int> detectCommunities() {
        map<int, int> community; // Node to community mapping
        for (int i = 0; i < nodes; ++i) {
            community[i] = i; // Initialize each node in its own community
        }

        bool changed = true;
        while (changed) {
            changed = false;
            for (int u = 0; u < nodes; ++u) {
                map<int, int> neighborCommunities;
                for (int v : adjList[u]) {
                    neighborCommunities[community[v]]++;
                }

                int maxCommunity = community[u];
                int maxConnections = 0;
                for (auto& [comm, count] : neighborCommunities) {
                    if (count > maxConnections) {
                        maxConnections = count;
                        maxCommunity = comm;
                    }
                }

                if (maxCommunity != community[u]) {
                    community[u] = maxCommunity;
                    changed = true;
                }
            }
        }
        return community;
    }

    // Print the adjacency list
    void printGraph() {
        for (int i = 0; i < nodes; ++i) {
            cout << "Node " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

private:
    int nodes;
    vector<set<int>> adjList; // Adjacency list with sets for unique neighbors
};

int main() {
    // Create a graph with 8 nodes (social network)
    Graph g(8);

    // Add edges (friendships)
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 0);

    // Print the graph
    cout << "Social Network (Adjacency List):" << endl;
    g.printGraph();

    // Analyze degree centrality
    cout << "\nDegree Centrality:" << endl;
    vector<int> centrality = g.degreeCentrality();
    for (int i = 0; i < centrality.size(); ++i) {
        cout << "Node " << i << ": " << centrality[i] << endl;
    }

    // Detect communities
    cout << "\nCommunities (Node -> Community):" << endl;
    map<int, int> communities = g.detectCommunities();
    for (auto& [node, community] : communities) {
        cout << "Node " << node << " -> Community " << community << endl;
    }

    return 0;
}
