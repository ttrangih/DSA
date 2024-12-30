//22521514 Nguyen Thuy Trang - LAB6_ex8

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

class Graph {
    int V; // Number of vertices
    list<pair<int, double>> *adj; // Adjacency list with weights

public:
    Graph(int V);
    void addEdge(int v, int w, double weight);
    vector<int> louvainMethod();
    double modularity(vector<int> &communities);
};

Graph::Graph(int V) {
    this->V = V;
    adj = new list<pair<int, double>>[V];
}

void Graph::addEdge(int v, int w, double weight) {
    adj[v].push_back({w, weight});
    adj[w].push_back({v, weight}); // Since the graph is undirected
}

vector<int> Graph::louvainMethod() {
    vector<int> communities(V);
    for (int i = 0; i < V; ++i) {
        communities[i] = i;
    }

    bool improvement = true;
    while (improvement) {
        improvement = false;
        for (int i = 0; i < V; ++i) {
            map<int, double> communityWeights;
            for (auto &neighbor : adj[i]) {
                int community = communities[neighbor.first];
                communityWeights[community] += neighbor.second;
            }

            int bestCommunity = communities[i];
            double bestIncrease = 0.0;
            for (auto &cw : communityWeights) {
                int community = cw.first;
                double increase = cw.second - adj[i].size();
                if (increase > bestIncrease) {
                    bestCommunity = community;
                    bestIncrease = increase;
                }
            }

            if (bestCommunity != communities[i]) {
                communities[i] = bestCommunity;
                improvement = true;
            }
        }
    }

    return communities;
}

double Graph::modularity(vector<int> &communities) {
    double mod = 0.0;
    double m = 0.0;
    map<int, double> communityWeights;
    for (int i = 0; i < V; ++i) {
        for (auto &neighbor : adj[i]) {
            if (communities[i] == communities[neighbor.first]) {
                mod += neighbor.second;
            }
            m += neighbor.second;
            communityWeights[communities[i]] += neighbor.second;
        }
    }
    mod /= m;
    for (auto &cw : communityWeights) {
        mod -= (cw.second / m) * (cw.second / m);
    }
    return mod;
}

int main() {
    Graph g(5);
    g.addEdge(0, 1, 1.0);
    g.addEdge(0, 2, 1.0);
    g.addEdge(1, 2, 1.0);
    g.addEdge(1, 3, 1.0);
    g.addEdge(3, 4, 1.0);

    vector<int> communities = g.louvainMethod();

    // Output communities
    cout << "Node to Community Mapping:" << endl;
    for (int i = 0; i < communities.size(); ++i) {
        cout << "Node " << i << ": Community " << communities[i] << endl;
    }

    return 0;
}
