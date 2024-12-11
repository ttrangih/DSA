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

// Function to perform level-order traversal and group values by levels
void levelOrderTraversal(Node* root, int levels[][100], int& maxLevels) {
    if (!root) return;

    // Manual queue using an array
    Node* queue[100];
    int front = 0, rear = 0;

    // Start with the root node
    queue[rear++] = root;

    maxLevels = 0;  // Initialize level count

    while (front < rear) {
        int levelSize = rear - front;  // Number of nodes at the current level
        int index = 0;

        for (int i = 0; i < levelSize; ++i) {
            Node* currentNode = queue[front++];  // Dequeue front element
            levels[maxLevels][index++] = currentNode->key;

            // Enqueue left and right children
            if (currentNode->left) {
                queue[rear++] = currentNode->left;
            }
            if (currentNode->right) {
                queue[rear++] = currentNode->right;
            }
        }
        levels[maxLevels][index] = -1;  // Mark end of this level
        maxLevels++;
    }
}

// Function to print levels
void printLevels(int levels[][100], int maxLevels) {
    for (int i = 0; i < maxLevels; ++i) {
        cout << "Level " << i + 1 << ": ";
        for (int j = 0; levels[i][j] != -1; ++j) {
            cout << levels[i][j] << " ";
        }
        cout << endl;
    }
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

    // Perform level-order traversal and store values
    int levels[100][100];  // Static 2D array for storing levels
    int maxLevels = 0;

    levelOrderTraversal(root, levels, maxLevels);

    // Print the levels
    cout << "Level-order Traversal (Grouped by Levels):\n";
    printLevels(levels, maxLevels);

    return 0;
}
