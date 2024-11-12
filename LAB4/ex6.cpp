#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Helper function to heapify a subtree rooted at index i
void heapify(vector<int>& arr, int n, int i) {
    int largest = i; // Initialize largest as root
    int left = 2 * i + 1; // Left child index
    int right = 2 * i + 2; // Right child index

    // If left child is larger than root
    if (left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    // If right child is larger than largest so far
    if (right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]); // Swap root with largest
        heapify(arr, n, largest);   // Recursively heapify the affected subtree
    }
}

// Function to build a max-heap from the input array
void buildMaxHeap(vector<int>& arr, int n) {
    // Start from the last non-leaf node and heapify each node
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }
}

// Function to find the maximum value in the heap (root of the max-heap)
int findMaxValue(vector<int>& arr, int n) {
    // Build the max-heap
    buildMaxHeap(arr, n);

    // The maximum value will be at the root (index 0)
    return arr[0];
}

int main() {
    vector<int> arr = {3, 5, 1, 10, 2, 7, 6, 8};

    int n = arr.size();
    int maxVal = findMaxValue(arr, n);

    cout << "Maximum value in the array is: " << maxVal << endl;

    return 0;
}
