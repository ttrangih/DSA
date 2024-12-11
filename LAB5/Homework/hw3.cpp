#include <iostream>
#include <cstring>
using namespace std;

struct HuffmanNode {
    char ch;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char ch, int freq) : ch(ch), freq(freq), left(nullptr), right(nullptr) {}
};

struct PriorityQueue {
    HuffmanNode* nodes[100];
    int size;

    PriorityQueue() : size(0) {}

    void push(HuffmanNode* node) {
        nodes[size++] = node;
        for (int i = size - 1; i > 0; i--) {
            if (nodes[i]->freq < nodes[i - 1]->freq) {
                swap(nodes[i], nodes[i - 1]);
            }
        }
    }

    HuffmanNode* pop() {
        return nodes[--size];
    }

    bool empty() {
        return size == 0;
    }
};

HuffmanNode* buildHuffmanTree(const char* text) {
    int freq[256] = {0};
    for (int i = 0; text[i] != '\0'; i++) {
        freq[text[i]]++;
    }

    PriorityQueue pq;
    for (int i = 0; i < 256; i++) {
        if (freq[i] > 0) {
            pq.push(new HuffmanNode((char)i, freq[i]));
        }
    }

    while (pq.size > 1) {
        HuffmanNode* left = pq.pop();
        HuffmanNode* right = pq.pop();
        HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
        parent->left = left;
        parent->right = right;
        pq.push(parent);
    }

    return pq.pop();
}

void encodeHuffman(HuffmanNode* root, char* code, int depth, char codes[256][256]) {
    if (!root) return;

    if (root->ch != '\0') {
        code[depth] = '\0';
        strcpy(codes[(unsigned char)root->ch], code);
    }

    code[depth] = '0';
    encodeHuffman(root->left, code, depth + 1, codes);

    code[depth] = '1';
    encodeHuffman(root->right, code, depth + 1, codes);
}

int main() {
    const char* text = "huffman coding";
    HuffmanNode* root = buildHuffmanTree(text);

    char codes[256][256] = {0};
    char code[256];
    encodeHuffman(root, code, 0, codes);

    cout << "Huffman Codes:\n";
    for (int i = 0; i < 256; i++) {
        if (codes[i][0] != '\0') {
            cout << (char)i << ": " << codes[i] << endl;
        }
    }

    return 0;
}
