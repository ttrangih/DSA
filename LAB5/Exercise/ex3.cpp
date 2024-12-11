#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;

    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class BinaryTree {
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

    Node* search(Node* current, int value) {
        if (!current || current->value == value) {
            return current;
        }
        if (value < current->value) {
            return search(current->left, value);
        }
        return search(current->right, value);
    }

    Node* deleteNode(Node* current, int value) {
        if (!current) {
            return current;
        }
        if (value < current->value) {
            current->left = deleteNode(current->left, value);
        } else if (value > current->value) {
            current->right = deleteNode(current->right, value);
        } else {
            if (!current->left) {
                Node* temp = current->right;
                delete current;
                return temp;
            } else if (!current->right) {
                Node* temp = current->left;
                delete current;
                return temp;
            }

            Node* temp = minValueNode(current->right);
            current->value = temp->value;
            current->right = deleteNode(current->right, temp->value);
        }
        return current;
    }

    Node* minValueNode(Node* node) {
        Node* current = node;
        while (current && current->left) {
            current = current->left;
        }
        return current;
    }

    void inorder(Node* current, vector<int>& result) {
        if (current) {
            inorder(current->left, result);
            result.push_back(current->value);
            inorder(current->right, result);
        }
    }

    int height(Node* node) {
        if (!node) return 0;
        return 1 + max(height(node->left), height(node->right));
    }

    bool isBalanced(Node* node) {
        if (!node) return true;

        int leftHeight = height(node->left);
        int rightHeight = height(node->right);

        if (abs(leftHeight - rightHeight) > 1) return false;

        return isBalanced(node->left) && isBalanced(node->right);
    }

public:
    BinaryTree() : root(nullptr) {}

    void insert(int value) {
        root = insert(root, value);
    }

    bool search(int value) {
        return search(root, value) != nullptr;
    }

    void deleteValue(int value) {
        root = deleteNode(root, value);
    }

    vector<int> inorderTraversal() {
        vector<int> result;
        inorder(root, result);
        return result;
    }

    int getHeight() {
        return height(root);
    }

    bool isHeightBalanced() {
        return isBalanced(root);
    }
};

int main() {
    BinaryTree tree;
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(2);
    tree.insert(7);

    vector<int> inorder = tree.inorderTraversal();
    cout << "Inorder Traversal: ";
    for (int val : inorder) {
        cout << val << " ";
    }
    cout << endl;

    cout << "Tree Height: " << tree.getHeight() << endl;
    cout << "Is Height Balanced: " << (tree.isHeightBalanced() ? "Yes" : "No") << endl;

    tree.insert(20);
    tree.insert(25);

    cout << "Tree Height After Insertion: " << tree.getHeight() << endl;
    cout << "Is Height Balanced After Insertion: " << (tree.isHeightBalanced() ? "Yes" : "No") << endl;

    return 0;
}
