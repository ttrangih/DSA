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

// Function to search for an element in an array
int search(int arr[], int start, int end, int value) {
    for (int i = start; i <= end; i++) {
        if (arr[i] == value) {
            return i;
        }
    }
    return -1;
}

// Recursive function to build the binary tree
Node* buildTree(int inorder[], int postorder[], int inStart, int inEnd, int& postIndex) {
    if (inStart > inEnd) {
        return nullptr;
    }

    // The current node is the last element in postorder array
    int current = postorder[postIndex--];
    Node* node = new Node(current);

    // If the node has no children, return it
    if (inStart == inEnd) {
        return node;
    }

    // Find the index of the current node in the inorder array
    int inIndex = search(inorder, inStart, inEnd, current);

    // Recursively build the right and left subtrees
    node->right = buildTree(inorder, postorder, inIndex + 1, inEnd, postIndex);
    node->left = buildTree(inorder, postorder, inStart, inIndex - 1, postIndex);

    return node;
}

// Function to print the tree in preorder traversal (for validation)
void preorder(Node* root) {
    if (!root) return;

    cout << root->key << " ";
    preorder(root->left);
    preorder(root->right);
}

// Function to print the binary tree structure
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
    // Define the inorder and postorder traversal arrays
    int inorder[] = {9, 3, 15, 20, 7};
    int postorder[] = {9, 15, 7, 20, 3};
    int n = sizeof(inorder) / sizeof(inorder[0]);

    // Reconstruct the tree
    int postIndex = n - 1;
    Node* root = buildTree(inorder, postorder, 0, n - 1, postIndex);

    // Print the reconstructed tree in preorder traversal
    cout << "Reconstructed Tree (Preorder Traversal): ";
    preorder(root);
    cout << endl;

    // Print the reconstructed tree structure
    cout << "\nReconstructed Tree Structure:\n";
    printTree(root);

    return 0;
}
