//SId: 22521514
//Nguyen Thuy Trang
//Homework 6

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
#include <cmath>

struct Point {
    std::vector<double> coords;

    Point(std::initializer_list<double> list) : coords(list) {}
};

struct KDTNode {
    Point point;
    KDTNode *left, *right;

    KDTNode(Point p) : point(p), left(nullptr), right(nullptr) {}
};

class KDTree {
    KDTNode *root;
    int k; // Number of dimensions

public:
    KDTree(int dimensions) : root(nullptr), k(dimensions) {}

    void insert(Point p) {
        root = insertRec(root, p, 0);
    }

    Point nearestNeighbor(Point target) {
        return nearestNeighborRec(root, target, 0, std::numeric_limits<double>::max(), root->point);
    }

private:
    KDTNode* insertRec(KDTNode* node, Point p, int depth) {
        if (node == nullptr) return new KDTNode(p);

        int axis = depth % k;
        if (p.coords[axis] < node->point.coords[axis]) {
            node->left = insertRec(node->left, p, depth + 1);
        } else {
            node->right = insertRec(node->right, p, depth + 1);
        }
        return node;
    }

    Point nearestNeighborRec(KDTNode* node, Point target, int depth, double &bestDist, Point bestPoint) {
        if (node == nullptr) return bestPoint;

        double dist = distance(node->point, target);
        if (dist < bestDist) {
            bestDist = dist;
            bestPoint = node->point;
        }

        int axis = depth % k;
        KDTNode *nearNode = (target.coords[axis] < node->point.coords[axis]) ? node->left : node->right;
        KDTNode *farNode = (target.coords[axis] < node->point.coords[axis]) ? node->right : node->left;

        bestPoint = nearestNeighborRec(nearNode, target, depth + 1, bestDist, bestPoint);

        if (fabs(target.coords[axis] - node->point.coords[axis]) < bestDist) {
            bestPoint = nearestNeighborRec(farNode, target, depth + 1, bestDist, bestPoint);
        }

        return bestPoint;
    }

    double distance(const Point &a, const Point &b) {
        double dist = 0.0;
        for (int i = 0; i < k; i++) {
            dist += (a.coords[i] - b.coords[i]) * (a.coords[i] - b.coords[i]);
        }
        return sqrt(dist);
    }
};

int main() {
    KDTree tree(2);
    tree.insert(Point{2, 3});
    tree.insert(Point{5, 4});
    tree.insert(Point{9, 6});
    tree.insert(Point{4, 7});
    tree.insert(Point{8, 1});
    tree.insert(Point{7, 2});

    Point nearest = tree.nearestNeighbor(Point{9, 2});
    std::cout << "Nearest Point: (" << nearest.coords[0] << ", " << nearest.coords[1] << ")\n";
    return 0;
}


#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Function to preprocess the pattern and compute the longest prefix suffix (LPS) array
void computeLPSArray(const string &pattern, vector<int> &lps) {
    int length = 0; // Length of the previous longest prefix suffix
    lps[0] = 0; // The first element of lps is always 0
    int i = 1;

    while (i < pattern.length()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // Use the previous LPS value
            } else {
                lps[i] = 0; // No prefix found
                i++;
            }
        }
    }
}

// Function to perform KMP search on the given text using the specified pattern
void KMPStringSearch(const string &text, const string &pattern) {
    vector<int> lps(pattern.length());
    computeLPSArray(pattern, lps); // Compute the LPS array

    int textIndex = 0; // Index for the text
    int patternIndex = 0; // Index for the pattern

    while (textIndex < text.length()) {
        if (pattern[patternIndex] == text[textIndex]) {
            textIndex++;
            patternIndex++;
        }

        if (patternIndex == pattern.length()) {
            cout << "Pattern found at index " << (textIndex - patternIndex) << "\n";
            patternIndex = lps[patternIndex - 1]; // Set patternIndex to the last matched position
        } else if (textIndex < text.length() && pattern[patternIndex] != text[textIndex]) {
            if (patternIndex != 0) {
                patternIndex = lps[patternIndex - 1]; // Use the previous LPS value
            } else {
                textIndex++; // Move to the next character in the text
            }
        }
    }
}

int main() {
    string text = "ABABDABACDABABCABAB"; // Text to search
    string pattern = "ABABCABAB"; // Pattern to find
    KMPStringSearch(text, pattern); // Perform the KMP search
    return 0;
}
