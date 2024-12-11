#include <iostream>
#include <vector>
#include <queue>
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

    void preorder(Node* current, vector<int>& result) {
        if (current) {
            result.push_back(current->value);
            preorder(current->left, result);
            preorder(current->right, result);
        }
    }

    void postorder(Node* current, vector<int>& result) {
        if (current) {
            postorder(current->left, result);
            postorder(current->right, result);
            result.push_back(current->value);
        }
    }

    vector<vector<int>> levelOrder(Node* root) {
        vector<vector<int>> result;
        if (!root) return result;

        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            int levelSize = q.size();
            vector<int> currentLevel;

            for (int i = 0; i < levelSize; ++i) {
                Node* currentNode = q.front();
                q.pop();
                currentLevel.push_back(currentNode->value);

                if (currentNode->left) q.push(currentNode->left);
                if (currentNode->right) q.push(currentNode->right);
            }

            result.push_back(currentLevel);
        }

        return result;
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

    vector<int> preorderTraversal() {
        vector<int> result;
        preorder(root, result);
        return result;
    }

    vector<int> postorderTraversal() {
        vector<int> result;
        postorder(root, result);
        return result;
    }

    vector<vector<int>> levelOrderTraversal() {
        return levelOrder(root);
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

    vector<int> preorder = tree.preorderTraversal();
    cout << "Preorder Traversal: ";
    for (int val : preorder) {
        cout << val << " ";
    }
    cout << endl;

    vector<int> postorder = tree.postorderTraversal();
    cout << "Postorder Traversal: ";
    for (int val : postorder) {
        cout << val << " ";
    }
    cout << endl;

    vector<vector<int>> levelOrder = tree.levelOrderTraversal();
    cout << "Level Order Traversal: \n";
    for (const auto& level : levelOrder) {
        for (int val : level) {
            cout << val << " ";
        }
        cout << endl;
    }

    return 0;
}
