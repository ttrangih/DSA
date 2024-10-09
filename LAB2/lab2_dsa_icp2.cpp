#include <iostream>
using namespace std;

class Node {
public:
    int data;
    Node* next;

    // Constructor to initialize node
    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Queue {
private:
    Node* front;
    Node* rear;
    int size;
    int maxSize;

public:
    // Function to initialize the queue
    Queue(int maxQueueSize) {
        front = nullptr;
        rear = nullptr;
        size = 0;
        maxSize = maxQueueSize;
    }

    //check if the queue is empty
    bool isEmpty() {
        return front == nullptr;
    }

    //check if the queue is full (if applicable)
    bool isFull() {
        return size == maxSize;
    }

    // enqueue an element into the queue
    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue is full." << endl;
            return;
        }

        Node* newNode = new Node(value);

        // If queue is empty, both front and rear will point to the new node
        if (isEmpty()) {
            front = rear = newNode;
        }
        else {
            rear->next = newNode;  // Link the new node at the rear
            rear = newNode;        // Make the new node the rear
        }

        size++;
        cout << value << " enqueued to the queue." << endl;
    }

    //dequeue an element from the queue
    int dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty, nothing to dequeue." << endl;
            return -1;
        }

        Node* temp = front;
        int dequeuedValue = front->data;
        front = front->next;  // Move front to the next node
        delete temp;          // Free the memory of the dequeued node

        size--;

        // If the queue becomes empty, set rear to nullptr
        if (front == nullptr) {
            rear = nullptr;
        }

        return dequeuedValue;
    }

    //print the front element
    int getFront() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        return front->data;
    }

    //print the rear element
    int getRear() {
        if (isEmpty()) {
            cout << "Queue is empty." << endl;
            return -1;
        }
        return rear->data;
    }
};

int main() {
    int choice;
    int value;
    int maxQueueSize;

    // Initialize queue size
    cout << "Enter the maximum size of the queue: ";
    cin >> maxQueueSize;

    Queue q(maxQueueSize);

    do {
        cout << "\nMenu:" << endl;
        cout << "2. Check if the queue is empty" << endl;
        cout << "3. Check if the queue is full" << endl;
        cout << "4. Enqueue an element" << endl;
        cout << "5. Dequeue an element" << endl;
        cout << "6. Print the FRONT element of the queue" << endl;
        cout << "7. Print the REAR element of the queue" << endl;
        cout << "8. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 2:
            if (q.isEmpty()) {
                cout << "Queue is empty." << endl;
            }
            else {
                cout << "Queue is not empty." << endl;
            }
            break;
            case 3:
            if (q.isFull()) {
                cout << "Queue is full." << endl;
            }
            else {
                cout << "Queue is not full." << endl;
            }
            break;
            case 4:
            cout << "Enter value to enqueue: ";
            cin >> value;
            q.enqueue(value);
            break;
            case 5:
            value = q.dequeue();
            if (value != -1) {
                cout << "Dequeued value: " << value << endl;
            }
            break;

        case 6:
            value = q.getFront();
            if (value != -1) {
                cout << "Front element: " << value << endl;
            }
            break;
        case 7:
            value = q.getRear();
            if (value != -1) {
                cout << "Rear element: " << value << endl;
            }
            break;
        case 8:
            cout << "Exiting..." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 8);

    return 0;
}
