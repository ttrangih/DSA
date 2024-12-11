#include <iostream>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinarySearchTree {
private:
    Node* root;

    Node* insert(Node* current, int value) {
        if (!current) {
            return new Node(value);
        }
        if (value < current->value) {
            current->left = insert(current->left, value);
        } else {
            current->right = insert(current->right, value);
        }
        return current;
    }

    Node* findLCA(Node* node, int n1, int n2) {
        if (!node) return nullptr;

        // If both n1 and n2 are smaller than node, LCA lies in the left subtree
        if (n1 < node->value && n2 < node->value) {
            return findLCA(node->left, n1, n2);
        }

        // If both n1 and n2 are greater than node, LCA lies in the right subtree
        if (n1 > node->value && n2 > node->value) {
            return findLCA(node->right, n1, n2);
        }

        // If neither of the above cases, the current node is the LCA
        return node;
    }

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    Node* lowestCommonAncestor(int n1, int n2) {
        return findLCA(root, n1, n2);
    }
};

int main() {
    BinarySearchTree tree;
    tree.insert(20);
    tree.insert(10);
    tree.insert(30);
    tree.insert(5);
    tree.insert(15);
    tree.insert(25);
    tree.insert(35);

    Node* lca = tree.lowestCommonAncestor(5, 15);
    if (lca) {
        cout << "Lowest Common Ancestor of 5 and 15: " << lca->value << endl;
    } else {
        cout << "Lowest Common Ancestor not found." << endl;
    }

    lca = tree.lowestCommonAncestor(5, 35);
    if (lca) {
        cout << "Lowest Common Ancestor of 5 and 35: " << lca->value << endl;
    } else {
        cout << "Lowest Common Ancestor not found." << endl;
    }

    return 0;
}
