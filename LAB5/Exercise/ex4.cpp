#include <iostream>
using namespace std;

struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) {
        key = value;
        left = right = nullptr;
    }
};

// Helper function to find the maximum of two numbers
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the diameter of a binary tree
int calculateDiameter(Node* node, int& maxDiameter) {
    if (!node) return 0;

    // Recursively find the height of left and right subtrees
    int leftHeight = calculateDiameter(node->left, maxDiameter);
    int rightHeight = calculateDiameter(node->right, maxDiameter);

    // Update the maximum diameter (longest path)
    maxDiameter = maxValue(maxDiameter, leftHeight + rightHeight + 1);

    // Return the height of the current node
    return 1 + maxValue(leftHeight, rightHeight);
}

int findDiameter(Node* root) {
    int maxDiameter = 0;
    calculateDiameter(root, maxDiameter);
    return maxDiameter;
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
    root->left->left->left = new Node(80);
    root->left->left->right = new Node(90);
    return root;
}

// Main Function
int main() {
    // Manually create the binary tree
    Node* root = createTree();

    cout << "Diameter of the tree: " << findDiameter(root) << endl;

    return 0;
}
