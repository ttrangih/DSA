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

// Define a manual value for INT_MIN (minimum integer value)
const int MIN_INT = -2147483648;

// Helper function to find the maximum of two integers
int maxValue(int a, int b) {
    return (a > b) ? a : b;
}

// Function to calculate the maximum path sum in the binary tree
int findMaxPathSum(Node* node, int& globalMax) {
    if (!node) {
        return 0;
    }

    // Recursively find the maximum path sum for the left and right subtrees
    int leftMax = maxValue(0, findMaxPathSum(node->left, globalMax));  // Only consider positive paths
    int rightMax = maxValue(0, findMaxPathSum(node->right, globalMax));

    // Update the global maximum path sum if the current node forms a higher path
    globalMax = maxValue(globalMax, leftMax + rightMax + node->key);

    // Return the maximum path sum for the current node's parent to consider
    return node->key + maxValue(leftMax, rightMax);
}

// Wrapper function to initiate the calculation
int getMaxPathSum(Node* root) {
    int globalMax = MIN_INT;  // Initialize global max to the smallest integer value
    findMaxPathSum(root, globalMax);
    return globalMax;
}

// Helper function to manually create a binary tree
Node* createTree() {
    Node* root = new Node(10);
    root->left = new Node(2);
    root->right = new Node(10);
    root->left->left = new Node(20);
    root->left->right = new Node(1);
    root->right->right = new Node(-25);
    root->right->right->left = new Node(3);
    root->right->right->right = new Node(4);
    return root;
}

// Helper function to insert a value into the BST
Node* insert(Node* root, int value) {
    if (!root) {
        return new Node(value);
    }
    if (value < root->key) {
        root->left = insert(root->left, value);
    } else if (value > root->key) {
        root->right = insert(root->right, value);
    }
    return root;
}

// Function to print the BST structure
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

// Main Function
int main() {
    Node* root = createTree();

    cout << "Binary Search Tree Structure:\n";
    printTree(root);

    // Find and display the maximum path sum
    cout << "Maximum Path Sum: " << getMaxPathSum(root) << endl;

    return 0;
}
