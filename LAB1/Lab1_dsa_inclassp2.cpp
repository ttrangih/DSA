#include <iostream>
#include<unordered_map>
using namespace std;

// Node class for linked list
class Node {
public:
    int data;
    Node* next;

    Node(int x) {
        data = x;
        next = nullptr;
    }
};

// LinkedList class
class LinkedList {
public:
    Node* head;

    LinkedList() : head(nullptr) {}

    // Function to add a node at the head
    void addNodeAtHead(int value) {
        Node* newNode = new Node(value);
        newNode->next = head;
        head = newNode;
    }

    // Function to add a node at the tail
    void addNodeAtTail(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = newNode;
            return;
        }
        Node* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }

    // Function to add a node at a specific position
    void addNodeAtPosition(int value, int position) {
        if (position == 0) {
            addNodeAtHead(value);
            return;
        }

        Node* newNode = new Node(value);
        Node* temp = head;
        for (int i = 0; i < position - 1 && temp != nullptr; i++) {
            temp = temp->next;
        }

        if (!temp) {
            cout << "Position is out of bounds!" << endl;
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        temp->next = newNode;
    }

    // Function to get the length of the list
    int getLength() {
        int len = 0;
        Node* temp = head;
        while (temp) {
            len++;
            temp = temp->next;
        }
        return len;
    }

    // Function to print the linked list
    void printList() {
        Node* temp = head;
        while (temp) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    // Function to add two numbers at random positions
    void addTwoNumbersAtRandomPositions(int value1, int value2) {
        int len = getLength();

        // Generate two random positions
        int pos1 = rand() % (len + 1); // Random position from 0 to len
        int pos2 = rand() % (len + 2); // Random position from 0 to len+1 (after adding first value)

        // Ensure pos1 and pos2 are different
        if (pos1 == pos2) {
            pos2 = (pos2 + 1) % (len + 2);
        }

        // Add the values at the generated positions
        addNodeAtPosition(value1, pos1);
        addNodeAtPosition(value2, pos2);

        cout << "Added " << value1 << " at position " << pos1 << endl;
        cout << "Added " << value2 << " at position " << pos2 << endl;
    }

    // Function to remove the N-th node from the end
    Node* removeNthFromEnd(Node* head, int n) {
        Node* dummy = new Node(0);
        dummy->next = head;
        Node* first = dummy;
        Node* second = dummy;

        for (int i = 0; i <= n; ++i) {
            if (first == nullptr) return head;
            first = first->next;
        }

        while (first != nullptr) {
            first = first->next;
            second = second->next;
        }

        second->next = second->next->next;
        return dummy->next;
    }

    // Function to separate odd and even nodes
    Node* separateOddEven(Node* head) {
        if (!head) return nullptr;

        Node* odd = head;
        Node* even = head->next;
        Node* evenHead = even;

        while (even && even->next) {
            odd->next = odd->next->next;
            even->next = even->next->next;
            odd = odd->next;
            even = even->next;
        }

        odd->next = evenHead;
        return head;
    }

    // Function to divide a linked list into k parts
    Node** divideList(Node* head, int k) {
        int len = 0;
        Node* temp = head;
        while (temp) {
            len++;
            temp = temp->next;
        }

        Node** parts = new Node*[k];
        int n = len / k, r = len % k;

        temp = head;
        for (int i = 0; i < k; ++i) {
            parts[i] = temp;
            int partSize = n + (i < r ? 1 : 0);
            for (int j = 0; j < partSize - 1; ++j) {
                if (temp) temp = temp->next;
            }
            if (temp) {
                Node* nextPart = temp->next;
                temp->next = nullptr;
                temp = nextPart;
            }
        }
        return parts;
    }

    // Function to remove zero-sum consecutive nodes
    Node* removeZeroSumSublists(Node* head) {
        Node* dummy = new Node(0);
        dummy->next = head;
        unordered_map<int, Node*> prefixMap;
        int prefixSum = 0;
        Node* curr = dummy;

        while (curr) {
            prefixSum += curr->data;
            if (prefixMap.find(prefixSum) != prefixMap.end()) {
                Node* prev = prefixMap[prefixSum];
                Node* temp = prev->next;
                int sum = prefixSum;
                while (temp != curr) {
                    sum += temp->data;
                    prefixMap.erase(sum);
                    temp = temp->next;
                }
                prev->next = curr->next;
            } else {
                prefixMap[prefixSum] = curr;
            }
            curr = curr->next;
        }

        return dummy->next;
    }

    // Function to swap nodes with values x and y
    void swapNodes(int x, int y) {
        if (x == y) {
            cout << "Both values are the same. No need to swap." << endl;
            return;
        }
        Node* prevX = nullptr, *currX = head;
        while (currX && currX->data != x) {
            prevX = currX;
            currX = currX->next;
        }

        Node* prevY = nullptr, *currY = head;
        while (currY && currY->data != y) {
            prevY = currY;
            currY = currY->next;
        }

        if (!currX || !currY) {
            cout << "One or both values not found in the list." << endl;
            return;
        }

        if (prevX) prevX->next = currY;
        else head = currY;

        if (prevY) prevY->next = currX;
        else head = currX;

        Node* temp = currX->next;
        currX->next = currY->next;
        currY->next = temp;
    }
};

int main() {
    LinkedList list;

    // Prepopulate the list with some values
    list.addNodeAtTail(5);
    list.addNodeAtTail(10);
    list.addNodeAtTail(15);
    list.addNodeAtTail(20);
    list.addNodeAtTail(25);

    int choice, n, k, x, y, value, value1, value2, position;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Add two values at random positions" << endl;
        cout << "2. Remove N-th Node from End" << endl;
        cout << "3. Separate Odd and Even Nodes" << endl;
        cout << "4. Divide Linked List into K Parts" << endl;
        cout << "5. Remove Zero-Sum Consecutive Nodes" << endl;
        cout << "6. Swap Nodes" << endl;
        cout << "7. Print List" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
            cout << "Enter the first value to add: ";
            cin >> value1;
            cout << "Enter the second value to add: ";
            cin >> value2;
            list.addTwoNumbersAtRandomPositions(value1, value2);
            list.printList();
            break;
        }
        case 2: {
            list.printList();
            cout << "Enter the position (N) from the end to remove: ";
            cin >> n;
            list.head = list.removeNthFromEnd(list.head, n);
            list.printList();
            break;
        }
        case 3: {
            list.head = list.separateOddEven(list.head);
            cout << "List after separating odd and even nodes: ";
            list.printList();
            break;
        }
        case 4: {
            list.printList();
            cout << "Enter the number of parts (K): ";
            cin >> k;
            Node** parts = list.divideList(list.head, k);
            for (int i = 0; i < k; ++i) {
                cout << "Part " << i + 1 << ": ";
                // Print each part separately
                Node* temp = parts[i];
                while (temp) {
                    cout << temp->data << " ";
                    temp = temp->next;
                }
                cout << endl;
            }
            break;
        }
        case 5: {
            list.head = list.removeZeroSumSublists(list.head);
            cout << "List after removing zero-sum consecutive nodes: ";
            list.printList();
            break;
        }
        case 6: {
            list.printList();
            cout << "Enter two node values to swap: ";
            cin >> x >> y;
            list.swapNodes(x, y);
            list.printList();
            break;
        }
        case 7:
            cout << "Current List: ";
            list.printList();
            break;
        case 8:
            cout << "Exiting." << endl;
            break;
        default:
            cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
