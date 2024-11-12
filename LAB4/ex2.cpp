#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <random>
#include <fstream>

using namespace std;
using namespace std::chrono;

vector<int> generateRandomList(int size) {
    vector<int> arr(size);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 10000);
    for (int &num : arr) num = dis(gen);
    return arr;
}

// Example Bubble Sort
void bubbleSort(vector<int>& arr) {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        for (size_t j = 0; j < arr.size() - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

template <typename SortFunc>
double measureExecutionTime(SortFunc sortFunc, vector<int> arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr);
    auto end = high_resolution_clock::now();
    return duration<double>(end - start).count();
}

int main() {
    vector<int> sizes = {100, 1000, 10000};
    ofstream outputFile("sort_times.csv");
    outputFile << "Algorithm,Size,Time\n";

    for (int size : sizes) {
        vector<int> arr = generateRandomList(size);
        vector<int> arrCopy = arr;
        double execTime = measureExecutionTime(bubbleSort, arrCopy);
        outputFile << "Bubble Sort," << size << "," << execTime << "\n";
    }
    outputFile.close();
    cout << "Results saved to sort_times.csv" << endl;

    return 0;
}
