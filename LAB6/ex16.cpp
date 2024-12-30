#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>

using namespace std;

// Node structure to represent each grid cell
struct Node {
    int x, y;
    int g;  // Cost from start to current node
    int h;  // Heuristic cost to goal
    int f;  // Total cost (g + h)
    Node* parent;

    Node(int x, int y, int g, int h, Node* parent = nullptr)
        : x(x), y(y), g(g), h(h), parent(parent), f(g + h) {}

    bool operator>(const Node& other) const {
        return f > other.f;  // Priority queue sorts by f value
    }
};

// Heuristic function to calculate Manhattan distance
int heuristic(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2);
}

// Check if a cell is within grid bounds
bool isInBounds(int x, int y, int rows, int cols) {
    return x >= 0 && y >= 0 && x < rows && y < cols;
}

// A* algorithm implementation
vector<pair<int, int>> a_star(const pair<int, int>& start, const pair<int, int>& goal, const vector<vector<int>>& grid) {
    int rows = grid.size();
    int cols = grid[0].size();

    priority_queue<Node, vector<Node>, greater<Node>> openList;
    unordered_set<int> closedList;
    unordered_map<int, Node*> allNodes;  // To track nodes and avoid duplicates

    auto encode = [&](int x, int y) { return x * cols + y; };
    auto decode = [&](int code) { return make_pair(code / cols, code % cols); };

    // Start node
    Node* startNode = new Node(start.first, start.second, 0, heuristic(start.first, start.second, goal.first, goal.second));
    openList.push(*startNode);
    allNodes[encode(start.first, start.second)] = startNode;

    while (!openList.empty()) {
        Node* current = new Node(openList.top());
        openList.pop();

        if (current->x == goal.first && current->y == goal.second) {
            vector<pair<int, int>> path;
            while (current != nullptr) {
                path.push_back(make_pair(current->x, current->y));
                current = current->parent;
            }
            reverse(path.begin(), path.end());  // Reverse path to go from start to goal
            return path;
        }

        closedList.insert(encode(current->x, current->y));

        // Explore neighbors (4 directions: left, right, up, down)
        vector<pair<int, int>> directions = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};
        for (const auto& dir : directions) {
            int nx = current->x + dir.first;
            int ny = current->y + dir.second;

            if (isInBounds(nx, ny, rows, cols) && grid[nx][ny] == 0 && closedList.find(encode(nx, ny)) == closedList.end()) {
                int gNew = current->g + 1;  // Cost to reach neighbor
                int hNew = heuristic(nx, ny, goal.first, goal.second);
                Node* neighbor = new Node(nx, ny, gNew, hNew, current);

                if (allNodes.find(encode(nx, ny)) == allNodes.end()) {
                    openList.push(*neighbor);
                    allNodes[encode(nx, ny)] = neighbor;
                }
            }
        }
    }

    return {};  // No path found
}

int main() {
    vector<vector<int>> grid = {
        {0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0}
    };

    pair<int, int> start = {0, 0};  // Start position
    pair<int, int> goal = {4, 4};   // Goal position

    vector<pair<int, int>> path = a_star(start, goal, grid);

    if (!path.empty()) {
        cout << "Path found: \n";
        for (const auto& p : path) {
            cout << "(" << p.first << ", " << p.second << ")\n";
        }
    } else {
        cout << "No path found.\n";
    }

    return 0;
}
