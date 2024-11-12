#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>

using namespace std;
using namespace chrono;

// Function to perform Insertion Sort
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

// Function to merge two sorted halves
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    // Copy data into temporary arrays
    for (int i = 0; i < n1; ++i)
        L[i] = arr[left + i];
    for (int i = 0; i < n2; ++i)
        R[i] = arr[mid + 1 + i];

    int i = 0, j = 0, k = left;
    // Merge the temp arrays back into the original array
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }

    // Copy the remaining elements of L[], if any
    while (i < n1) {
        arr[k++] = L[i++];
    }
    // Copy the remaining elements of R[], if any
    while (j < n2) {
        arr[k++] = R[j++];
    }
}

// Merge Sort with Hybrid Optimization
void mergeSortHybrid(vector<int>& arr, int left, int right) {
    if (right - left <= 10) {
        insertionSort(arr, left, right);  // Use Insertion Sort for small arrays
        return;
    }

    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHybrid(arr, left, mid);       // Sort the left half
        mergeSortHybrid(arr, mid + 1, right);  // Sort the right half
        merge(arr, left, mid, right);          // Merge the two halves
    }
}

// Standard Merge Sort
void mergeSortStandard(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortStandard(arr, left, mid);       // Sort the left half
        mergeSortStandard(arr, mid + 1, right);  // Sort the right half
        merge(arr, left, mid, right);            // Merge the two halves
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
    // Test arrays with different sizes
    vector<int> arr1 = {38, 27, 43, 3, 9, 82, 10, 21, 5, 8, 12, 41};
    vector<int> arr2 = {38, 27, 43, 3, 9, 82, 10, 21, 5, 8, 12, 41};
    vector<int> arr3 = {38, 27, 43, 3, 9, 82, 10, 21, 5, 8, 12, 41};

    int n1 = arr1.size();
    int n2 = arr2.size();
    int n3 = arr3.size();

    cout << "Array before sorting:" << endl;
    for (int num : arr1) cout << num << " ";
    cout << endl;

    cout << "Testing Merge Sort Standard:" << endl;
    measureTime(mergeSortStandard, arr1);

    cout << "Testing Hybrid Merge Sort:" << endl;
    measureTime(mergeSortHybrid, arr2);

    cout << "Array before sorting:" << endl;
    for (int num : arr3) cout << num << " ";
    cout << endl;

    // You can modify the array sizes here to test different array sizes

    return 0;
}
