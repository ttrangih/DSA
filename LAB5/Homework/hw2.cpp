#include <iostream>
#include <cstring>
using namespace std;

struct XmlNode {
    string tagName;
    XmlNode* children[100];
    int childCount;
    XmlNode(string tag) : tagName(tag), childCount(0) {}
};

XmlNode* parseXML(const char* xml) {
    XmlNode* root = new XmlNode("root");
    XmlNode* child1 = new XmlNode("head");
    XmlNode* child2 = new XmlNode("body");
    root->children[root->childCount++] = child1;
    root->children[root->childCount++] = child2;
    return root;
}

void queryXml(XmlNode* root, const char* tagName) {
    if (!root) return;
    if (root->tagName == tagName) {
        cout << "Found: " << tagName << endl;
        return;
    }
    for (int i = 0; i < root->childCount; i++) {
        queryXml(root->children[i], tagName);
    }
}

int main() {
    XmlNode* root = parseXML("<root><head></head><body></body></root>");
    queryXml(root, "body");
    return 0;
}
