#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace std::chrono;

// Standard Insertion Sort
void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;

        // Move elements of arr[0..i-1], that are greater than key,
        // to one position ahead of their current position
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Binary Search to find the position for insertion
int binarySearch(const vector<int>& arr, int item, int low, int high) {
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (arr[mid] == item)
            return mid + 1; // Insert after duplicates
        else if (arr[mid] < item)
            low = mid + 1;
        else
            high = mid - 1;
    }
    return low;
}

// Binary Insertion Sort
void binaryInsertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        // Find location where key should be inserted
        int pos = binarySearch(arr, key, 0, i - 1);

        // Shift all elements after position to the right
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }
        arr[pos] = key;
    }
}

// Function to measure the execution time
template <typename SortFunc>
double measureExecutionTime(SortFunc sortFunc, vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

int main() {
    const int SIZE = 1000; // Size of array for testing
    vector<int> data(SIZE);

    // Fill array with random integers
    for (int i = 0; i < SIZE; ++i) {
        data[i] = rand() % 10000;
    }

    // Test Standard Insertion Sort
    vector<int> dataCopy = data;
    cout << "Standard Insertion Sort: "
         << measureExecutionTime(insertionSort, dataCopy) << " seconds" << endl;

    // Test Binary Insertion Sort
    dataCopy = data;
    cout << "Binary Insertion Sort: "
         << measureExecutionTime(binaryInsertionSort, dataCopy) << " seconds" << endl;

    return 0;
}
