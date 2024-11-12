#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

// Define a struct to represent a 2D point
struct Point {
    int x, y;

    // Constructor to initialize point
    Point(int x, int y) : x(x), y(y) {}

    // Function to calculate distance from origin
    double distanceFromOrigin() const {
        return sqrt(x * x + y * y);
    }
};

// Insertion Sort for Points based on distance from origin
void insertionSort(vector<Point>& points, int left, int right) {
    for (int i = left + 1; i <= right; ++i) {
        Point key = points[i];
        int j = i - 1;
        while (j >= left && points[j].distanceFromOrigin() > key.distanceFromOrigin()) {
            points[j + 1] = points[j];
            --j;
        }
        points[j + 1] = key;
    }
}

// Partition function for Quick Sort (using distance from origin as key)
int partition(vector<Point>& points, int low, int high) {
    double pivot = points[high].distanceFromOrigin();
    int i = low - 1;
    for (int j = low; j < high; ++j) {
        if (points[j].distanceFromOrigin() < pivot) {
            ++i;
            swap(points[i], points[j]);
        }
    }
    swap(points[i + 1], points[high]);
    return i + 1;
}

// Quick Sort for Points based on distance from origin
void quickSort(vector<Point>& points, int low, int high) {
    if (low < high) {
        int pivotIndex = partition(points, low, high);
        quickSort(points, low, pivotIndex - 1);
        quickSort(points, pivotIndex + 1, high);
    }
}

// Hybrid Quick Sort using Insertion Sort for small subarrays
void hybridQuickSort(vector<Point>& points, int low, int high) {
    if (high - low <= 10) {
        insertionSort(points, low, high);
    } else {
        if (low < high) {
            int pivotIndex = partition(points, low, high);
            hybridQuickSort(points, low, pivotIndex - 1);
            hybridQuickSort(points, pivotIndex + 1, high);
        }
    }
}

// Function to measure execution time of a sort function
void measureTime(void (*sortFunc)(vector<Point>&, int, int), vector<Point>& points) {
    auto start = high_resolution_clock::now();
    sortFunc(points, 0, points.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    cout << "Time taken: " << duration.count() << " ms" << endl;
}

int main() {
    // Sample points (x, y)
    vector<Point> points = {{3, 4}, {1, 1}, {5, 12}, {0, 0}, {9, 40}, {2, 3}, {6, 8}};

    // Display original points
    cout << "Points before sorting: " << endl;
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;

    // Measure time for Hybrid Quick Sort
    cout << "Testing Hybrid Quick Sort:" << endl;
    measureTime(hybridQuickSort, points);

    // Display sorted points
    cout << "Points after sorting: " << endl;
    for (const auto& point : points) {
        cout << "(" << point.x << ", " << point.y << ") ";
    }
    cout << endl;

    return 0;
}
