#include <iostream>
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;
using namespace std::chrono;

const int SIZE = 1000;

// Hàm tạo mảng ngẫu nhiên
void generateRandomArray(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10000);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

// Bubble Sort
void bubbleSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int minIdx = i;
        for (int j = i + 1; j < size; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[i], arr[minIdx]);
    }
}

// Insertion Sort
void insertionSort(int arr[], int size) {
    for (int i = 1; i < size; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
    }
}

// Quick Sort
int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Merge Sort
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    int L[n1], R[n2];
    for (int i = 0; i < n1; ++i) L[i] = arr[left + i];
    for (int j = 0; j < n2; ++j) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// Hàm đo thời gian thực thi
template <typename SortFunc>
double measureExecutionTime(SortFunc sortFunc, int arr[], int size) {
    int tempArr[SIZE];
    copy(arr, arr + size, tempArr);

    auto start = high_resolution_clock::now();
    sortFunc(tempArr, size);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

// Hàm đo thời gian thực thi cho Quick Sort và Merge Sort
double measureExecutionTimeQuickSort(void (*sortFunc)(int[], int, int), int arr[], int size) {
    int tempArr[SIZE];
    copy(arr, arr + size, tempArr);

    auto start = high_resolution_clock::now();
    sortFunc(tempArr, 0, size - 1);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

int main() {
    int arr[SIZE];
    generateRandomArray(arr, SIZE);

    // Đo thời gian thực thi cho mỗi thuật toán sắp xếp
    cout << "Bubble Sort Time: " << measureExecutionTime(bubbleSort, arr, SIZE) << " seconds" << endl;
    cout << "Selection Sort Time: " << measureExecutionTime(selectionSort, arr, SIZE) << " seconds" << endl;
    cout << "Insertion Sort Time: " << measureExecutionTime(insertionSort, arr, SIZE) << " seconds" << endl;
    cout << "Quick Sort Time: " << measureExecutionTimeQuickSort(quickSort, arr, SIZE) << " seconds" << endl;
    cout << "Merge Sort Time: " << measureExecutionTimeQuickSort(mergeSort, arr, SIZE) << " seconds" << endl;

    return 0;
}
