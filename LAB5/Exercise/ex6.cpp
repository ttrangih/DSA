#include <iostream>
#include <cmath>
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

// Helper function to calculate the height of the tree
int calculateHeight(Node* node) {
    if (!node) {
        return 0;  // Height of an empty tree is 0
    }

    // Recursively calculate the height of left and right subtrees
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    // Return the height of the current node
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Function to determine if a binary tree is height-balanced
bool isHeightBalanced(Node* node) {
    if (!node) {
        return true;  // An empty tree is balanced
    }

    // Calculate the height of left and right subtrees
    int leftHeight = calculateHeight(node->left);
    int rightHeight = calculateHeight(node->right);

    // Check if the current node is balanced
    if (abs(leftHeight - rightHeight) > 1) {
        return false;  // The tree is not balanced
    }

    // Recursively check the left and right subtrees
    return isHeightBalanced(node->left) && isHeightBalanced(node->right);
}

// Function to print the binary tree
void printTree(Node* node, int depth = 0) {
    if (!node) {
        return;
    }

    // Print the right subtree with increased depth
    printTree(node->right, depth + 1);

    // Print current node with indentation
    for (int i = 0; i < depth; ++i) {
        cout << "   ";
    }
    cout << node->key << endl;

    // Print the left subtree with increased depth
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
    // Manually create a binary tree
    Node* root = createTree();

    // Print the binary tree
    cout << "Binary Tree Structure:\n";
    printTree(root);

    // Check if the tree is height-balanced
    if (isHeightBalanced(root)) {
        cout << "The tree is height-balanced.\n";
    } else {
        cout << "The tree is not height-balanced.\n";
    }

    return 0;
}
