//22521514 Nguyen Thuy Trang - LAB6_ex9

#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

class PageRank {
public:
    // Constructor: takes the number of nodes and an adjacency list representation of the graph
    PageRank(int nodes, const vector<vector<int>>& adjList) {
        this->nodes = nodes;
        this->adjList = adjList;
        this->dampingFactor = 0.85;
        this->tolerance = 1e-6; // Convergence tolerance
        this->ranks = vector<double>(nodes, 1.0 / nodes); // Initial ranks
    }

    // Function to perform the PageRank algorithm
    void computePageRank() {
        vector<double> newRanks(nodes, 0.0);
        bool converged = false;

        while (!converged) {
            converged = true;

            // Iterate through each node
            for (int i = 0; i < nodes; i++) {
                double rankSum = 0.0;

                // For each node that points to 'i', add its contribution
                for (int j : adjList[i]) {
                    rankSum += ranks[j] / adjList[j].size();
                }

                // Calculate the new rank for node 'i'
                newRanks[i] = (1 - dampingFactor) / nodes + dampingFactor * rankSum;
            }

            // Check if the ranks have converged
            for (int i = 0; i < nodes; i++) {
                if (fabs(newRanks[i] - ranks[i]) > tolerance) {
                    converged = false;
                }
                ranks[i] = newRanks[i]; // Update the rank of node 'i'
            }
        }
    }

    // Function to print the computed PageRanks
    void printPageRanks() {
        cout << fixed << setprecision(6);
        for (int i = 0; i < nodes; i++) {
            cout << "Page " << i << ": " << ranks[i] << endl;
        }
    }

private:
    int nodes; // Number of nodes (web pages)
    vector<vector<int>> adjList; // Adjacency list of the graph
    vector<double> ranks; // Vector to store PageRank of each node
    double dampingFactor; // Damping factor (usually 0.85)
    double tolerance; // Convergence tolerance
};

int main() {
    // Example directed graph with 4 pages (nodes)
    // Adjacency list representation of the graph
    vector<vector<int>> adjList = {
        {1, 2}, // Page 0 links to Pages 1 and 2
        {2},    // Page 1 links to Page 2
        {0},    // Page 2 links to Page 0
        {1}     // Page 3 links to Page 1
    };

    // Create PageRank object
    PageRank pagerank(4, adjList);

    // Compute PageRank values
    pagerank.computePageRank();

    // Print the computed PageRank values
    pagerank.printPageRanks();

    return 0;
}
