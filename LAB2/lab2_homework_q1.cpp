#include <iostream>
#include <stack>
#include <cmath> // For pow function
using namespace std;

// Function to move a disk from one tower to another
void moveDisk(stack<int>& from, stack<int>& to, char fromTower, char toTower) {
    int diskFrom, diskTo;

    if (from.empty()) {
        diskTo = to.top();
        to.pop();
        from.push(diskTo);
        cout << "Move disk " << diskTo << " from " << toTower << " to " << fromTower << endl;
    } else if (to.empty()) {
        diskFrom = from.top();
        from.pop();
        to.push(diskFrom);
        cout << "Move disk " << diskFrom << " from " << fromTower << " to " << toTower << endl;
    } else {
        diskFrom = from.top();
        diskTo = to.top();

        if (diskFrom > diskTo) {
            from.pop();
            from.push(diskTo);
            to.pop();
            to.push(diskFrom);
            cout << "Move disk " << diskTo << " from " << toTower << " to " << fromTower << endl;
        } else {
            from.pop();
            to.push(diskFrom);
            cout << "Move disk " << diskFrom << " from " << fromTower << " to " << toTower << endl;
        }
    }
}

// Function to implement the iterative solution to the Towers of Hanoi problem
void iterativeHanoi(int n) {
    stack<int> src, dest, aux; // Stacks representing towers: src (A), dest (C), aux (B)
    char s = 'A', d = 'C', a = 'B'; // Tower names

    // Push disks into the source tower in descending order
    for (int i = n; i >= 1; i--)
        src.push(i);

    // Calculate total number of moves
    int totalMoves = pow(2, n) - 1;

    // If number of disks is even, swap destination and auxiliary
    if (n % 2 == 0)
        swap(d, a);

    // Iterate over the total number of moves
    for (int i = 1; i <= totalMoves; i++) {
        if (i % 3 == 1)
            moveDisk(src, dest, s, d); // Move between source and destination
        else if (i % 3 == 2)
            moveDisk(src, aux, s, a); // Move between source and auxiliary
        else if (i % 3 == 3)
            moveDisk(aux, dest, a, d); // Move between auxiliary and destination
    }
}

int main() {
    int n;
    cout << "Enter the number of disks: ";
    cin >> n;
    cout << "The sequence of moves involved are:\n";
    iterativeHanoi(n);
    return 0;
}
