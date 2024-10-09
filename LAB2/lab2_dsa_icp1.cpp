//22521514_Nguyen Thuy Trang
#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* prev;
    Node* next;

    // Constructor
    Node(int x) {
        data = x;
        prev = NULL;
        next = NULL;
    }
};

class Stack {
private:
    Node* top;  // Pointer to the top of the stack
    int size;
    int maxSize;
public:
    Stack(int maxStackSize) {
        top = nullptr;
        size = 0;
        maxSize = maxStackSize;
    }

    // Function to check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    bool isFull() {
        return size == maxSize;
    }

    void push(int value) {
        if (isFull()) {
            cout << "Stack is full." << endl;
            return;
        }
        Node* newNode = new Node(value);
        newNode->next = top;
        top = newNode;
        size++;
    }

    int pop() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return -1;
        }
        int poppedData = top->data;  // Get the data of the top node
        Node* temp = top;  // Temporary node to hold the current top
        top = top->next;  // Move the top to the next node
        delete temp;  // Delete the old top node
        size--;
        return poppedData;
    }

    // Function to view the top item without removing it
    int peek() {
        if (isEmpty()) {
            cout << "Stack is empty." << endl;
            return -1;
        }
        return top->data;  // Return the data of the top node
    }
    int getSize() {
        return size;
    }
};

int main() {
    int choice;
    int value;
    Stack s(8);  // Initialize the stack

    s.push(10);
    s.push(20);
    s.push(30);


    do {
        // Displaying a simple menu
        cout << "\nMenu:" << endl;
        cout << "1. Initialize the stack" << endl;
        cout << "2. Check if the stack is empty" << endl;
        cout << "3. Check if the stack is full (if applicable)" << endl;
        cout << "4. Push an element onto the stack " << endl;
        cout << "5. Pop an element from the stack" << endl;
        cout << "6. Print the TOP element of the stack" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Top element is: " << s.peek() << endl;
            cout << "Popped element: " << s.pop() << endl;
            cout << "Popped element: " << s.pop() << endl;
            cout << "Top element after popping: " << s.peek() << endl;
            break;
        case 2:
            if (s.isEmpty()) {
                cout << "Stack is empty." << endl;
            }
            else {
                cout << "Stack is not empty." << endl;
            }
            break;
        case 3:
            if (s.isFull()) {
                cout << "Stack is full." << endl;
            }
            else {
                cout << "Stack is not full." << endl;
            }
            break;
        case 4:
            cout << "Enter value to push: ";
            cin >> value;
            s.push(value);
            break;
        case 5:
            value = s.pop();
            if (value != -1) {
                cout << "Popped value: " << value << endl;
            }
        case 6:
            value = s.peek();
            if (value != -1) {
                cout << "Top element is: " << value << endl;
            }
            break;
        default:
            cout << "Invalid choice. Please try again";
            break;
        }
    }
        while (choice != 6);
    return 0;
}
