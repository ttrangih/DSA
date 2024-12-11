#include <iostream>
#include <cstring>
using namespace std;

struct FileNode {
    string name;
    bool isFile;
    FileNode* children[100];
    int childCount;

    FileNode(string name, bool isFile) : name(name), isFile(isFile), childCount(0) {}
};

class FileSystem {
private:
    FileNode* root;
    FileNode* currentDir;

    FileNode* findChild(FileNode* node, const string& name) {
        for (int i = 0; i < node->childCount; i++) {
            if (node->children[i]->name == name) return node->children[i];
        }
        return nullptr;
    }

public:
    FileSystem() {
        root = new FileNode("/", false);
        currentDir = root;
    }

    void list() {
        cout << "Contents of '" << currentDir->name << "':\n";
        for (int i = 0; i < currentDir->childCount; i++) {
            cout << (currentDir->children[i]->isFile ? "File: " : "Dir: ")
                 << currentDir->children[i]->name << endl;
        }
    }

    void create(string name, bool isFile) {
        if (findChild(currentDir, name)) {
            cout << "Error: Already exists.\n";
            return;
        }
        FileNode* newNode = new FileNode(name, isFile);
        currentDir->children[currentDir->childCount++] = newNode;
        cout << (isFile ? "File" : "Directory") << " created: " << name << endl;
    }

    void deleteItem(string name) {
        for (int i = 0; i < currentDir->childCount; i++) {
            if (currentDir->children[i]->name == name) {
                delete currentDir->children[i];
                for (int j = i; j < currentDir->childCount - 1; j++) {
                    currentDir->children[j] = currentDir->children[j + 1];
                }
                currentDir->childCount--;
                cout << "Deleted: " << name << endl;
                return;
            }
        }
        cout << "Error: Not found.\n";
    }
};

int main() {
    FileSystem fs;
    fs.create("docs", false);
    fs.create("file1.txt", true);
    fs.list();
    fs.deleteItem("docs");
    fs.list();
    return 0;
}
