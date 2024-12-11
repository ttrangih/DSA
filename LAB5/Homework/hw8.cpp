#include <iostream>
#include <string>
using namespace std;

struct Transaction {
    string data;
    Transaction(string data) : data(data) {}
};

// Merkle Tree Node for Blockchain
struct MerkleNode {
    string hash;
    MerkleNode* left;
    MerkleNode* right;

    MerkleNode(string data) : hash(hashFunction(data)), left(nullptr), right(nullptr) {}
    MerkleNode(MerkleNode* l, MerkleNode* r) : left(l), right(r) {
        hash = hashFunction(l->hash + r->hash);
    }

    static string hashFunction(const string& data) {
        unsigned long hash = 5381;
        for (char c : data) {
            hash = ((hash << 5) + hash) + c;
        }
        return to_string(hash);
    }
};

MerkleNode* buildMerkleTree(Transaction transactions[], int start, int end) {
    if (start == end) {
        return new MerkleNode(transactions[start].data);
    }

    int mid = (start + end) / 2;
    MerkleNode* left = buildMerkleTree(transactions, start, mid);
    MerkleNode* right = buildMerkleTree(transactions, mid + 1, end);

    return new MerkleNode(left, right);
}

int main() {
    Transaction transactions[] = {
        Transaction("Tx1"), Transaction("Tx2"), Transaction("Tx3"), Transaction("Tx4")
    };
    int n = sizeof(transactions) / sizeof(transactions[0]);

    MerkleNode* root = buildMerkleTree(transactions, 0, n - 1);
    cout << "Blockchain Merkle Tree Root Hash: " << root->hash << endl;

    return 0;
}
