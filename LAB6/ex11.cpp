#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_map>
#include <limits>

using namespace std;

// Define a pair of (cost, node)
typedef pair<double, int> pdi;

// A structure to represent a point in 2D space
struct Point {
    double x, y;
    Point(double x = 0, double y = 0) : x(x), y(y) {}
};

// Heuristic function: Calculate Euclidean distance
double euclideanDistance(const Point& a, const Point& b) {
    return sqrt(pow(a.x - b.x, 2) + pow(a.y - b.y, 2));
}

class Graph {
public:
    Graph(int nodes) {
        this->nodes = nodes;
        adjList.resize(nodes);
        points.resize(nodes);
    }

    // Add an edge to the graph
    void addEdge(int u, int v, double weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); // Undirected graph
    }

    // Set coordinates for a node
    void setPoint(int node, double x, double y) {
        points[node] = Point(x, y);
    }

    // A* Algorithm for shortest path
    double aStar(int start, int goal) {
        // Priority queue: (f_score, node)
        priority_queue<pdi, vector<pdi>, greater<pdi>> pq;

        vector<double> gScore(nodes, numeric_limits<double>::infinity());
        vector<double> fScore(nodes, numeric_limits<double>::infinity());

        gScore[start] = 0;
        fScore[start] = euclideanDistance(points[start], points[goal]);
        pq.push({fScore[start], start});

        while (!pq.empty()) {
            int current = pq.top().second;
            pq.pop();

            // If we reached the goal, return the total cost
            if (current == goal) {
                return gScore[current];
            }

            // Process neighbors
            for (auto& neighbor : adjList[current]) {
                int next = neighbor.first;
                double weight = neighbor.second;

                // Tentative gScore for neighbor
                double tentative_gScore = gScore[current] + weight;

                if (tentative_gScore < gScore[next]) {
                    gScore[next] = tentative_gScore;
                    fScore[next] = gScore[next] + euclideanDistance(points[next], points[goal]);
                    pq.push({fScore[next], next});
                }
            }
        }

        return -1; // Return -1 if no path exists
    }

private:
    int nodes; // Number of nodes
    vector<vector<pdi>> adjList; // Adjacency list (node, weight)
    vector<Point> points; // Coordinates of nodes
};

int main() {
    // Create a graph with 6 delivery points
    Graph g(6);

    // Set coordinates for each delivery point
    g.setPoint(0, 0, 0); // Delivery point 0
    g.setPoint(1, 2, 3); // Delivery point 1
    g.setPoint(2, 5, 5); // Delivery point 2
    g.setPoint(3, 8, 3); // Delivery point 3
    g.setPoint(4, 6, 1); // Delivery point 4
    g.setPoint(5, 10, 0); // Delivery point 5

    // Add weighted edges between delivery points
    g.addEdge(0, 1, 4.2);
    g.addEdge(0, 2, 7.8);
    g.addEdge(1, 2, 3.0);
    g.addEdge(1, 3, 5.1);
    g.addEdge(2, 4, 2.4);
    g.addEdge(3, 4, 3.5);
    g.addEdge(4, 5, 4.0);

    // Find the shortest path from point 0 to point 5
    double shortestPath = g.aStar(0, 5);

    if (shortestPath != -1) {
        cout << "Shortest path from 0 to 5: " << shortestPath << endl;
    } else {
        cout << "No path exists from 0 to 5." << endl;
    }

    return 0;
}
