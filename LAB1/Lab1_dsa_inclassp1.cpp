#include <iostream>

using namespace std;

class Node {
public:
    int data;
    Node* next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

// Function to find the middle node of a linked list
Node* findMiddle(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    return slow;
}

void printList(Node* head) {
    Node* curr = head;
    while (curr != NULL) {
        cout << curr->data << " ";
        curr = curr->next;
    }
    cout << endl;
}

void middleNodeOption(Node* head) {
    Node* middle = findMiddle(head);

    if (middle != NULL) {
        cout << "The middle node is: " << middle->data << endl;
    } else {
        cout << "The list is empty." << endl;
    }
}

//detect a cycle in the linked list
bool detectCycle(Node* head) {
    if (head == NULL) {
        return false;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;

        if (slow == fast) {
            return true;
        }
    }

    return false;
}

 //merge two sorted linked lists
Node* mergeSortedLists(Node* l1, Node* l2) {
    // Nếu một trong hai danh sách rỗng, trả về danh sách còn lại
    if (!l1) return l2;
    if (!l2) return l1;

    // Khởi tạo đầu danh sách mới
    Node* mergedHead = NULL;

    // Xác định đầu tiên của danh sách đã gộp
    if (l1->data < l2->data) {
        mergedHead = l1;
        l1 = l1->next;
    } else {
        mergedHead = l2;
        l2 = l2->next;
    }

    // Con trỏ để duyệt qua danh sách đã gộp
    Node* current = mergedHead;

    // Duyệt qua cả hai danh sách và gộp chúng
    while (l1 && l2) {
        if (l1->data < l2->data) {
            current->next = l1;
            l1 = l1->next;
        } else {
            current->next = l2;
            l2 = l2->next;
        }
        current = current->next;
    }

    if (l1) {
        current->next = l1;
    } else {
        current->next = l2;
    }

    return mergedHead;
}


//
void combineSortedListsOption(Node* head1, Node* head2) {
    Node* mergedHead = mergeSortedLists(head1, head2);
    cout << "Merged Sorted List: ";
    printList(mergedHead);
}


// find the intersection point of two linked lists
int getLength(Node* head) {
    int length = 0;
    while (head != NULL) {
        length++;
        head = head->next;
    }
    return length;
}

Node* findIntersection(Node* head1, Node* head2) {
    int len1 = getLength(head1);
    int len2 = getLength(head2);

    if (len1 > len2) {
        int diff = len1 - len2;
        while (diff--) {
            head1 = head1->next;
        }
    } else {
        int diff = len2 - len1;
        while (diff--) {
            head2 = head2->next;
        }
    }

    while (head1 != NULL && head2 != NULL) {
        if (head1 == head2) {
            return head1;
        }
        head1 = head1->next;
        head2 = head2->next;
    }

    return NULL;
}

void findIntersectionOption(Node* head1, Node* head2) {
    Node* intersection = findIntersection(head1, head2);
    if (intersection != NULL) {
        cout << "The intersection node is: " << intersection->data << endl;
    } else {
        cout << "No intersection found." << endl;
    }
}

// Function to reverse a linked list
Node* reverseList(Node* head) {
    Node* prev = NULL;
    Node* curr = head;
    Node* next = NULL;

    while (curr != NULL) {
        next = curr->next;  // Store next node
        curr->next = prev;  // Reverse current node's pointer
        prev = curr;        // Move prev and curr one step forward
        curr = next;
    }

    head = prev;  // Update head to the new front of the list
    return head;
}

void reverseListOption(Node* &head) {
    head = reverseList(head);
    cout << "Reversed list: ";
    printList(head);
}
 //Eliminate Duplicates from a Sorted Linked List
 Node* removeDuplicates(Node* head) {
    if (head == NULL) {
        return NULL;
    }

    Node* current = head;

    // Duyệt qua danh sách liên kết
    while (current->next != NULL) {
        if (current->data == current->next->data) {
            // Nếu phần tử hiện tại bằng phần tử kế tiếp, bỏ qua phần tử kế tiếp
            Node* duplicate = current->next;
            current->next = current->next->next;
            delete duplicate;  // Xóa phần tử trùng lặp khỏi bộ nhớ
        } else {
            // Di chuyển đến phần tử kế tiếp nếu không có trùng lặp
            current = current->next;
        }
    }

    return head;
}

void removeDuplicatesOption(Node* &head) {
    head = removeDuplicates(head);
    cout << "List after removing duplicates: ";
    printList(head);
}

//Check if a Linked List is a Palindrome
bool isPalindrome(Node* head) {
    if (head == NULL || head->next == NULL) {
        return true;
    }

    // Step 1: Find the middle of the linked list
    Node* slow = head;
    Node* fast = head;
    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse the second half of the linked list
    Node* secondHalf = reverseList(slow);

    // Step 3: Compare the first half and the reversed second half
    Node* firstHalf = head;
    Node* secondHalfCopy = secondHalf;  // Keep a copy of the reversed half to restore later
    while (secondHalf != NULL) {
        if (firstHalf->data != secondHalf->data) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    // Step 4: Restore the second half back to its original form (optional)
    reverseList(secondHalfCopy);

    return true;
}

void checkPalindromeOption(Node* head) {
    if (isPalindrome(head)) {
        cout << "The linked list is a palindrome." << endl;
    } else {
        cout << "The linked list is not a palindrome." << endl;
    }
}

//Search for nodes with the value X in the list.
Node* searchNodes(Node* head, int X) {
    bool found = false;  // kiểm tra có tìm thấy giá trị X không

    Node* current = head;
    while (current != NULL) {
        if (current->data == X) {
            cout << "Node with value " << X << " found at address: " << current << endl;
            found = true;
        }
        current = current->next;
    }

    // Nếu không tìm thấy X, trả về NULL
    if (!found) {
        cout << "No nodes with value " << X << " found." << endl;
        return NULL;
    }

    return head;  //trả về đầu danh sách nếu có tìm thấy giá trị X
}

void searchValueXOption(Node* head, int X) {
    searchNodes(head, X);  //gọi hàm tìm kiếm và in kết quả
}

int main() {

    // Create two lists for intersection test
    Node* head1 = new Node(1);
    head1->next = new Node(3);
    head1->next->next = new Node(5);
    head1->next->next->next = new Node(7);
    head1->next->next->next->next = new Node(9);

    Node* head2 = new Node(2);
    head2->next = new Node(4);
    head2->next->next = head1->next->next->next;  // Intersect at node 7

    // Create another list for middle and cycle detection
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);
    head->next->next->next = new Node(4);
    head->next->next->next->next = new Node(5);

Node* list1 = new Node(1);
    list1->next = new Node(3);
    list1->next->next = new Node(5);

    Node* list2 = new Node(2);
    list2->next = new Node(4);
    list2->next->next = new Node(6);


    int choice;
    int X;

    do {
        cout << "\nMenu:" << endl;
        cout << "1. Find the middle node of the list" << endl;
        cout << "2. Detect a Cycle in the list" << endl;
        cout << "3. Combine Two Sorted Linked Lists" << endl;
        cout << "4. Find Intersection of Two Linked Lists" << endl;
        cout << "5. Reverse a Linked List" << endl;
        cout << "6. Eliminate Duplicates from a Sorted Linked List" << endl;
        cout << "7. Check if a Linked List is a Palindrome" <<endl;
        cout << "8. Search for nodes with the value X in the list." <<endl;
        cout << "9. Current list" <<endl;
        cout << "10. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            middleNodeOption(head);
            break;
        case 2: {
            bool hasCycle = detectCycle(head);
            if (hasCycle) {
                cout << "Cycle detected in the linked list." << endl;
            } else {
                cout << "No cycle in the linked list." << endl;
            }
            break;
        }
        case 3:
            combineSortedListsOption(list1, list2);
            break;
        case 4:
            findIntersectionOption(head1, head2);
            break;
        case 5:
            reverseListOption(head);
            break;
        case 6:
            removeDuplicatesOption(head);
            break;
        case 7:
             checkPalindromeOption(head);
             break;
        case 8:
            cout << "Enter value X to search: ";
            cin >> X;
            searchValueXOption(head, X);
        case 9:
           cout << "Current list: ";
            printList(head);
            break;
        case 10:
             cout << "Exiting..."<< endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 6);

    return 0;
}

