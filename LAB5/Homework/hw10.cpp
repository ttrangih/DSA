#include <iostream>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEndOfWord;

    TrieNode() : isEndOfWord(false) {
        for (int i = 0; i < 26; i++) children[i] = nullptr;
    }
};

class Trie {
private:
    TrieNode* root;

public:
    Trie() {
        root = new TrieNode();
    }

    void insert(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) {
                node->children[index] = new TrieNode();
            }
            node = node->children[index];
        }
        node->isEndOfWord = true;
    }

    bool search(const string& word) {
        TrieNode* node = root;
        for (char ch : word) {
            int index = ch - 'a';
            if (!node->children[index]) return false;
            node = node->children[index];
        }
        return node->isEndOfWord;
    }
};

int main() {
    Trie trie;
    trie.insert("hello");
    trie.insert("world");

    cout << "Search for 'hello': " << (trie.search("hello") ? "Found" : "Not Found") << endl;
    cout << "Search for 'world': " << (trie.search("world") ? "Found" : "Not Found") << endl;
    cout << "Search for 'notfound': " << (trie.search("notfound") ? "Found" : "Not Found") << endl;

    return 0;
}
