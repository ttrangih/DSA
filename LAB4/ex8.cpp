#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Insertion Sort function
void insertionSort(vector<int>& arr, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= left && arr[j] > key) {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

// Partition function for Quick Sort
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            ++i;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Quick Sort function
void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(arr, low, high);
        quickSort(arr, low, pivotIndex - 1);
        quickSort(arr, pivotIndex + 1, high);
    }
}

// Hybrid Quick Sort function using Insertion Sort for small subarrays
void hybridQuickSort(vector<int>& arr, int low, int high) {
    if (high - low <= 10) {
        insertionSort(arr, low, high);  // Use Insertion Sort for small subarrays
    } else {
        if (low < high) {
            int pivotIndex = partition(arr, low, high);
            hybridQuickSort(arr, low, pivotIndex - 1);  // Sort left part
            hybridQuickSort(arr, pivotIndex + 1, high); // Sort right part
        }
    }
}

// Function to measure execution time
void measureTime(void (*sortFunc)(vector<int>&, int, int), vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;
}

int main() {
    // Example arrays for testing
    vector<int> arr1 = {38, 27, 43, 3, 9, 82, 10, 21, 5, 8, 12, 41};  // Small size (12 elements)
    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10, 21, 5, 8, 12, 41};  // Same array for comparison

    // Display original array
    cout << "Array before sorting:" << endl;
    for (int num : arr1) cout << num << " ";
    cout << endl;

    // Measure time for Hybrid Quick Sort
    cout << "Testing Hybrid Quick Sort:" << endl;
    measureTime(hybridQuickSort, arr1);

    // Measure time for Standard Quick Sort
    cout << "Testing Standard Quick Sort:" << endl;
    measureTime(quickSort, arr2);

    return 0;
}
