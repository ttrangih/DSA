#include <iostream>
#include <chrono>
#include <random>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;
using namespace std::chrono;

const int SIZE = 1000;

// Hàm tạo mảng ngẫu nhiên cho `int`
void generateRandomArray(int arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10000);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

// Hàm tạo mảng ngẫu nhiên cho `float`
void generateRandomArray(float arr[], int size) {
    random_device rd;
    mt19937 gen(rd());
    uniform_real_distribution<> dis(0.0, 10000.0);
    for (int i = 0; i < size; ++i) {
        arr[i] = dis(gen);
    }
}

// Hàm tạo mảng ngẫu nhiên cho `string`
void generateRandomArray(string arr[], int size) {
    const string chars = "abcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> lenDis(3, 10);  // Độ dài chuỗi từ 3 đến 10
    for (int i = 0; i < size; ++i) {
        int len = lenDis(gen);
        string str;
        for (int j = 0; j < len; ++j) {
            str += chars[gen() % chars.size()];
        }
        arr[i] = str;
    }
}

// Bubble Sort (template)
template <typename T>
void bubbleSort(T arr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < size - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort (template)
template <typename T>
void selectionSort(T arr[], int size) {
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

// Quick Sort (template)
template <typename T>
int partition(T arr[], int low, int high) {
    T pivot = arr[high];
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

template <typename T>
void quickSort(T arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

// Hàm đo thời gian thực thi
template <typename SortFunc, typename T>
double measureExecutionTime(SortFunc sortFunc, T arr[], int size) {
    T tempArr[SIZE];
    copy(arr, arr + size, tempArr); // Sao chép mảng gốc vào mảng tạm để sắp xếp

    auto start = high_resolution_clock::now();
    sortFunc(tempArr, size);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

template <typename T>
double measureExecutionTimeQuickSort(void (*sortFunc)(T[], int, int), T arr[], int size) {
    T tempArr[SIZE];
    copy(arr, arr + size, tempArr);

    auto start = high_resolution_clock::now();
    sortFunc(tempArr, 0, size - 1);
    auto end = high_resolution_clock::now();

    return duration<double>(end - start).count();
}

int main() {
    int intArr[SIZE];
    float floatArr[SIZE];
    string stringArr[SIZE];

    // Tạo các mảng ngẫu nhiên cho các loại dữ liệu khác nhau
    generateRandomArray(intArr, SIZE);
    generateRandomArray(floatArr, SIZE);
    generateRandomArray(stringArr, SIZE);

    // Đo thời gian thực thi của Bubble Sort với các loại dữ liệu
    cout << "Bubble Sort on int array: " << measureExecutionTime(bubbleSort<int>, intArr, SIZE) << " seconds" << endl;
    cout << "Bubble Sort on float array: " << measureExecutionTime(bubbleSort<float>, floatArr, SIZE) << " seconds" << endl;
    cout << "Bubble Sort on string array: " << measureExecutionTime(bubbleSort<string>, stringArr, SIZE) << " seconds" << endl;

    // Đo thời gian thực thi của Selection Sort với các loại dữ liệu
    cout << "Selection Sort on int array: " << measureExecutionTime(selectionSort<int>, intArr, SIZE) << " seconds" << endl;
    cout << "Selection Sort on float array: " << measureExecutionTime(selectionSort<float>, floatArr, SIZE) << " seconds" << endl;
    cout << "Selection Sort on string array: " << measureExecutionTime(selectionSort<string>, stringArr, SIZE) << " seconds" << endl;

    // Đo thời gian thực thi của Quick Sort với các loại dữ liệu
    cout << "Quick Sort on int array: " << measureExecutionTimeQuickSort(quickSort<int>, intArr, SIZE) << " seconds" << endl;
    cout << "Quick Sort on float array: " << measureExecutionTimeQuickSort(quickSort<float>, floatArr, SIZE) << " seconds" << endl;
    cout << "Quick Sort on string array: " << measureExecutionTimeQuickSort(quickSort<string>, stringArr, SIZE) << " seconds" << endl;

    return 0;
}
