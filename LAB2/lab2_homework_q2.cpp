//SId: 22521514
//Name: Nguyen Thuy Trang
//Lab_2 Homework question 2

#include <iostream>
using namespace std;

// Node structure to store each URL
struct Node {
    string url;
    Node* next;
};

// Stack structure to hold back or forward history
struct Stack {
    Node* top;

    Stack() {
        top = nullptr;
    }

    // Push an element (URL) onto the stack
    void push(string url) {
        Node* newNode = new Node();
        newNode->url = url;
        newNode->next = top;
        top = newNode;
    }

    // Pop an element (URL) from the stack
    string pop() {
        if (isEmpty()) {
            return ""; // Return empty string if stack is empty
        }
        Node* temp = top;
        string url = top->url;
        top = top->next;
        delete temp;
        return url;
    }

    // Peek the top element of the stack
    string peek() {
        if (!isEmpty()) {
            return top->url;
        }
        return ""; // Return empty string if stack is empty
    }

    // Check if the stack is empty
    bool isEmpty() {
        return top == nullptr;
    }

    // Clear all elements from the stack
    void clear() {
        while (!isEmpty()) {
            pop();
        }
    }
};

// BrowserHistory class with custom stack for back and forward operations
class BrowserHistory {
private:
    Stack backStack;
    Stack forwardStack;
    string currentUrl;

public:
    BrowserHistory(string homepage) {
        currentUrl = homepage;
        forwardStack.clear(); // Clear forward history
    }

    void visit(string url) {
        backStack.push(currentUrl);  // Push current to backStack before visiting new
        currentUrl = url;
        forwardStack.clear(); // Clear forward history
    }

    string back(int steps) {
        while (steps > 0 && !backStack.isEmpty()) {
            forwardStack.push(currentUrl);
            currentUrl = backStack.pop();
            steps--;
        }
        return currentUrl;
    }

    string forward(int steps) {
        while (steps > 0 && !forwardStack.isEmpty()) {
            backStack.push(currentUrl);
            currentUrl = forwardStack.pop();
            steps--;
        }
        return currentUrl;
    }
};

int main() {
    string homepage;
    cout << "Enter the homepage URL: ";
    cin >> homepage;
    BrowserHistory* browserHistory = new BrowserHistory(homepage);

    int choice, steps;
    string url;

    while (true) {
        cout << "\nChoose an operation:\n1. Visit a new URL\n2. Go back\n3. Go forward\n4. Exit\n";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter URL to visit: ";
            cin >> url;
            browserHistory->visit(url);
            cout << "Visited: " << url << endl;
            break;
        case 2:
            cout << "Enter number of steps to go back: ";
            cin >> steps;
            cout << "Current URL after going back: " << browserHistory->back(steps) << endl;
            break;
        case 3:
            cout << "Enter number of steps to go forward: ";
            cin >> steps;
            cout << "Current URL after going forward: " << browserHistory->forward(steps) << endl;
            break;
        case 4:
            cout << "Exiting the browser history simulation." << endl;
            return 0;
        default:
            cout << "Invalid choice. Try again." << endl;
        }
    }

    return 0;
}
