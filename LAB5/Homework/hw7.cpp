#include <iostream>
#include <string>
using namespace std;

// Employee Node
struct EmployeeNode {
    string name;
    EmployeeNode* subordinates[10];
    int subCount;

    EmployeeNode(string empName) : name(empName), subCount(0) {}
};

// Add subordinate to an employee
void addSubordinate(EmployeeNode* manager, EmployeeNode* subordinate) {
    if (manager->subCount < 10) {
        manager->subordinates[manager->subCount++] = subordinate;
    } else {
        cout << "Max subordinates reached for " << manager->name << endl;
    }
}

// Print Organizational Chart
void printChart(EmployeeNode* root, int level = 0) {
    for (int i = 0; i < level; i++) cout << "  ";
    cout << root->name << endl;
    for (int i = 0; i < root->subCount; i++) {
        printChart(root->subordinates[i], level + 1);
    }
}

int main() {
    EmployeeNode* ceo = new EmployeeNode("CEO");
    EmployeeNode* vp1 = new EmployeeNode("VP1");
    EmployeeNode* vp2 = new EmployeeNode("VP2");
    EmployeeNode* manager1 = new EmployeeNode("Manager1");
    EmployeeNode* manager2 = new EmployeeNode("Manager2");

    addSubordinate(ceo, vp1);
    addSubordinate(ceo, vp2);
    addSubordinate(vp1, manager1);
    addSubordinate(vp2, manager2);

    cout << "Organizational Chart:\n";
    printChart(ceo);

    return 0;
}
