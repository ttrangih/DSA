#include <iostream>
#include <string>
using namespace std;

// Helper function to compute a simple hash
string hashFunction(const string& data) {
    unsigned long hash = 5381;
    for (char c : data) {
        hash = ((hash << 5) + hash) + c;
    }
    return to_string(hash);
}

// Merkle Tree Node
struct MerkleNode {
    string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(string data) : hash(hashFunction(data)), left(nullptr), right(nullptr) {}
    MerkleNode(MerkleNode* l, MerkleNode* r) : left(l), right(r) {
        hash = hashFunction(l->hash + r->hash);
    }
};

// Build Merkle Tree recursively
MerkleNode* buildMerkleTree(string data[], int start, int end) {
    if (start == end) {
        return new MerkleNode(data[start]);
    }

    int mid = (start + end) / 2;
    MerkleNode* left = buildMerkleTree(data, start, mid);
    MerkleNode* right = buildMerkleTree(data, mid + 1, end);

    return new MerkleNode(left, right);
}

// Print Merkle Tree (preorder traversal)
void printMerkleTree(MerkleNode* root) {
    if (!root) return;
    cout << "Hash: " << root->hash << endl;
    printMerkleTree(root->left);
    printMerkleTree(root->right);
}

int main() {
    string data[] = {"Block1", "Block2", "Block3", "Block4"};
    int n = sizeof(data) / sizeof(data[0]);

    MerkleNode* root = buildMerkleTree(data, 0, n - 1);

    cout << "Merkle Tree Root Hash: " << root->hash << endl;
    cout << "Merkle Tree Structure:\n";
    printMerkleTree(root);

    return 0;
}
