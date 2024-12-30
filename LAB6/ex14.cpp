#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <algorithm>
using namespace std;

class RecommendationSystem {
private:
    unordered_map<int, unordered_set<int>> userItemGraph; // User-item interaction graph

public:
    // Add interaction between user and item
    void addInteraction(int user, int item) {
        userItemGraph[user].insert(item);
    }

    // Calculate Jaccard similarity between two users
    double jaccardSimilarity(int user1, int user2) {
        if (userItemGraph.find(user1) == userItemGraph.end() ||
            userItemGraph.find(user2) == userItemGraph.end()) {
            return 0.0;
        }

        const auto& items1 = userItemGraph[user1];
        const auto& items2 = userItemGraph[user2];

        unordered_set<int> intersection;
        for (int item : items1) {
            if (items2.count(item)) {
                intersection.insert(item);
            }
        }

        unordered_set<int> unionSet = items1;
        unionSet.insert(items2.begin(), items2.end());

        if (unionSet.empty()) return 0.0;
        return static_cast<double>(intersection.size()) / unionSet.size();
    }

    // Recommend items for a user based on neighbors' preferences
    vector<int> recommend(int user, int topK = 5) {
        unordered_map<int, double> itemScores;

        // Calculate similarity with other users
        for (const auto& [otherUser, items] : userItemGraph) {
            if (user == otherUser) continue;

            double similarity = jaccardSimilarity(user, otherUser);
            if (similarity <= 0) continue;

            // Score items from the similar user
            for (int item : items) {
                if (userItemGraph[user].count(item) == 0) { // Skip items already interacted
                    itemScores[item] += similarity;
                }
            }
        }

        // Sort items by score
        vector<pair<int, double>> scoredItems(itemScores.begin(), itemScores.end());
        sort(scoredItems.begin(), scoredItems.end(),
             [](const pair<int, double>& a, const pair<int, double>& b) {
                 return a.second > b.second;
             });

        // Get top K recommendations
        vector<int> recommendations;
        for (int i = 0; i < min(topK, (int)scoredItems.size()); ++i) {
            recommendations.push_back(scoredItems[i].first);
        }
        return recommendations;
    }

    void printGraph() {
        for (const auto& [user, items] : userItemGraph) {
            cout << "User " << user << ": ";
            for (int item : items) {
                cout << item << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    RecommendationSystem rs;

    // Add user-item interactions
    rs.addInteraction(1, 101);
    rs.addInteraction(1, 102);
    rs.addInteraction(1, 103);

    rs.addInteraction(2, 101);
    rs.addInteraction(2, 104);
    rs.addInteraction(2, 105);

    rs.addInteraction(3, 102);
    rs.addInteraction(3, 106);

    rs.addInteraction(4, 104);
    rs.addInteraction(4, 105);
    rs.addInteraction(4, 106);

    cout << "User-Item Graph:" << endl;
    rs.printGraph();

    // Recommend items for user 1
    cout << "\nRecommendations for User 1:" << endl;
    vector<int> recommendations = rs.recommend(1, 3);
    for (int item : recommendations) {
        cout << "Item " << item << endl;
    }

    return 0;
}
