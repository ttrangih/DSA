#include <iostream>
using namespace std;

// Node structure
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Structure to store nodes with horizontal distance
struct NodeWithHD {
    Node* node;
    int hd; // Horizontal distance
};

// Recursive function to find the minimum and maximum horizontal distances
void findMinMaxHD(Node* node, int hd, int& minHD, int& maxHD) {
    if (!node) return;

    // Update min and max horizontal distances
    if (hd < minHD) minHD = hd;
    if (hd > maxHD) maxHD = hd;

    // Recursively find in left and right subtrees
    findMinMaxHD(node->left, hd - 1, minHD, maxHD);
    findMinMaxHD(node->right, hd + 1, minHD, maxHD);
}

// Recursive function to collect nodes for a given horizontal distance
void collectNodesAtHD(Node* node, int hd, int targetHD, int result[], int& index) {
    if (!node) return;

    // If the node is at the target horizontal distance, add it to the result
    if (hd == targetHD) {
        result[index++] = node->key;
    }

    // Traverse left and right subtrees
    collectNodesAtHD(node->left, hd - 1, targetHD, result, index);
    collectNodesAtHD(node->right, hd + 1, targetHD, result, index);
}

// Function to perform vertical order traversal
void verticalOrderTraversal(Node* root) {
    if (!root) return;

    // Find the minimum and maximum horizontal distances
    int minHD = 0, maxHD = 0;
    findMinMaxHD(root, 0, minHD, maxHD);

    // Traverse for each horizontal distance
    for (int hd = minHD; hd <= maxHD; ++hd) {
        int result[100], index = 0; // Temporary array for storing nodes at this HD
        collectNodesAtHD(root, 0, hd, result, index);

        // Print the vertical slice
        cout << "Vertical Slice at HD " << hd << ": ";
        for (int i = 0; i < index; ++i) {
            cout << result[i] << " ";
        }
        cout << endl;
    }
}

// Function to print the tree structure
void printTree(Node* node, int depth = 0) {
    if (!node) return;

    // Print right subtree
    printTree(node->right, depth + 1);

    // Print current node
    for (int i = 0; i < depth; ++i) {
        cout << "   ";
    }
    cout << node->key << endl;

    // Print left subtree
    printTree(node->left, depth + 1);
}

// Helper function to manually create a binary tree
Node* createTree() {
    Node* root = new Node(10);
    root->left = new Node(20);
    root->right = new Node(30);
    root->left->left = new Node(40);
    root->left->right = new Node(50);
    root->right->left = new Node(60);
    root->right->right = new Node(70);
    return root;
}

// Main Function
int main() {
    // Manually create the binary tree
    Node* root = createTree();

    // Print the binary tree structure
    cout << "Binary Tree Structure:\n";
    printTree(root);

    // Perform vertical order traversal
    cout << "\nVertical Order Traversal:\n";
    verticalOrderTraversal(root);

    return 0;
}
