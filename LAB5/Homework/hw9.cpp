#include <iostream>
#include <string>
using namespace std;

// Node structure for Phylogenetic Tree
struct PhyloNode {
    string species;
    PhyloNode* left;
    PhyloNode* right;

    PhyloNode(string s) : species(s), left(nullptr), right(nullptr) {}
};

void printPhyloTree(PhyloNode* root, int level = 0) {
    if (!root) return;
    for (int i = 0; i < level; i++) cout << "  ";
    cout << root->species << endl;
    printPhyloTree(root->left, level + 1);
    printPhyloTree(root->right, level + 1);
}

int main() {
    PhyloNode* root = new PhyloNode("Root");
    root->left = new PhyloNode("Species1");
    root->right = new PhyloNode("Species2");
    root->left->left = new PhyloNode("Subspecies1A");
    root->left->right = new PhyloNode("Subspecies1B");

    cout << "Phylogenetic Tree:\n";
    printPhyloTree(root);

    return 0;
}
