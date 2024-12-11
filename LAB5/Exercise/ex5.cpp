#include <iostream>
using namespace std;

// Node structure for the binary tree
struct Node {
    int key;
    Node* left;
    Node* right;

    Node(int value) : key(value), left(nullptr), right(nullptr) {}
};

// Function to calculate the height of the binary tree
int calculateHeight(Node* root) {
    if (root == nullptr) {
        return 0; // Base case: height of an empty tree is 0
    }

    // Recursively calculate the height of the left and right subtrees
    int leftHeight = calculateHeight(root->left);
    int rightHeight = calculateHeight(root->right);

    // The height of the tree is the greater of the two subtree heights, plus 1 for the current node
    return 1 + max(leftHeight, rightHeight);
}

// Helper function to create a binary tree for testing
Node* createTree() {
    Node* root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);
    root->right->left = new Node(6);
    root->right->right = new Node(7);
    return root;
}

// Main function
int main() {
    Node* root = createTree();

    cout << "Height of the binary tree: " << calculateHeight(root) << endl;

    return 0;
}
